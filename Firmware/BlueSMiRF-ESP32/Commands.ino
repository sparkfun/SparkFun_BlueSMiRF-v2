// To add a new ATxx command:
// Add an entry to the "commands" table below

// To add a new commnd prefix such as AT or RT
// Add an entry to the "prefix" table below

//----------------------------------------
//  Data structures
//----------------------------------------

enum
{
    TYPE_BOOL = 0,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_CHAR,
    TYPE_SPEED_SERIAL,
    TYPE_U8,
    TYPE_U16,
    TYPE_U32,
    TYPE_MAC,
};

typedef bool (*COMMAND_ROUTINE)(const char *commandString);
typedef struct
{
    const char *prefix;
    COMMAND_ROUTINE processCommand;
} COMMAND_PREFIX;

//----------------------------------------
//  Command table
//----------------------------------------

const COMMAND_ENTRY commands[] = {
    /*Bluetooth parameters
     Ltr, All, reset, min, max, digits,    type,         validation,     name, setting addr */
    {'B', 0, 0, 0, 1, 0, TYPE_U8, valInt, "BluetoothType", &tempSettings.btType},
    {'B', 0, 0, 0, 1024 * 10, 0, TYPE_U16, valInt, "BluetoothRxSize", &tempSettings.btRxSize}, // Arbitrary 10k max
    {'B', 0, 0, 0, 1024 * 10, 0, TYPE_U16, valInt, "BluetoothTxSize", &tempSettings.btTxSize},
    {'B', 0, 0, 0, 3, 0, TYPE_U8, valInt, "BluetoothReadTaskPriority", &tempSettings.btReadTaskPriority},
    {'B', 0, 0, 0, 1, 0, TYPE_U8, valInt, "BluetoothReadTaskCore", &tempSettings.btReadTaskCore},
    {'B', 0, 0, 0, 1, 0, TYPE_U8, valInt, "BluetoothReadTaskCore", &tempSettings.btReadTaskCore},
    {'B', 0, 0, 0, 50, 0, TYPE_STRING, valString, "BluetoothNickname", &tempSettings.btNickname},
    {'B', 0, 0, 100, 25000, 0, TYPE_U16, valInt, "BluetoothConnectTimeoutMs", &tempSettings.btConnectTimeoutMs},
    {'B', 0, 0, 0, 100, 0, TYPE_U8, valInt, "BluetoothConnectRetries", &tempSettings.btConnectRetries},
    {'B', 0, 0, 0, 0, 0, TYPE_MAC, valMac, "BluetoothPairedMac", &tempSettings.btPairedMac},
    {'B', 0, 0, 0, 50, 0, TYPE_STRING, valString, "BluetoothPairedName", &tempSettings.btPairedName},

    /*System parameters
     Ltr, All, reset, min, max, digits,    type,         validation,     name, setting addr */
    {'Y', 0, 0, ' ', '~', 0, TYPE_CHAR, valChar, "EscapeCharacter", &tempSettings.escapeCharacter},
    {'Y', 0, 0, 0, 255, 0, TYPE_U8, valInt, "EscapeCharacterCount", &tempSettings.maxEscapeCharacters},
    {'Y', 0, 0, 0, 20000, 0, TYPE_U16, valInt, "MinEscapeTimeMs", &tempSettings.minEscapeTime_ms}, // Arbitrary 20s max
    {'Y', 0, 0, 0, 65000, 0, TYPE_U16, valInt, "MaxCommandTimeMs",
     &tempSettings.maxCommandTime_ms}, // Arbitrary 65s max
    {'Y', 0, 0, 0, 255, 0, TYPE_U8, valInt, "LedStyle", &tempSettings.ledStyle},
    {'Y', 0, 0, 0, 50, 0, TYPE_STRING, valString, "WiFiSSID", &tempSettings.wifiSsid},
    {'Y', 0, 0, 0, 50, 0, TYPE_STRING, valString, "WiFiPassword", &tempSettings.wifiPassword},
    // AT-BluetoothPairedName=test

    /*Serial parameters
      Ltr, All, reset, min, max, digits,    type,         validation,     name,                   setting addr */
    {'S', 0, 0, 0, 1, 0, TYPE_BOOL, valInt, "Echo", &tempSettings.echo},
    {'S', 0, 0, 0, 1, 0, TYPE_BOOL, valInt, "FlowControl", &tempSettings.flowControl},
    {'S', 0, 0, 0, 1, 0, TYPE_BOOL, valInt, "InvertCts", &tempSettings.invertCts},
    {'S', 0, 0, 0, 1, 0, TYPE_BOOL, valInt, "InvertRts", &tempSettings.invertRts},
    {'S', 0, 0, 1, 99, 0, TYPE_U8, valInt, "RtsStopSendingPercent", &tempSettings.rtsStopSendingPercent},
    {'S', 0, 0, 1, 99, 0, TYPE_U8, valInt, "RtsStartSendingPercent", &tempSettings.rtsStartSendingPercent},
    {'S', 0, 0, 0, 0, 0, TYPE_U32, valInt, "SerialReceiveBufferSize", &tempSettings.serialReceiveBufferSize},
    {'S', 0, 0, 0, 0, 0, TYPE_U32, valInt, "SerialTransmitBufferSize", &tempSettings.serialTransmitBufferSize},
    {'S', 0, 0, 0, 0, 0, TYPE_SPEED_SERIAL, valSpeedSerial, "SerialSpeed", &tempSettings.baudRate},
    {'S', 0, 0, 0, 1000, 0, TYPE_U16, valInt, "PartialFrameTimeout", &tempSettings.serialPartialFrameTimeoutMs}, // Arbitrary 1s max

    /*Debug parameters
      Ltr, All, reset, min, max, digits,    type,         validation,     name,                   setting addr */
    {'D', 0, 0, 0, 1, 0, TYPE_BOOL, valInt, "DebugSerial", &tempSettings.debugSerial},
    {'D', 0, 0, 0, 1, 0, TYPE_BOOL, valInt, "DebugBluetooth", &tempSettings.debugBluetooth},
    {'D', 0, 0, 0, 1, 0, TYPE_BOOL, valInt, "DebugHeap", &tempSettings.enableHeapReport},
};

