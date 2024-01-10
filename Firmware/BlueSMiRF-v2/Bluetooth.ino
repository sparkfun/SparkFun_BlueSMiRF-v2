static volatile BTState bluetoothState = BT_OFF;

#ifdef COMPILE_BT
BTSerialInterface *bluetoothSerial = nullptr;
#endif

// Determine if we are waiting for an incoming connection or initiating a paired connection
void bluetoothBegin()
{
#ifdef COMPILE_BT
    ledState = LED_BLUETOOTH_STARTING;

    if (bluetoothSerial == nullptr)
    {
        // Create object
        // Select Bluetooth setup
        if (settings.btType == BLUETOOTH_RADIO_OFF)
            return;
        else if (settings.btType == BLUETOOTH_RADIO_SPP)
            bluetoothSerial = new BTClassicSerial();
        else if (settings.btType == BLUETOOTH_RADIO_BLE)
            bluetoothSerial = new BTLESerial();
        else
            systemPrintln("Error: Unknown Bluetooth setting");
    }

    if (strlen(settings.btNickname) == 0)
    {
        // Default to 'BlueSMiRF-BC61'
        snprintf(settings.btNickname, sizeof(settings.btNickname), "%s-%02X%02X", platformPrefix, btMACAddress[4],
                 btMACAddress[5]);
    }

    char bluetoothTypeString[10] = "";
    if (settings.btType == BLUETOOTH_RADIO_BLE)
        strcpy(bluetoothTypeString, "-BLE");

    snprintf(broadcastName, sizeof(broadcastName), "%s%s", settings.btNickname, bluetoothTypeString);

    // https://stackoverflow.com/questions/51534284/how-to-circumvent-format-truncation-warning-in-gcc
    snprintf(broadcastNamePaired, sizeof(broadcastNamePaired), "%s%s-Paired", broadcastName, bluetoothTypeString) < 0
        ? snprintfAbort()
        : (void)0;
    snprintf(broadcastNameConnected, sizeof(broadcastNameConnected), "%s%s-Connected", broadcastName,
             bluetoothTypeString) < 0
        ? snprintfAbort()
        : (void)0; // BlueSMiRF-50AF-Connected

    if (settings.debugBluetooth == true)
    {
        systemPrintf("Broadcast name: %s\r\n", broadcastName);
        systemPrintf("settings.btRxSize: %d\r\n", settings.btRxSize);
        systemPrintf("settings.btTxSize: %d\r\n", settings.btTxSize);
    }

    // Start BT
    bluetoothStartRadio();

    // Check for pairing/discovery work around flag
    if (settings.btPairOnStartup == true)
    {
        if (settings.debugBluetooth)
            systemPrintln("Restarting pairing due to reset work around");

        settings.btPairOnStartup = false;
        recordSystemSettings();

        // Broadcast the standard name
        if (bluetoothSetBroadcastName(broadcastName) == false)
        {
            systemPrintln("An error occurred initializing Bluetooth in paired mode");
            return;
        }

        // User has initiated pairing. Begin pairing process before connecting.
        bluetoothBeginPairing();
        return;
    }

    // If this device has been paired (with a valid MAC), attempt to connect to mate's MAC
    else if (deviceIsPairedMac() == true && settings.btType == BLUETOOTH_RADIO_SPP)
    {
        // Attempt to connect to remote device
        if (connectToDeviceMac(settings.btPairedMac, settings.btConnectRetries) == true)
        {
            bluetoothStartTasks();
            bluetoothState = BT_CONNECTED;
            ledState = LED_CONNECTED;

            // Change broadcast name to '-Paired'
            if (bluetoothSetBroadcastName(broadcastNamePaired) == false)
                systemPrintln("An error occurred setting broadcast name");

            return;
        }

        // If we fail to connect, fall through and start general Bluetooth
    }
    // If this device has been paired (with a valid MAC), attempt to connect to mate's MAC
    else if (deviceIsPairedName() == true && settings.btType == BLUETOOTH_RADIO_SPP)
    {
        // Attempt to connect to remote device
        if (connectToDeviceName(settings.btPairedName, settings.btConnectRetries) == true)
        {
            bluetoothStartTasks();
            bluetoothState = BT_CONNECTED;
            ledState = LED_CONNECTED;

            // Change broadcast name to '-Paired'
            if (bluetoothSetBroadcastName(broadcastNamePaired) == false)
                systemPrintln("An error occurred setting broadcast name");

            return;
        }

        // If we fail to connect, fall through and start general Bluetooth
    }

    // Start BT in passive mode
    if (bluetoothSetBroadcastName(broadcastName) == false)
    {
        systemPrintln("An error occurred initializing Bluetooth");
        return;
    }

    // Set PIN so we can connect to older BT devices, but not require a PIN for modern device pairing
    // See issue: https://github.com/sparkfun/SparkFun_RTK_Firmware/issues/5
    // https://github.com/espressif/esp-idf/issues/1541
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    esp_bt_sp_param_t param_type = ESP_BT_SP_IOCAP_MODE;

    esp_bt_io_cap_t iocap = ESP_BT_IO_CAP_NONE; // Requires pin 1234 on old BT dongle, No prompt on new BT dongle

    esp_bt_gap_set_security_param(param_type, &iocap, sizeof(uint8_t));

    esp_bt_pin_type_t pin_type = ESP_BT_PIN_TYPE_FIXED;
    esp_bt_pin_code_t pin_code;
    pin_code[0] = settings.btPin[0];
    pin_code[1] = settings.btPin[1];
    pin_code[2] = settings.btPin[2];
    pin_code[3] = settings.btPin[3];
    esp_bt_gap_set_pin(pin_type, 4, pin_code);
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    bluetoothStartTasks();

    bluetoothState = BT_NOTCONNECTED;
    ledState = LED_NOTCONNECTED;
#else
    ledState = LED_OFF;
    systemPrintln("Bluetooth not compiled");
#endif
}

