// Read a byte from the serial port
uint8_t systemRead()
{
    return (Serial.read());
}

// Enable printfs to various endpoints
// https://stackoverflow.com/questions/42131753/wrapper-for-printf
void systemPrintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    va_list args2;
    va_copy(args2, args);
    char buf[vsnprintf(nullptr, 0, format, args) + sizeof("\r\n")];

    vsnprintf(buf, sizeof buf, format, args2);

    // Add CR+LF
    buf[sizeof(buf) - 3] = '\r';
    buf[sizeof(buf) - 2] = '\n';
    buf[sizeof(buf) - 1] = '\0';

    systemWrite((const uint8_t *)buf, strlen(buf));

    va_end(args);
    va_end(args2);
}

// Move a buffer of the specified length to the serialTransmitBuffer
void systemWrite(const uint8_t *buffer, uint16_t length)
{
    if (serialTransmitBuffer == nullptr)
    {
        Serial.println("serialTransmitBuffer not malloc'd");
        return;
    }

    for (uint16_t x = 0; x < length; x++)
        serialAddToOutputBuffer(buffer[x]); // Add data to serialTransmitBuffer
}

void systemWrite(uint8_t value)
{
    serialAddToOutputBuffer(value); // Add data to serialTransmitBuffer
}

void systemPrint(const char *string)
{
    systemWrite((const uint8_t *)string, strlen(string));
}

// Print a floating point value with a specified number of decimal places
void systemPrint(float value, uint8_t decimals)
{
    char temp[20];
    sprintf(temp, "%.*f", decimals, value);
    systemPrint(temp);
}

// Print an 8-bit value as HEX or decimal
void systemPrint(uint8_t value, uint8_t printType)
{
    char temp[20];

    if (printType == HEX)
        sprintf(temp, "%02X", value);
    else if (printType == DEC)
        sprintf(temp, "%d", value);

    systemPrint(temp);
}

// Print an integer value
void systemPrint(int value)
{
    char temp[20];
    sprintf(temp, "%d", value);
    systemPrint(temp);
}

// Print a string with a carriage return and linefeed
void systemPrintln(const char *value)
{
    systemPrint(value);
    systemPrint((const char *)"\r\n");
}

// Print a carriage return and linefeed
void systemPrintln()
{
    systemPrint((const char *)"\r\n");
}

// Begin the Preferences library and load the current settings in RAM from NVM
void loadSettings()
{
    Settings tempSettings;

    // We can't use systemPrints here because we haven't malloc'd the buffers yet
    systemSettings.begin("settings"); // Start the preferences library, working within a namespace called settings

    if (systemSettings.getBytesLength("settingsStruct") == 0) // Check if the NVM is blank
    {
        // Use the default constructors for settings
        recordSystemSettings();
        // Serial.println("NVM is blank! Settings are now default");
    }
    else
    {
        systemSettings.getBytes("settingsStruct", &tempSettings, sizeof(Settings)); // Load NVM into the settings struct

        if (tempSettings.length != sizeof(Settings))
        {
            // Use the default constructors for settings
            recordSystemSettings();
            Serial.println("NVM was incorrect length! Settings are now default");
        }
        else
        {
            settings = tempSettings; // Copy settings into global
            // Serial.println("System settings loaded from NVM");
        }
    }
}

void recordSystemSettings()
{
    settings.length = sizeof(Settings);
    systemSettings.putBytes("settingsStruct", &settings, sizeof(Settings)); // Write current settings to NVM
    // systemPrintln("System settings recorded to NVM");
}

// Set setting struct to the default settings
// Settings struct is not recorded to NVM here
void factoryDefaults()
{
    Settings *defaultSettings = new Settings;
    memcpy(&settings, defaultSettings, sizeof(Settings));
    delete defaultSettings;
}

void clearSerialBuffer()
{
    delay(20);
    while (Serial.available())
        Serial.read();
}