const int commandCount = sizeof(commands) / sizeof(commands[0]);

//----------------------------------------
//  Command prefix routines
//----------------------------------------

// Process the AT commands
bool commandAT(const char *commandString)
{
    uint32_t delayMillis;
    long deltaMillis;
    const char *string;
    unsigned long timer;

    static bool newOTAFirmwareAvailable = false;

    //'AT'
    if (commandLength == 2)
        return true;

    // AT?, ATA, ATB, ATD, ATF, ATS, ATW, ATX, ATY, ATZ commands
    if (commandLength == 3)
    {
        switch (commandString[2])
        {
        default:
            return false;

        case ('?'): // Display the command help
            systemPrintln("Command summary:");
            systemPrintln("  AT? - Print the command summary");
            systemPrintln("  ATA - Display all settings");
            systemPrintln("  ATB - Display Bluetooth settings"); // User settings
#ifdef COMPILE_WIFI
            if (newOTAFirmwareAvailable == false)
                systemPrintln("  ATC - Check for new firmware");
            else
                ; // Don't print anything
#else
            systemPrintln("  ATC - Check for new firmware ** WiFi not compiled **");
#endif
            systemPrintln("  ATD - Display debug settings"); // User settings
            systemPrintln("  ATF - Restore factory settings");
            systemPrintln("  ATM - Display MAC");
            systemPrintln("  ATP - Start Pairing Process");
            systemPrintln("  ATS - Display serial settings"); // User settings
            if (newOTAFirmwareAvailable == true)
#ifdef COMPILE_WIFI
                systemPrintln("  ATU - Update Firmware");
#else
                systemPrintln("  ATU - Update Firmware ** WiFi not compiled **");
#endif
            systemPrintln("  ATV - Display firmware version");
            systemPrintln("  ATW - Save current settings to NVM");
            systemPrintln("  ATX - Exit command mode");
            systemPrintln("  ATY - Display system settings"); // User settings
            systemPrintln("  ATZ - Reboot the system");
            systemPrintln("  AT-Param=xxx - Set parameter's value to xxx by name (Param)");
            systemPrintln("  AT-Param? - Print parameter's current value by name (Param)");
            return true;

        case ('C'): // ATC - Check for new firmware
#ifdef COMPILE_WIFI
            newOTAFirmwareAvailable = wifiCheckNewFirmware();
#else
            systemPrintln(" ** WiFi not compiled **");
#endif
            return true;

        case ('F'):                  // ATF - Reset to factory default
            factoryDefaults();       // Set settings struct to defaults
            recordSystemSettings();  // Record current settings struct to NVM
            tempSettings = settings; // Make AT command system temp settings reflect current settings struct
            // If the user changes the temp settings after this, they are applied, but not recorded to NVM
            systemPrintln("Factory defaults applied");
            return true;

        case ('M'): // ATM - Display MAC
            systemPrintf("%s", stringMac(btMACAddress));
            return true;

        case ('P'): // ATP - Start Pairing Process
        {
            if (settings.debugBluetooth == true)
                systemPrintln("Command initiated pairing");

            if (bluetoothConnected() == true)
            {
                // We can't initiate a discovery after the Bluetooth stack has connected
                // See issue: https://github.com/espressif/arduino-esp32/issues/8448
                // Workaround is to set flag and reset

                if (settings.debugBluetooth == true)
                {
                    systemPrintln("Reset for pairing work around");
                    delay(50); // Allow print to finish
                }
                settings.btPairOnStartup = true;
                recordSystemSettings();
                ESP.restart();
            }

            bluetoothBeginPairing();
            return true;
        }

        case ('U'): // ATU - Update firmware
            if (newOTAFirmwareAvailable == true)
                wifiUpdate();
            return true;

        case ('V'): // ATV - Display current firmware verions
            char currentVersion[21];
            getFirmwareVersion(currentVersion, sizeof(currentVersion));
            systemPrintf("%s", currentVersion);
            return true;

        case ('W'):                  // ATW - Write parameters to the flash memory
            settings = tempSettings; // Apply user's modifications to settings struct
            recordSystemSettings();  // Record current settings struct to NVM
            // If the user changes the temp settings after this, they are applied, but not recorded to NVM
            return true;

        case ('X'): // ATX - Exit command mode
            wifiStop();
            inCommandMode = false;   // Return to printing normal RF serial data
            settings = tempSettings; // Apply user's modifications

            ledStatusOff();
            ledConnectOff();

            // The LED state may have changed while in config mode
            if (bluetoothConnected() == true)
                ledState = LED_CONNECTED;
            else
                ledState = oldLedState; // Return to previous state
            return true;

        case ('Z'): // ATZ - Reboots the system
            reportOK();
            commandReset();
            return true;
        }
    }

    // Invalid command
    return false;
}