// Change the name that is being broadcast over Bluetooth
bool bluetoothSetBroadcastName(char *castName)
{
    // at-bluetoothnickname=MyReallyLongNameToBreakTheFirmware
    // at-bluetoothnickname=MyReallyLongNameToBreakTheFir
    // at-bluetoothtype=1
    // at-bluetoothtype=0

    // For SPP, if a name is more than 32 characters, it will revert to "ESP32"
    // For BleSerial, if a name is more than 29 characters, device will reset
    // Shorten if needed.
    if (strlen(castName) > 29)
    {
        if (settings.debugBluetooth == true)
            systemPrintf("Warning! The Bluetooth device name '%s' is %d characters long and will not be fully "
                         "displayed.\r\n",
                         castName, strlen(castName));

        castName[29] = '\0'; // Truncate

        if (settings.debugBluetooth == true)
            systemPrintf("Truncated castName: %s\r\n", castName);
    }

    // To change the name during SPP, we do a new begin()
    if (settings.btType == BLUETOOTH_RADIO_SPP)
    {
        // localName, isMaster, rxBufferSize, txBufferSize)
        bool response = bluetoothSerial->begin(castName, false, settings.btRxSize, settings.btTxSize);

        if (response == true)
        {
            if (settings.debugBluetooth == true)
            {
                systemPrint("Bluetooth broadcast name set to: ");
                systemPrintln(castName);
            }

            return (true);
        }
        else
        {
            if (settings.debugBluetooth == true)
                systemPrintln("Bluetooth SPP name change failed");
        }
    }

    // To change the name during BLE, we use esp_ble_gap_set_device_name
    else if (settings.btType == BLUETOOTH_RADIO_BLE)
    {
        esp_err_t response = esp_ble_gap_set_device_name(castName);

        if (response == ESP_OK)
        {
            if (settings.debugBluetooth)
            {
                systemPrint("Bluetooth broadcasting as: ");
                systemPrintln(castName);
            }
            return (true);
        }
    }

    return (false);
}

// Start the bluetooth stack
void bluetoothStartRadio()
{
    bluetoothStartRadio(broadcastName); // Default
}