// Gathers raw characters from user until \n or \r is received
// Handles backspace
// Used for raw mixed entry (SSID, pws, etc)
// Used by other menu input methods that use sscanf
// Returns INPUT_RESPONSE_TIMEOUT, INPUT_RESPONSE_OVERFLOW, INPUT_RESPONSE_EMPTY, or INPUT_RESPONSE_VALID
InputResponse getString(char *userString, uint8_t stringSize)
{
    clearSerialBuffer();

    long startTime = millis();
    uint8_t spot = 0;

    while ((millis() - startTime) / 1000 <= menuTimeout)
    {
        delay(1); // Yield to processor

        // Get the next input character
        while (Serial.available() > 0)
        {
            byte incoming = Serial.read();

            if ((incoming == '\r') || (incoming == '\n'))
            {
                systemPrintln();         // Echo
                userString[spot] = '\0'; // Null terminate

                if (spot == 0)
                    return INPUT_RESPONSE_EMPTY;

                return INPUT_RESPONSE_VALID;
            }
            else
            {
                Serial.write(incoming); // Echo

                userString[spot++] = incoming;
                if (spot == (stringSize - 1)) // Leave room for termination
                    return INPUT_RESPONSE_OVERFLOW;
            }
        }
    }

    return INPUT_RESPONSE_TIMEOUT;
}

// Gets a single character or number (0-32) from the user. Negative numbers become the positive equivalent.
// Numbers larger than 32 are allowed but will be confused with characters: ie, 74 = 'J'.
// Returns 255 if timeout
// Returns 0 if no data, only carriage return or newline
byte getCharacterNumber()
{
    char userEntry[50]; // Allow user to enter more than one char. sscanf will remove extra.
    int userByte = 0;

    InputResponse response = getString(userEntry, sizeof(userEntry));
    if (response == INPUT_RESPONSE_VALID)
    {
        int filled = sscanf(userEntry, "%d", &userByte);
        if (filled == 0) // Not a number
            sscanf(userEntry, "%c", (byte *)&userByte);
        else
        {
            if (userByte == 255)
                userByte = 0; // Not allowed
            else if (userByte > 128)
                userByte *= -1; // Drop negative sign
        }
    }
    else if (response == INPUT_RESPONSE_TIMEOUT)
    {
        systemPrintln("\r\nNo user response - Do you have line endings turned on?");
        userByte = INPUT_RESPONSE_GETCHARACTERNUMBER_TIMEOUT; // Timeout
    }
    else if (response == INPUT_RESPONSE_EMPTY)
    {
        userByte = 0; // Empty
    }

    return userByte;
}

// Get a long int from user, uses sscanf to obtain 64-bit int
// Returns INPUT_RESPONSE_GETNUMBER_EXIT if user presses 'x' or doesn't enter data
// Returns INPUT_RESPONSE_GETNUMBER_TIMEOUT if input times out
long getNumber()
{
    char userEntry[50]; // Allow user to enter more than one char. sscanf will remove extra.
    long userNumber = 0;

    InputResponse response = getString(userEntry, sizeof(userEntry));
    if (response == INPUT_RESPONSE_VALID)
    {
        if (strcmp(userEntry, "x") == 0 || strcmp(userEntry, "X") == 0)
            userNumber = INPUT_RESPONSE_GETNUMBER_EXIT;
        else
            sscanf(userEntry, "%ld", &userNumber);
    }
    else if (response == INPUT_RESPONSE_TIMEOUT)
    {
        systemPrintln("\r\nNo user response - Do you have line endings turned on?");
        userNumber = INPUT_RESPONSE_GETNUMBER_TIMEOUT; // Timeout
    }
    else if (response == INPUT_RESPONSE_EMPTY)
    {
        userNumber = INPUT_RESPONSE_GETNUMBER_EXIT; // Empty
    }

    return userNumber;
}

// Gets a double (float) from the user
// Returns INPUT_RESPONSE_GETNUMBER_TIMEOUT for timeout and 0 for empty response
double getDouble()
{
    char userEntry[50];
    double userFloat = 0.0;

    InputResponse response = getString(userEntry, sizeof(userEntry));
    if (response == INPUT_RESPONSE_VALID)
    {
        if (strcmp(userEntry, "x") == 0 || strcmp(userEntry, "X") == 0)
            userFloat = INPUT_RESPONSE_GETNUMBER_EXIT;
        else
            sscanf(userEntry, "%lf", &userFloat);
    }
    else if (response == INPUT_RESPONSE_TIMEOUT)
    {
        systemPrintln("No user response - Do you have line endings turned on?");
        userFloat = INPUT_RESPONSE_GETNUMBER_TIMEOUT;
    }
    else if (response == INPUT_RESPONSE_EMPTY)
    {
        userFloat = 0.0;
    }

    return userFloat;
}