//----------------------------------------
//  Command prefix table
//----------------------------------------

const COMMAND_PREFIX prefixTable[] = {
    {"ATA", commandDisplayAll},
    {"ATB", commandDisplayBluetooth},
    {"ATD", commandDisplayDebug},
    {"ATS", commandDisplaySerial},
    {"ATY", commandDisplaySystem},
    {"AT-", commandSetByName},
    {"AT", commandAT},
};

const int prefixCount = sizeof(prefixTable) / sizeof(prefixTable[0]);

//----------------------------------------
//  Command processing routine
//----------------------------------------

// Check to see if a valid command has been received
void checkCommand()
{
    char *commandString;
    int index;
    int prefixLength;
    uint16_t responseLength;
    bool success;

    // Zero terminate the string
    success = false;
    commandBuffer[commandLength] = 0;

    // Remove any whitespace
    commandString = trimCommand();

    // Upper case the command
    for (index = 0; index < commandLength; index++)
    {
        if (commandString[index] == '=')
            break; // Stop caps after equals
        commandString[index] = toupper(commandString[index]);
    }

    // Echo the command
    systemPrintln(commandString);

    // Verify the command length
    if (commandLength >= 2)
    {
        // Locate the correct processing routine for the command prefix
        for (index = 0; index < prefixCount; index++)
        {
            // Locate the prefix
            prefixLength = strlen(prefixTable[index].prefix);
            if (strncmp(commandString, prefixTable[index].prefix, prefixLength) != 0)
                continue;

            // Process the command
            success = prefixTable[index].processCommand(commandString);
            break;
        }
    }
    else if (!commandLength)
        success = true;

    // Print the command failure
    if (success)
        reportOK();
    else
    {
        systemPrintln("ERROR");
    }

    systemFlush();
    commandLength = 0; // Get ready for next command
}