void bluetoothStartRadio(char *castName)
{
    // For both SPP and BLE, we use begin
    // but BLE cannot be begin() multiple times
    if (bluetoothState == BT_OFF)
    {
        // For SPP, if a name is more than 32 characters, it will revert to "ESP32"
        // For BleSerial, if a name is more than 29 characters, device will reset
        // Shorten if needed.
        if (strlen(castName) > 29)
        {
            if (settings.debugBluetooth == true)
                systemPrintf("Warning! The Bluetooth device name '%s' is %d characters long and will not be fully "
                             "displayed.\r\n",
                             castName, strlen(castName));

            castName[29] = '\0'; // Truncate

            if (settings.debugBluetooth == true)
                systemPrintf("Truncated castName: %s\r\n", castName);
        }

        // localName, isMaster, rxBufferSize, txBufferSize)
        bool response = bluetoothSerial->begin(castName, false, settings.btRxSize, settings.btTxSize);

        if (response == true)
        {
            if (settings.debugBluetooth == true)
                systemPrintln("Bluetooth started");

            bluetoothState = BT_NOTCONNECTED;
        }
    }
}

// A throw-away function for snprintf warning suppression
void snprintfAbort()
{
    if (settings.debugBluetooth == true)
    {
        systemPrintln("snprintf error");
    }
}

void bluetoothStartTasks()
{
#ifdef COMPILE_BT
    bluetoothSerial->register_callback(bluetoothCallback); // Controls Bluetooth state machine
    bluetoothSerial->setTimeout(settings.btTimeout);

    // Reads data from Bluetooth and sends to serialTransmitBuffer
    if (btReadTaskHandle == nullptr)
        xTaskCreatePinnedToCore(btReadTask,                  // Function to call
                                "btRead",                    // Just for humans
                                btReadTaskStackSize,         // Stack Size
                                nullptr,                     // Task input parameter
                                settings.btReadTaskPriority, // Priority
                                &btReadTaskHandle,           // Task handle
                                settings.btReadTaskCore);    // Core where task should run, 0=core, 1=Arduino

    if (btWriteTaskHandle == nullptr)
        xTaskCreatePinnedToCore(btWriteTask,                  // Function to call
                                "btWrite",                    // Just for humans
                                btWriteTaskStackSize,         // Stack Size
                                nullptr,                      // Task input parameter
                                settings.btWriteTaskPriority, // Priority
                                &btWriteTaskHandle,           // Task handle
                                settings.btWriteTaskCore);    // Core where task should run, 0=core, 1=Arduino
#endif
}

// Attempt to connect to a given MAC
// Returns true if successful
bool connectToDeviceMac(uint8_t *macAddress, int maxTries)
{
#ifdef COMPILE_BT
    if (settings.debugBluetooth == true)
        systemPrintf("Connecting to MAC: %s", stringMac(macAddress));

    ledState = LED_CONNECTING;

    for (int x = 0; x < maxTries; x++)
    {
        if (settings.debugBluetooth == true)
            systemPrintf("Try #%d\r\n", x + 1);

        bluetoothSerial->end();

        // Start BT in master mode with the name '-Paired'
        if (bluetoothSerial->begin(broadcastNamePaired, true, settings.btRxSize, settings.btTxSize) == false)
        {
            systemPrintln("An error occurred initializing Bluetooth in master mode");
            return (false);
        }

        bluetoothState = BT_NOTCONNECTED;

        // After discovery, if we immediately try to connect, it will always fail
        // If we wait 250ms, it works ~50% of the time, and usually connects on 2nd attempt
        delay(250);

        // remoteAddress, channel, sec_mask, role, connectTimeout
        if (bluetoothSerial->connect(macAddress, 0, (ESP_SPP_SEC_ENCRYPT | ESP_SPP_SEC_AUTHENTICATE),
                                     ESP_SPP_ROLE_MASTER, settings.btConnectTimeoutMs) == true)
        {
            if (settings.debugBluetooth == true)
                systemPrintln("Connected!");

            bluetoothState = BT_CONNECTED;
            return (true);
        }
    }

    if (settings.debugBluetooth == true)
        systemPrintln("Failed to connect to paired device.");

    bluetoothSerial->end(); // Release all resources

    return (false);
#else  // COMPILE_BT
    systemPrintln("Bluetooth not compiled.");
    return (false);
#endif // COMPILE_BT
}

