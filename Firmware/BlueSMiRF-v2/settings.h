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
    BT_OFF = 0,      // Entered if user turns off Bluetooth entirely
    BT_NOTCONNECTED, // Default mode. Waiting to be connected to.
    BT_CONNECTED,    // Entered when BT singles it has a connection
    BT_PAIRING,      // Entered when pair mode is active

    // BT_CONNECTING,   // Entered if a board is connecting to a paired MAC
    // BT_SCANNING,     // Entered when pair mode is active
    // BT_DISCOVERABLE, // Entered when scanning fails to detect any friendly devices
} BTState;

typedef enum
{
    LED_OFF = 0,            // Both LEDs off
    LED_BLUETOOTH_STARTING, // Both LEDs on
    LED_NOTCONNECTED,       // S-0/C-1Hz: Default mode. Waiting to be connected to.
    LED_CONNECTED,          // S-0/C-1: Entered when BT singles it has a connection
    LED_CONNECTING,         // S-1/C-0: Entered if a board is connecting to a paired MAC
    LED_SCANNING,           // S-Fade/C-0: Entered when actively scanning for compatible devices
    LED_DISCOVERABLE,       // S-0/C-Fade: Entered when scanning fails to detect any friendly devices

    LED_BUTTON_3S_HOLD, // Blink S/C back/forth at 2Hz. Entered when user holds button for > 3 second
    LED_BUTTON_8S_HOLD, // Blink S/C back/forth at 10Hz. Entered when user holds button for > 8 seconds

    LED_CONFIG, // Fade S/C during serial configuration
} LEDState;
LEDState ledState = LED_OFF;
LEDState oldLedState = LED_OFF;

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

    LEDS_ALL_OFF, // All LEDs off
} LEDS_USE_TYPE;

typedef struct
{
    // Bluetooth settings - 'B'
    uint8_t btConnectRetries = 5;       // Number of retries of a paired connection
    uint16_t btConnectTimeoutMs = 3000; // Milliseconds before a paired connection attempt times out
    uint8_t btEscapeCharacter = '+';    // The character received from the remote system, sought to enter command mode.
    char btNickname[50] = {0};          // User configurable name to broadcast over Bluetooth during discovery
    uint8_t btPairedMac[6] = {0};       // MAC address of the unit that the user wants to connect to at startup
    char btPairedName[50] = {0};        // Name of the unit that the user wants to connect to at startup
    bool btPairOnStartup = false;       // Goes true when user initiates a pair. Work around for core discover bug
    // See issue: https://github.com/espressif/arduino-esp32/issues/8448
    char btPin[5] = "1234";         // Default Pin for older Bluetooth devices is 1234.
    uint8_t btReadTaskCore = 1;     // Core where task should run, 0=core, 1=Arduino
    uint8_t btReadTaskPriority = 1; // Read from BT SPP and write to serialTransmitBuffer. 3 = highest, 0 = lowest
    uint16_t btRxSize = 1024 * 10;    // Receive buffer size. Original library is 320 bytes
    uint16_t btTimeout = 250;        // Default, ms
    uint16_t btTxSize = 1024 * 10;     // Original library is 32 bytes
    uint8_t btType = BLUETOOTH_RADIO_SPP;
    uint8_t btWriteTaskCore = 1;     // Core where task should run, 0=core, 1=Arduino
    uint8_t btWriteTaskPriority = 1; // Read from serialReceiveBuffer and write to SPP. 3 = highest, 0 = lowest

    // Serial settings - 'S'
    bool flowControl = false; // Enable the use of CTS/RTS flow control signals
    bool invertCts = false;   // Invert the input of CTS
    bool invertRts = false;   // Invert the output of RTS
    uint16_t serialPartialFrameTimeoutMs = 50; // Send partial buffer if time expires
    uint8_t rtsStartSendingPercent =
        25; // Percent of serialReceiveBuffer that is free when RTS is asserted. Default of 25% of serialReceiveBuffer.
    uint32_t serialReceiveBufferSize =
        1024 * 500; // Buffer size to receive serial data from the serial port, to be sent over Bluetooth.
    uint16_t rtsStopSendingPercent =
        5; // Percent of serialReceiveBuffer that is free when RTS is deasserted. Default of 5% of serialReceiveBuffer.
    int baudRate = 115200; // Also known as SerialSpeed
    uint32_t serialTransmitBufferSize =
        1024 * 500; // Buffer size to receive bytes from Bluetooth waiting to be printed out UART.

    uint32_t uartReceiveBufferSize = 1024 * 500; // Buffer size to receive bytes from hardware interrupt.
    uint16_t serialRxFullThreshold = 50; // RX FIFO full interrupt. Max of ~128. See serialStart().
    int16_t serialTimeout = 1;           // In ms - used during SerialGNSS.begin. Number of ms to pass of no data before
                                         // hardware serial reports data available.

    uint8_t serialReadTaskPriority = 1;  // Read from UART and write to serialReceiveBuffer. 3 = highest, 0 = lowest
    uint8_t serialReadTaskCore = 1;      // Core where task should run, 0=core, 1=Arduino
    uint8_t serialWriteTaskPriority = 1; // Read from serialTransmitBuffer and write to UART. 3 = highest, 0 = lowest
    uint8_t serialWriteTaskCore = 1;     // Core where task should run, 0=core, 1=Arduino

    // System settings - 'Y'
    uint8_t escapeCharacter = '$';      // The character sought to enter command mode
    uint8_t maxEscapeCharacters = 3;    // The number of escape characters required to enter command mode
    uint8_t ledStyle = LEDS_CLASSIC;    // Controls the behavior of the Status and Connect LEDs
    uint16_t maxCommandTime_ms = 60000; // After this time, command mode cannot be entered
    uint16_t minEscapeTime_ms = 2000;   // Serial traffic must stop this amount before an escape char is recognized
    uint16_t psramThreshold = 1000;     // Use PSRAM for memory requests larger than this number of bytes
    char wifiSsid[50] = "";             // For firmware update over WiFi
    char wifiPassword[50] = "";


    bool debugSerial = false;
    bool debugBluetooth = false;
    bool enableHeapReport = false;

    uint16_t length = 0; // Used to detect if settings stuct has changed between firmware versions
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
    char display;
    bool forceRadioReset;
    uint32_t minValue;
    uint32_t maxValue;
    uint8_t digits;
    uint8_t type;
    VALIDATION_ROUTINE validate;
    const char *name;
    void *setting;
} COMMAND_ENTRY;