// Indicate successful command completion
void reportOK()
{
    systemPrintln("OK");
}

// Notify the host of the reset then reboot the system
void commandReset()
{
    systemFlush();
    ESP.restart();
}

// Remove any preceeding or following whitespace chars
char *trimCommand()
{
    int index;
    int j;

    // Remove the comment
    for (index = 0; index < commandLength; index++)
    {
        if (commandBuffer[index] == '#')
        {
            commandBuffer[index] = 0;
            commandLength = index;
            break;
        }
    }

    // Remove the white space
    for (index = 0; index < commandLength; index++)
    {
        while (isspace(commandBuffer[index]))
        {
            for (j = index + 1; j < commandLength; j++)
                commandBuffer[j - 1] = commandBuffer[j];
            commandBuffer[--commandLength] = 0;
        }
    }
    return commandBuffer;
}

// Display all of the commands
bool commandDisplayAll(const char *commandString)
{
    displayParameters(0, false);
    return true;
}

// Display only the Bluetooth commands
bool commandDisplayBluetooth(const char *commandString)
{
    displayParameters('B', false);
    return true;
}

// Display only the debugging commands
bool commandDisplayDebug(const char *commandString)
{
    displayParameters('D', false);
    return true;
}

// Display only the serial commands
bool commandDisplaySerial(const char *commandString)
{
    displayParameters('S', false);
    return true;
}

// Display only the system commands
bool commandDisplaySystem(const char *commandString)
{
    displayParameters('Y', false);
    return true;
}

//----------------------------------------
//  Data validation routines
//----------------------------------------

// Validate an integer value
bool valInt(void *value, uint32_t valMin, uint32_t valMax)
{
    uint32_t settingValue = *(uint32_t *)value;

    return ((settingValue >= valMin) && (settingValue <= valMax));
}

// Validate a single char
bool valChar(void *value, uint32_t valMin, uint32_t valMax)
{
    char settingValue = *(char *)value;

    return (settingValue >= ' ' && settingValue <= '~' && settingValue != '\\'); // Exclude \ from allowed chars
}

// Validate the length of the string
bool valString(void *value, uint32_t valMin, uint32_t valMax)
{
    char *str = (char *)value;

    unsigned int length = strlen(str);
    if (length < valMin)
        return false;
    if (length > valMax)
        return false;

    return true;
}

// Validate the SerialSpeed value
bool valSpeedSerial(void *value, uint32_t valMin, uint32_t valMax)
{
    uint32_t settingValue = *(uint32_t *)value;

    return ((settingValue == 2400) || (settingValue == 4800) || (settingValue == 9600) || (settingValue == 14400) ||
            (settingValue == 19200) || (settingValue == 38400) || (settingValue == 57600) || (settingValue == 115200) ||
            (settingValue == 115200 * 2) || (settingValue == 115200 * 4) || (settingValue == 115200 * 8));
}