// Attempt to connect to a given radio Name
// Returns true if successful
bool connectToDeviceName(char *deviceName, int maxTries)
{
#ifdef COMPILE_BT
    if (settings.debugBluetooth == true)
        systemPrintf("Connecting to name: %s", deviceName);

    ledState = LED_CONNECTING;

    for (int x = 0; x < maxTries; x++)
    {
        if (settings.debugBluetooth == true)
            systemPrintf("Try #%d\r\n", x + 1);

        bluetoothSerial->end();

        // Start BT in master mode with the name '-Paired'
        if (bluetoothSerial->begin(broadcastNamePaired, true, settings.btRxSize, settings.btTxSize) == false)
        {
            systemPrintln("An error occurred initializing Bluetooth in master mode");
            return (false);
        }

        bluetoothState = BT_NOTCONNECTED;

        // After discovery, if we immediately try to connect, it will always fail
        // If we wait 250ms, it works ~50% of the time, and usually connects on 2nd attempt
        delay(250);

        // remoteName, scanTimeoutMs
        if (bluetoothSerial->connect(deviceName, settings.btConnectTimeoutMs) == true)
        {
            if (settings.debugBluetooth == true)
                systemPrintln("Connected!");
            return (true);
        }
    }

    if (settings.debugBluetooth == true)
        systemPrintln("Failed to connect to paired device.");

    bluetoothSerial->end(); // Release all resources

    return (false);
#else  // COMPILE_BT
    systemPrintln("Bluetooth not compiled.");
    return (false);
#endif // COMPILE_BT
}

#ifdef COMPILE_BT

// Call back for when BT connection event happens (connected/disconnect)
// Used for updating the bluetoothState state machine
void bluetoothCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
{
    if (event == ESP_SPP_SRV_OPEN_EVT)
    {
        if (settings.debugBluetooth)
            systemPrintln("BT client Connected");

        // Do not rename BLE radio during connect
        if (settings.btType == BLUETOOTH_RADIO_SPP)
        {
            // Rename the device to *-Connected
            if (bluetoothSetBroadcastName(broadcastNameConnected) == false)
            {
                systemPrintln("An error occurred renaming Bluetooth");
                return;
            }
        }

        bluetoothState = BT_CONNECTED;
        ledState = LED_CONNECTED;
    }

    if (event == ESP_SPP_CLOSE_EVT)
    {
        if (settings.debugBluetooth)
            systemPrintln("BT client disconnected");

        // Rename the device to default broadcast name
        if (bluetoothSetBroadcastName(broadcastName) == false)
        {
            systemPrintln("An error occurred renaming Bluetooth");
            return;
        }

        btPrintEcho = false;
        btPrintEchoExit = true; // Force exit command mode
        printEndpoint = PRINT_ENDPOINT_SERIAL;

        bluetoothState = BT_NOTCONNECTED;
        ledState = LED_NOTCONNECTED;
    }
}

#endif // COMPILE_BT

// This function stops BT so that it can be restarted later
// It also releases as much system resources as possible so that WiFi/caster is more stable
void bluetoothStop()
{
#ifdef COMPILE_BT
    if (bluetoothState == BT_NOTCONNECTED || bluetoothState == BT_CONNECTED)
    {
        bluetoothSerial->register_callback(nullptr);
        bluetoothSerial->flush();      // Complete any transfers
        bluetoothSerial->disconnect(); // Drop any clients
        bluetoothSerial->end();        // bluetoothSerial->end() will release significant RAM (~100k!) but a
                                       // bluetoothSerial->start will crash.

        // Stop tasks
        if (btReadTaskHandle != nullptr)
        {
            vTaskDelete(btReadTaskHandle);
            btReadTaskHandle = nullptr;
        }
        if (btWriteTaskHandle != nullptr)
        {
            vTaskDelete(btWriteTaskHandle);
            btWriteTaskHandle = nullptr;
        }

        if (settings.debugBluetooth)
            systemPrintln("Bluetooth turned off");

        bluetoothState = BT_OFF;
        reportHeapNow();
    }
#endif // COMPILE_BT
}

