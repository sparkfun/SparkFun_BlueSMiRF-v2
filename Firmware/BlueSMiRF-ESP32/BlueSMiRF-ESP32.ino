/*
  Read in serial and transmit over Bluetooth SPP
  Date: August 18, 2023
  License: MIT. See license file for more information but you can basically do whatever you want with this code.

  We have multiple buffers to control the flow of serial data.

  The built-in Bluetooth library has been modified to allow run-time creation
  of variable buffer sizes for both TX and RX buffers controlled by settings.bluetoothTxSize
  and settings.bluetoothRxSize. The Bluetooth RX buffer is crucial as it is the buffer that
  gets used if a Bluetooth transmission fails - the bluetoothRxSize buffer needs to be large enough to handle
  incoming serial when an outgoing RF packet fails to be delivered.

  Additionally, we have two holding buffers: serialReceiveBuffer and serialTransmitBuffer
      serialReceiveBuffer receives incoming serial from UART0 and gets moved into
      bluetoothWrite() (which uses a bluetoothRxSize'd buffer)
      serialTransmitBuffer receives data from Bluetooth (with uses a bluetoothTxSize'd buffer)
      and gets Serial.write to UART0

  The serialReceiveBuffer and serialTransmitBuffer are needed in case:
      The external system drives CTS high (CTS is asserted) indicating the BlueSMiRF should stop transmitting serial
      data out the TX pin. At which time the serialTransmitBuffer will begin to fill up.
      The Bluetooth stack becomes congested. At which time the serialReceiveBuffer will begin to fill up. If the
      serialReceiveBuffer hits a high water mark then the BlueSMiRF will drive RTS high (RTS is asserted) telling the
      external system to stop sending serial data. By default, the high water mark is when the buffer becomes <25%
      available, but is configurable (settings.rtsOnPercent).

  Note: CTS and RTS are only active/used when flow control is enabled (by default flow control is disabled).
  Note: CTS and RTS logic can be inverted (selectively) for rare systems that require it.

  Note: All visible ASCII characters are allowed in the command parser with the following exceptions:
    \ is not allowed
    # is seen as a script comment. Anything following a # will be ignored.

  Compiler settings:
  * Board: ESP32 Dev Module
  * Flash Size: 4MB
  * Partition Scheme: Use custom partition file called BlueSMiRF_Partitions.csv (or built-in "Minimal SPIFFs (1.9MB APP
  with OTA)")
  * PSRAM: Enabled
*/

#define COMPILE_BT // Comment out to remove Bluetooth functionality
#define COMPILE_WIFI // Comment out to remove WiFi functionality

// This is passed in from compiler extra flags
#ifndef FIRMWARE_VERSION_MAJOR
#define FIRMWARE_VERSION_MAJOR 99
#define FIRMWARE_VERSION_MINOR 99
#endif // FIRMWARE_VERSION_MAJOR

// Hardware connections
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#define PIN_UNDEFINED 255

uint8_t pin_pairButton = PIN_UNDEFINED;
uint8_t pin_cts = PIN_UNDEFINED;
uint8_t pin_rts = PIN_UNDEFINED;
uint8_t pin_statusLED = PIN_UNDEFINED;
uint8_t pin_connectLED = PIN_UNDEFINED;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "settings.h"

// Hardware serial and BT buffers
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifdef COMPILE_BT
// See bluetoothSelect.h for implementation
#include "bluetoothSelect.h"
#endif // COMPILE_BT

#include <driver/uart.h> //Required for uart_set_rx_full_threshold() on cores <v2.0.5

TaskHandle_t btReadTaskHandle = nullptr; // Store task handle so that we can delete it if needed
const int btReadTaskStackSize = 2000;

TaskHandle_t btWriteTaskHandle = nullptr; // Store task handle so that we can delete it if needed
const int btWriteTaskStackSize = 2000;

volatile static int combinedSpaceRemaining = 0; // Overrun indicator
int bufferOverruns = 0;                         // Running count of possible data losses since power-on

bool btPrintEcho = false;     // Set true when echoing all serial prints to Bluetooth.
bool btPrintEchoExit = false; // When true, exit command mode.
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Global variables - Serial
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Buffer to receive serial data from the serial port, for transmission via the radio
uint32_t serialRxHead = 0;
uint32_t serialRxTail = 0;
uint8_t *serialReceiveBuffer = nullptr; // Buffer to receive serial data from the serial port

// Buffer to store bytes to be sent to the USB or serial ports
uint32_t serialTxHead = 0;
uint32_t serialTxTail = 0;
uint8_t *serialTransmitBuffer =
    nullptr; // Bytes received from RF waiting to be printed out UART. Buffer up to 1s of bytes at 4k

TaskHandle_t serialReadTaskHandle = nullptr; // Store task handle so that we can delete it if needed
const int serialReadTaskStackSize = 10000;   // Must be larger to handle command interface + WiFi update

TaskHandle_t serialWriteTaskHandle = nullptr; // Store task handle so that we can delete it if needed
const int serialWriteTaskStackSize = 3000;