// Validate a MAC address entry
// A valid entry has 5 colons and 6 hex values - AA:BB:CC:DD:EE:FF
bool valMac(void *value, uint32_t valMin, uint32_t valMax)
{
    char *str = (char *)value;

    int macLength = strlen("00:00:00:00:00:00");

    unsigned int length = strlen(str);

    if (length == 0)
    {
        strncpy(str, "00:00:00:00:00:00", macLength); // Zero out the MAC address to mark it as unpaired
        return (true);
    }

    if (length == 1 && str[0] == '0')
    {
        strncpy(str, "00:00:00:00:00:00", macLength); // Zero out the MAC address to mark it as unpaired
        return (true);
    }

    if (length < macLength)
        return (false);
    if (length > macLength)
        return (false);

    // Check for HEX values and colons
    for (int x = 0; x < length; x++)
    {
        // Check colons
        if (x == 2 || x == 5 || x == 8 || x == 11 || x == 14)
        {
            if (str[x] != ':')
                return (false);
        }
        else // Check hex digit
        {
            if (isxdigit(str[x]) == false)
                return (false);
        }
    }

    return true;
}

//----------------------------------------
//  ATSxx routines
//----------------------------------------

// Display a command
void commandDisplay(const COMMAND_ENTRY *command)
{
    // Print the setting value
    switch (command->type)
    {
    case TYPE_BOOL:
        systemPrint((uint8_t)(*(bool *)(command->setting)));
        break;
    case TYPE_FLOAT:
        systemPrint(*((float *)(command->setting)), command->digits);
        break;
    case TYPE_STRING:
        displayString((char *)(command->setting));
        break;
    case TYPE_CHAR:
        displayChar((char *)(command->setting));
        break;
    case TYPE_U8:
        systemPrint(*(uint8_t *)(command->setting));
        break;
    case TYPE_U16:
        systemPrint(*(uint16_t *)(command->setting));
        break;
    case TYPE_SPEED_SERIAL:
    case TYPE_U32:
        systemPrint(*(uint32_t *)(command->setting));
        break;
    case TYPE_MAC: {
        bool deviceIsPaired = false;

        // Check that the MAC is > 0
        for (int x = 0; x < 6; x++)
        {
            if (tempSettings.btPairedMac[x] > 0)
            {
                deviceIsPaired = true;
                break;
            }
        }
        if (deviceIsPaired == true)
            displayString(stringMac((uint8_t *)command->setting));
    }
    break;
    default:
        systemPrintln("Unknown type");
        break;
    }
    systemPrintln();
}

// Display a string setting
void displayString(char *toPrint)
{
    for (uint8_t x = 0; x < strlen(toPrint); x++)
        systemWrite(toPrint[x]);
}

// Display a single char
void displayChar(char *toPrint)
{
    systemWrite(toPrint[0]);
}

// Set or display the parameter by name
bool commandSetByName(const char *commandString)
{
    const char *buffer;
    const COMMAND_ENTRY *command;
    int index;
    int nameLength;
    int number;
    const char *param;
    int paramLength;
    int table;

    // Determine the parameter name length
    param = &commandString[3];
    buffer = param;
    paramLength = 0;
    while (*buffer && (*buffer != '=') && (*buffer != '?'))
    {
        buffer++;
        paramLength += 1;
    }

    command = NULL;
    for (index = 0; index < commandCount; index++)
    {
        nameLength = strlen(commands[index].name);
        if (nameLength == paramLength)
        {
            // Compare the parameter names
            if (strnicmp(param, commands[index].name, nameLength) == 0)
            {
                command = &commands[index];
                break;
            }
        }
    }

    // Verify that the parameter was found
    if (!command)
        // Report the error
        return false;

    // Process this command
    return commandSetOrDisplayValue(command, buffer);
}