// Option not known
void printUnknown(uint8_t unknownChoice)
{
    systemPrint("Unknown choice: ");
    Serial.write(unknownChoice);
    systemPrintln();
}

void printUnknown(int unknownValue)
{
    systemPrint("Unknown value: ");
    systemPrint((uint8_t)unknownValue, DEC);
    systemPrintln();
}

// Case independent string comparison
int stricmp(const char *str1, const char *str2)
{
    char char1;
    char char2;

    // Do a case insensitive comparison between the two strings
    do
    {
        char1 = toupper(*str1++);
        char2 = toupper(*str2++);
    } while (char1 && (char1 == char2));

    // Return the difference between the two strings
    return char1 - char2;
}

// Case independent string comparison with specified maximum length
int strnicmp(const char *str1, const char *str2, int length)
{
    char char1;
    char char2;

    // Do a case insensitive comparison between the two strings
    do
    {
        char1 = toupper(*str1++);
        char2 = toupper(*str2++);
    } while (char1 && (char1 == char2) && --length);

    // Return the difference between the two strings
    return char1 - char2;
}

// Platform specific reset commands
void systemReset()
{
    ESP.restart();
}

// Ensure all serial output has been transmitted, FIFOs are empty
void systemFlush()
{
    // Wait for btWriteTask task to clear serialReceiveBuffer
    while (availableRXBytes() > 0)
        delay(1);

    // Wait for serialWriteTask task to clear serialTransmitBuffer
    while (availableTXBytes() > 0)
        delay(1);

    if (printEndpoint == PRINT_ENDPOINT_ALL)
    {
        Serial.flush();
        bluetoothFlush();
    }
    else if (printEndpoint == PRINT_ENDPOINT_BLUETOOTH)
        bluetoothFlush();
    else
        Serial.flush();
}

// If debug option is on, print available heap
void reportHeapNow()
{
    if (settings.enableHeapReport == true)
    {
        lastHeapReport = millis();
        systemPrintf("FreeHeap: %d / HeapLowestPoint: %d / LargestBlock: %d\r\n", ESP.getFreeHeap(),
                     xPortGetMinimumEverFreeHeapSize(), heap_caps_get_largest_free_block(MALLOC_CAP_8BIT));
    }
}

// If debug option is on, print available heap
void reportHeap()
{
    if (settings.enableHeapReport == true)
    {
        if (millis() - lastHeapReport > 1000)
        {
            reportHeapNow();
        }
    }
}

// Get the current firmware version
void getFirmwareVersion(char *buffer, int bufferLength, bool includeDate)
{
    formatFirmwareVersion(FIRMWARE_VERSION_MAJOR, FIRMWARE_VERSION_MINOR, buffer, bufferLength, includeDate);
}

// Format the firmware version
void formatFirmwareVersion(uint8_t major, uint8_t minor, char *buffer, int bufferLength, bool includeDate)
{
    char prefix;

    // Construct the full or release candidate version number
    prefix = ENABLE_DEVELOPER ? 'd' : 'v';
    if (settings.enableRCFirmware && (bufferLength >= 21))
        // 123456789012345678901
        // pxxx.yyy-dd-mmm-yyyy0
        snprintf(buffer, bufferLength, "%c%d.%d-%s", prefix, major, minor, __DATE__);

    // Construct a truncated version number
    else if (bufferLength >= 9)
        // 123456789
        // pxxx.yyy0
        snprintf(buffer, bufferLength, "%c%d.%d", prefix, major, minor);

    // The buffer is too small for the version number
    else
    {
        systemPrintf("ERROR: Buffer too small for version number!\r\n");
        if (bufferLength > 0)
            *buffer = 0;
    }
}