// Return the Bluetooth state
byte bluetoothGetState()
{
#ifdef COMPILE_BT
    return bluetoothState;
#else  // COMPILE_BT
    return BT_OFF;
#endif // COMPILE_BT
}

// Read data from the Bluetooth device
int bluetoothRead(uint8_t *buffer, int length)
{
#ifdef COMPILE_BT
    return bluetoothSerial->readBytes(buffer, length);
#else  // COMPILE_BT
    return 0;
#endif // COMPILE_BT
}

// Read data from the Bluetooth device
uint8_t bluetoothRead()
{
#ifdef COMPILE_BT
    return bluetoothSerial->read();
#else  // COMPILE_BT
    return 0;
#endif // COMPILE_BT
}

// Determine if data is available
bool bluetoothDataAvailable()
{
#ifdef COMPILE_BT
    return bluetoothSerial->available();
#else  // COMPILE_BT
    return false;
#endif // COMPILE_BT
}

// Write data to the Bluetooth device
int bluetoothWrite(const uint8_t *buffer, int length)
{
#ifdef COMPILE_BT
    // BLE write does not handle 0 length requests correctly
    if (length > 0)
        return bluetoothSerial->write(buffer, length);
    else
        return 0;
#else  // COMPILE_BT
    return 0;
#endif // COMPILE_BT
}

// Write data to the Bluetooth device
int bluetoothWrite(uint8_t value)
{
#ifdef COMPILE_BT
    return bluetoothSerial->write(value);
#else  // COMPILE_BT
    return 0;
#endif // COMPILE_BT
}

// Flush Bluetooth device
void bluetoothFlush()
{
#ifdef COMPILE_BT
    bluetoothSerial->flush();
#else  // COMPILE_BT
    return;
#endif // COMPILE_BT
}

// Break string MAC into six uint_8's
// Convert "94:e6:86:b6:89:0a" to {0x94, 0xE6, 0x86, 0xB6, 0x89, 0x0A}
// Based on https://forum.arduino.cc/t/conversion-of-mac-addresses-string-to-uint8-t-array-for-esp-now/857512/5
void convertMac(char *charMac, uint8_t *convertedMac)
{
    for (int i = 0; i < 6; ++i)
    {
        int idx = i * 3;
        sscanf(charMac + idx, "%02x", (unsigned int *)&convertedMac[i]);
    }
}

// Pretty print a uint_8 array to MAC
char *stringMac(uint8_t *macAddress)
{
    int macSize = strlen("00:00:00:00:00:00");
    char *str = (char *)malloc(macSize + 1);
    snprintf(str, macSize + 1, "%02X:%02X:%02X:%02X:%02X:%02X", macAddress[0], macAddress[1], macAddress[2],
             macAddress[3], macAddress[4], macAddress[5]);
    return str;
}

// If we have a valid MAC, return true
// Used to enter connect mode at power-up
bool deviceIsPairedMac()
{
    // Check that the MAC is > 0
    for (int x = 0; x < 6; x++)
    {
        if (settings.btPairedMac[x] > 0)
            return (true);
    }

    return (false);
}

// If we have a valid Name, return true
// Used to enter connect mode at power-up
bool deviceIsPairedName()
{
    // Check that the Name is longer than 0
    if (strlen(settings.btPairedName) > 0)
        return (true);

    return (false);
}

// Look for devices called "BlueSMiRF-Pairing"
// Return true if MAC address has been obtained/stored
bool scanForFriendlyDevices(uint16_t maxScanTimeMs)
{
#ifdef COMPILE_BT
    // Select Bluetooth setup
    if (settings.btType == BLUETOOTH_RADIO_OFF)
        return (false);
    else if (settings.btType == BLUETOOTH_RADIO_SPP)
        bluetoothSerial = new BTClassicSerial();
    else if (settings.btType == BLUETOOTH_RADIO_BLE)
    {
        systemPrintln("Discover not supported in BLE mode.");
        return (false);
        // bluetoothSerial = new BTLESerial();
    }

    friendlyDeviceFound = false;

    // Prep LED values for fading
    statusLedBrightness = 0;
    statusFadeAmount = startingFadeAmount;
    ledState = LED_SCANNING;

    if (settings.debugBluetooth == true)
        systemPrintln("Starting discover process");

    if (bluetoothSerial->discoverAsync(btAdvertisedDeviceFound) == false)
    {
        systemPrintln("Error starting discoverAsync");
    }
    else
    {
        // Allow for devices to be found. 2s works, but should probably be longer like 5 or 8 seconds.
        for (int x = 0; x < maxScanTimeMs; x++)
        {
            if (friendlyDeviceFound == true)
            {
                if (settings.debugBluetooth == true)
                    systemPrintf("Friendly device found in %dms\r\n", x);
                break;
            }
            delay(1);
        }

        bluetoothSerial->discoverAsyncStop();
    }

    return (friendlyDeviceFound);
#else
    systemPrintln("Bluetooth not compiled");
    return (false);
#endif
}