// Set or display the command
bool commandSetOrDisplayValue(const COMMAND_ENTRY *command, const char *buffer)
{
    const char *digit;
    double doubleSettingValue;
    uint32_t settingValue;
    bool valid;

    do
    {
        // Is this a display request
        if ((*buffer == 0) || (strcmp(buffer, "?") == 0))
        {
            commandDisplay(command);
            return true;
        }

        // Make sure the command has the proper syntax
        if (*buffer++ != '=')
            break;

        // Verify the input value
        for (digit = buffer; *digit != 0; digit++)
            if ((*digit < '0') || (*digit > '9'))
            {
                // Floating point values may contain a decimal point
                if ((command->type == TYPE_FLOAT) && (*digit == '.'))
                    continue;

                // Strings may only contain visible ASCII
                if (command->type == TYPE_STRING || command->type == TYPE_CHAR)
                {
                    if (*digit >= ' ' && *digit <= '~' && *digit != '\\') // Exclude \ character
                        continue;
                }

                // MACs can contain HEX or colons
                if (command->type == TYPE_MAC)
                {
                    if (isxdigit(*digit) || *digit == ':')
                        continue;
                }
                break;
            }
        if (*digit)
            break;

        // Get the value
        doubleSettingValue = strtod(buffer, NULL);
        settingValue = doubleSettingValue;

        // Validate and set the value
        valid = false;
        switch (command->type)
        {
        case TYPE_BOOL:
            valid = command->validate((void *)&settingValue, command->minValue, command->maxValue);
            if (valid)
                *(bool *)(command->setting) = (bool)settingValue;
            break;
        case TYPE_FLOAT:
            valid = command->validate((void *)&doubleSettingValue, command->minValue, command->maxValue);
            if (valid)
                *((float *)(command->setting)) = doubleSettingValue;
            break;
        case TYPE_STRING:
            valid = command->validate((void *)buffer, command->minValue, command->maxValue);
            if (valid)
                strcpy((char *)(command->setting), buffer);
            break;
        case TYPE_CHAR:
            valid = command->validate((void *)buffer, command->minValue, command->maxValue);
            if (valid)
                *(char *)(command->setting) = buffer[0];
            break;
        case TYPE_SPEED_SERIAL:
        case TYPE_U32:
            valid = command->validate((void *)&settingValue, command->minValue, command->maxValue);
            if (valid)
                *(uint32_t *)(command->setting) = settingValue;
            break;
        case TYPE_U8:
            valid = command->validate((void *)&settingValue, command->minValue, command->maxValue);
            if (valid)
                *(uint8_t *)(command->setting) = (uint8_t)settingValue;
            break;
        case TYPE_U16:
            valid = command->validate((void *)&settingValue, command->minValue, command->maxValue);
            if (valid)
                *(uint16_t *)(command->setting) = (uint16_t)settingValue;
            break;
        case TYPE_MAC:
            valid = command->validate((void *)buffer, command->minValue, command->maxValue);
            if (valid)
                convertMac((char *)buffer, (uint8_t *)(command->setting));
            break;
        }
        if (valid == false)
            break;

        // See if this command requires a radio reset to be applied
        if (valid && command->forceRadioReset)
            forceRadioReset = true;

        // The parameter was successfully set
        return true;
    } while (0);

    // Report the error
    return false;
}

// Show current settings in user friendly way
void displayParameters(char letter, bool displayAll)
{
    int index;
    uint8_t sortOrder[commandCount];
    uint8_t temp;
    int x;

    // Set the default sort order
    for (index = 0; index < commandCount; index++)
        sortOrder[index] = index;

    // Perform a bubble sort if requested
    for (index = 0; index < commandCount; index++)
        for (x = index + 1; x < commandCount; x++)
            if (stricmp(commands[sortOrder[index]].name, commands[sortOrder[x]].name) > 0)
            {
                temp = sortOrder[index];
                sortOrder[index] = sortOrder[x];
                sortOrder[x] = temp;
            }

    // Print the parameters
    for (index = 0; index < commandCount; index++)
    {
        if (displayAll || (letter == commands[sortOrder[index]].letter) ||
            ((letter == 0) && (!commands[sortOrder[index]].requireAll)))
        {
            systemPrint("A");
            systemPrint("T-");
            systemPrint(commands[sortOrder[index]].name);
            systemPrint("=");
            commandDisplay(&commands[sortOrder[index]]);
        }
    }
}
