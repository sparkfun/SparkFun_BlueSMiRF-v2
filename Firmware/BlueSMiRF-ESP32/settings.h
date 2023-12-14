const uint16_t menuTimeout = 60 * 10; // Menus will exit/timeout after this number of seconds

typedef enum
{
    BLUESMIRF_01 = 0,
    BLUESMIRF_UNKNOWN,
} ProductVariant;
ProductVariant productVariant = BLUESMIRF_01;

// Radio status LED goes from off (LED off), no connection (blinking), to connected (solid)
typedef enum
{
    BT_OFF = 0,
    BT_NOTCONNECTED,
    BT_CONNECTED,
} BTState;

enum
{
    BLUETOOTH_RADIO_SPP = 0,
    BLUETOOTH_RADIO_BLE,
    BLUETOOTH_RADIO_OFF,
};

typedef enum
{
    PRINT_ENDPOINT_SERIAL = 0,
    PRINT_ENDPOINT_BLUETOOTH,
    PRINT_ENDPOINT_ALL,
} PrintEndpoint;
PrintEndpoint printEndpoint = PRINT_ENDPOINT_SERIAL; // Controls where the configuration menu gets piped to

typedef enum
{
    // Original RN-41 behavior. Connect blinks while waiting for BT connect, solid when connected.
    // Status LED off waiting for BT connect, blinks with TX/RX traffic.
    LEDS_CLASSIC = 0,    
    
    // If not BT connection, blink connect LED
    // Connect LED blinks with TX traffic, Status LED blinks with RX traffic.
    LEDS_SERIAL_TRAFFIC, 

    LEDS_ALL_OFF,  // All LEDs off
} LEDS_USE_TYPE;

typedef struct
{
    // Bluetooth settings - 'B'
    uint8_t btType = BLUETOOTH_RADIO_SPP;
    uint16_t btRxSize = 512 * 4;     // Original library is 320 bytes
    uint16_t btTxSize = 512 * 2;     // Original library is 32 bytes
    uint16_t btTimeout = 250;        // Default, ms
    uint8_t btReadTaskPriority = 1;  // Read from BT SPP and write to serialTransmitBuffer. 3 = highest, 0 = lowest
    uint8_t btReadTaskCore = 1;      // Core where task should run, 0=core, 1=Arduino
    uint8_t btWriteTaskPriority = 1; // Read from serialReceiveBuffer and write to SPP. 3 = highest, 0 = lowest
    uint8_t btWriteTaskCore = 1;     // Core where task should run, 0=core, 1=Arduino
    char btPin[5] = "1234";          // Default Pin for older Bluetooth devices is 1234.
    char btNickname[50] = {0};       // User configurable name to broadcast over Bluetooth during discovery
    uint8_t btEscapeCharacter = 0; // The character received from the remote system, sought to enter command mode. Default off.

    // Serial settings - 'S'
    bool echo = false;        // Print locally inputted serial
    bool flowControl = false; // Enable the use of CTS/RTS flow control signals
    bool invertCts = false;   // Invert the input of CTS
    bool invertRts = false;   // Invert the output of RTS
    uint16_t rtsStopSendingPercent =
        5; // Percent of serialReceiveBuffer that is free when RTS is deasserted.  Default of 5% of serialReceiveBuffer.
    uint8_t rtsStartSendingPercent =
        25; // Percent of serialReceiveBuffer that is free when RTS is asserted. Default of 25% of serialReceiveBuffer.
    int baudRate = 115200;
    uint32_t serialReceiveBufferSize =
        1024 * 50; // Buffer size to receive serial data from the serial port, to be sent over Bluetooth.
    uint32_t serialTransmitBufferSize =
        1024 * 10; // Buffer size to receive bytes from Bluetooth waiting to be printed out UART.

    uint32_t uartReceiveBufferSize = 1024 * 2; // Buffer size to receive bytes from hardware interrupt.

    uint16_t serialRxFullThreshold = 50; // RX FIFO full interrupt. Max of ~128. See serialStart().
    int16_t serialTimeout = 1;           // In ms - used during SerialGNSS.begin. Number of ms to pass of no data before
                                         // hardware serial reports data available.

    uint8_t serialReadTaskPriority = 1;  // Read from UART and write to serialReceiveBuffer. 3 = highest, 0 = lowest
    uint8_t serialReadTaskCore = 1;      // Core where task should run, 0=core, 1=Arduino
    uint8_t serialWriteTaskPriority = 1; // Read from serialTransmitBuffer and write to UART. 3 = highest, 0 = lowest
    uint8_t serialWriteTaskCore = 1;     // Core where task should run, 0=core, 1=Arduino

    // System settings - 'Y'
    uint8_t escapeCharacter = '$';    // The character sought to enter command mode
    uint8_t maxEscapeCharacters = 3;  // The number of escape characters required to enter command mode
    uint16_t minEscapeTime_ms = 2000; // Serial traffic must stop this amount before an escape char is recognized
    uint16_t maxCommandTime_ms = 60000; // After this time, command mode cannot be entered
    uint8_t ledStyle = LEDS_CLASSIC;  // Connect LED will blink when waiting for BT connection.
    char wifiSsid[50] = ""; // For firmware update over WiFi
    char wifiPassword[50] = "";

    bool debugSerial = false;
    bool debugBluetooth = false;
    bool enableHeapReport = false;

    uint8_t length = 0; // Used to detect if settings stuct has changed between firmware versions
} Settings;
Settings settings;

// Return values for getString()
typedef enum
{
    INPUT_RESPONSE_GETNUMBER_EXIT = -9999999,
    INPUT_RESPONSE_GETNUMBER_TIMEOUT = -9999998,
    INPUT_RESPONSE_GETCHARACTERNUMBER_TIMEOUT = 255,
    INPUT_RESPONSE_GETCHARACTERNUMBER_EMPTY = 254,
    INPUT_RESPONSE_TIMEOUT = -3,
    INPUT_RESPONSE_OVERFLOW = -2,
    INPUT_RESPONSE_EMPTY = -1,
    INPUT_RESPONSE_VALID = 1,
} InputResponse;

typedef bool (*VALIDATION_ROUTINE)(void *value, uint32_t valMin, uint32_t valMax);

typedef struct _COMMAND_ENTRY
{
    char letter;
    char requireAll;
    bool forceRadioReset;
    uint32_t minValue;
    uint32_t maxValue;
    uint8_t digits;
    uint8_t type;
    VALIDATION_ROUTINE validate;
    const char *name;
    void *setting;
} COMMAND_ENTRY;