#ifdef COMPILE_BT

// The remote device will advertise as 'BlueSMiRF-ABCD-Pairing' during pairing discovery mode
// Look for BlueSMiRF and -Pairing in a name
void btAdvertisedDeviceFound(BTAdvertisedDevice *pDevice)
{
    if (settings.debugBluetooth == true)
        systemPrintf("Found a device Name: %s\n\r", pDevice->getName().c_str());

    char search1[] = "BlueSMiRF";
    char search2[] = "-Pairing";

    char *ptr = strstr(pDevice->getName().c_str(), search1);

    if (ptr != NULL) // Found first search
    {
        char *ptr2 = strstr(pDevice->getName().c_str(), search2);

        if (ptr2 != NULL) // Found
        {
            // Convert "94:e6:86:b6:89:0a" to {0x94, 0xE6, 0x86, 0xB6, 0x89, 0x0A}
            convertMac((char *)pDevice->getAddress().toString().c_str(), settings.btPairedMac);

            recordSystemSettings(); // Store this MAC

            if (settings.debugBluetooth == true)
                systemPrintf("Found a friendly device MAC: %s", stringMac(settings.btPairedMac));

            friendlyDeviceFound = true; // Indicate we can stop scanning
        }
    }
}

#endif

// Restart Bluetooth and broadcast as "BlueSMiRF-Pairing" so that this unit
// can be discovered
void becomeDiscoverable()
{
#ifdef COMPILE_BT
    // Select Bluetooth setup
    if (settings.btType == BLUETOOTH_RADIO_OFF)
        return;
    else if (settings.btType == BLUETOOTH_RADIO_BLE)
    {
        systemPrintln("Discoverable not supported in BLE mode.");
        return;
        // bluetoothSerial = new BTLESerial();
    }

    // Prep LED values for fading
    connectLedBrightness = 0;
    connectFadeAmount = startingFadeAmount;
    ledState = LED_DISCOVERABLE;

    bluetoothSerial->end();

    char broadcastNamePairing[50] = "";

    // During discovery, broadcast as 'BlueSMiRF-BC61-Pairing', regardless of nickname setting
    snprintf(broadcastNamePairing, sizeof(broadcastNamePairing), "BlueSMiRF-%02X%02X-Pairing", btMACAddress[4],
             btMACAddress[5]);

    // Move to passive mode with buffers
    bluetoothSetBroadcastName(broadcastNamePairing);

    if (settings.debugBluetooth == true)
        systemPrintf("Device now discoverable as %s\r\n", broadcastNamePairing);

#else
    ledState = LED_OFF;
    return;
#endif
}

// Start the pairing process
// Scan for friendly devices
// If one is found, initiate a connection
// If one is not found, become discoverable
void bluetoothBeginPairing()
{
    bluetoothState = BT_PAIRING;

    // Look for devices called "BlueSMiRF-Pairing"
    // Return true if MAC address has been obtained/stored
    if (scanForFriendlyDevices(2000) == true)
    {
        // We have a MAC address, restart Bluetooth and it will use it
        bluetoothBegin();
    }
    else
    {
        becomeDiscoverable();
    }
}

// Returns true if a connection is open
bool bluetoothConnected()
{
#ifdef BT_COMPILE
    if (bluetoothSerial->connected())
        return (true);
#endif
    return (false);
}