unsigned long lastByteReceived_ms = 0; // Track when last transmission was. Send partial buffer once time has expired.
uint32_t rtsStartSendingBytes = 0;     // Calculated as a percentage of the overall buffer size. Calc'd at beginSerial
uint32_t rtsStopSendingBytes = 0;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Global variables - Command Processing
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
char commandBuffer[100];           // Received serial gets stored into buffer until \r or \n is received
uint8_t commandRXBuffer[100];      // Bytes received from remote, waiting for printing or AT parsing
uint8_t commandTXBuffer[1024 * 4]; // Bytes waiting to be transmitted to the remote unit
uint16_t commandTXHead = 0;
uint16_t commandTXTail = 0;
uint16_t commandRXHead = 0;
uint16_t commandRXTail = 0;

unsigned long lastEscapeReceived_ms = 0; // Tracks end of serial traffic

bool rtsAsserted; // When RTS is asserted, host says it's ok to send data
bool remoteCommandResponse;
bool waitRemoteCommandResponse;

uint8_t commandLength = 0;
bool forceRadioReset = false; // Goes true when a setting requires a link/radio reset to work
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Preferences for storing settings
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#include <Preferences.h> //Built-in ESP32 library
Preferences systemSettings;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Buttons - Interrupt driven and debounce
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#include <JC_Button.h> //http://librarymanager/All#JC_Button v2.1.2
Button *pairButton = nullptr;

TaskHandle_t ButtonCheckTaskHandle = nullptr;
const uint8_t ButtonCheckTaskPriority = 0; // 3 being the highest, and 0 being the lowest
const int buttonTaskStackSize = 2000;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// WiFi
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
#ifdef COMPILE_WIFI

#include <WiFi.h>      //Built-in.
#include <WiFiMulti.h> //Built-in.

#endif
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Over-The-Air Update
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
#ifdef COMPILE_WIFI

#include "ESP32OTAPull.h" //http://librarymanager/All#ESP-OTA-Pull Used for getting

#define OTA_FIRMWARE_JSON_URL                                                                                          \
    "https://raw.githubusercontent.com/sparkfun/SparkFun_RTK_Firmware_Binaries/main/RTK-Firmware.json"
//"https://raw.githubusercontent.com/sparkfun/SparkFun_BlueSMiRF_Binaries/main/BlueSMiRF-Firmware.json"
#endif
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Status and Connect LED control
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
TaskHandle_t ledTaskHandle = nullptr; // Store task handle so that we can delete it if needed
const int ledTaskStackSize = 2000;
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// Global variables
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
char platformPrefix[12] = "BlueSMiRF"; // Sets the prefix for broadcast names
uint8_t btMACAddress[6];
char broadcastName[100]; // The serial string that is broadcast. Ex: 'BlueSMiRF-BC61'

Settings tempSettings; // Temporary settings used for command processing

bool inLocalCommandMode = false;  // Normal data is prevented from entering serial output when in command mode
uint32_t lastHeapReport = 0; // Report heap every 1s if option enabled
uint32_t lastReport_ms = 0;

uint32_t lastLedUpdate = 0;  // Timer for LEDs
int statusLedBrightness = 0; // Enables LED to fade up/down
int statusFadeAmount = 0;
int connectLedBrightness = 0;
int connectFadeAmount = 0;
const int startingFadeAmount = 10; // Controls aggressiveness of fade.
const int fadeUpdateTimeMs = 20;   // ms between fade updates
const int maxFadeBrightness =
    200; // Because brightness is non-linear, we reduce time where LED isn't noticeably changing

bool friendlyDeviceFound = false; // Goes true during manual pairing if friendly device is discovered

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

void setup()
{
    Serial.begin(115200); // Start serial for any initial debug messages

    loadSettings(); // Get settings from NVM

    serialStart(); // Malloc serial TX and RX buffers

    beginBoard(); // Setup input/output pins

    ledBegin(); // Setup the LEDs

    buttonBegin(); // Setup the pair button

    bluetoothBegin(); // Setup Bluetooth radio for normal or paired communication

    ledStatusOff(); // Turn off Status LED until serial traffic is detected

    rtsAssert(); // Signal to external system that we are ready for data
}

void loop()
{
    /* Data flows through the following tasks
      serialReadTask() - Read from UART and write to serialReceiveBuffer. Check for escape characters. Echo characters
      to serialTransmitBuffer.
      btWriteTask() - Read from serialReceiveBuffer and write to SPP.

      btReadTask() - Read from BT SPP and write to serialTransmitBuffer. Check for escape characters.
      serialWriteTask() - Read from serialTransmitBuffer and write to UART.

      ledUpdate() - Updates the state of the Status and Connect LEDs
    */

    reportHeap(); // Display available RAM on heap

    // Force exit command mode if Bluetooth link is dropped
    if (btPrintEchoExit == true)
    {
        btPrintEchoExit = false;
        inCommandMode = false;
        commandLength = 0; // Get ready for next command
    }

    // Allow other low (0) priority tasks to run
    feedWdt();
    taskYIELD();
}
