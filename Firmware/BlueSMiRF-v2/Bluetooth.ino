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
    }

    if (strlen(settings.btNickname) == 0)
    {
        // Default to 'BlueSMiRF-BC61'
        snprintf(settings.btNickname, sizeof(settings.btNickname), "%s-%02X%02X", platformPrefix, btMACAddress[4],
                 btMACAddress[5]);
    }

    snprintf(broadcastName, sizeof(broadcastName), "%s", settings.btNickname);

    if (settings.debugBluetooth == true)
    {
        systemPrintf("Broadcast name: %s\r\n", broadcastName);
        systemPrintf("settings.btRxSize: %d\r\n", settings.btRxSize);
        systemPrintf("settings.btTxSize: %d\r\n", settings.btTxSize);
    }

    // Check for pairing/discovery work around flag
    if (settings.btPairOnStartup == true)
    {
        if (settings.debugBluetooth)
            systemPrintln("Restarting pairing due to reset work around");

        settings.btPairOnStartup = false;
        recordSystemSettings();

        // Start BT in passive mode
        if (bluetoothSerial->begin(broadcastName, false, settings.btRxSize, settings.btTxSize) ==
            false) // localName, isMaster, rxBufferSize, txBufferSize
        {
            systemPrintln("An error occurred initializing Bluetooth");
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
            return;
        }

        // If we fail to connect, fall through and start general Bluetooth
    }

    // Start BT in passive mode
    if (bluetoothSerial->begin(broadcastName, false, settings.btRxSize, settings.btTxSize) ==
        false) // localName, isMaster, rxBufferSize, txBufferSize
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

    if (settings.debugBluetooth)
    {
        systemPrint("Bluetooth broadcasting as: ");
        systemPrintln(broadcastName);
    }

    bluetoothStartTasks();

    bluetoothState = BT_NOTCONNECTED;
    ledState = LED_NOTCONNECTED;
#else
    ledState = LED_OFF;
    systemPrintln("Bluetooth not compiled");
#endif
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
        systemPrintf("Connecting to %s", stringMac(macAddress));

    ledState = LED_CONNECTING;

    for (int x = 0; x < maxTries; x++)
    {
        if (settings.debugBluetooth == true)
            systemPrintf("Try #%d\r\n", x + 1);

        bluetoothSerial->end();

        // Move to master mode with buffers
        if (bluetoothSerial->begin("BlueSMiRF-Paired", true, settings.btRxSize, settings.btTxSize) == false)
        {
            systemPrintln("An error occurred initializing Bluetooth in master mode");
            return (false);
        }

        // After discovery, if we immediately try to connect, it will always fail
        // If we wait 250ms, it works ~50% of the time, and usually connects on 2nd attempt
        delay(250);

        // remoteAddress, channel, sec_mask, role, connectTimeout
        if (bluetoothSerial->connect(macAddress, 0, (ESP_SPP_SEC_ENCRYPT | ESP_SPP_SEC_AUTHENTICATE),
                                     ESP_SPP_ROLE_MASTER, settings.btConnectTimeoutMs) == true)
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

// Attempt to connect to a given radio Name
// Returns true if successful
bool connectToDeviceName(char *deviceName, int maxTries)
{
#ifdef COMPILE_BT
    if (settings.debugBluetooth == true)
        systemPrintf("Connecting to %s", deviceName);

    ledState = LED_CONNECTING;

    for (int x = 0; x < maxTries; x++)
    {
        if (settings.debugBluetooth == true)
            systemPrintf("Try #%d\r\n", x + 1);

        bluetoothSerial->end();

        // Move to master mode with buffers
        if (bluetoothSerial->begin("BlueSMiRF-Paired", true, settings.btRxSize, settings.btTxSize) == false)
        {
            systemPrintln("An error occurred initializing Bluetooth in master mode");
            return (false);
        }

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
        bluetoothState = BT_CONNECTED;
        ledState = LED_CONNECTED;
    }

    if (event == ESP_SPP_CLOSE_EVT)
    {
        if (settings.debugBluetooth)
            systemPrintln("BT client disconnected");

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

void btAdvertisedDeviceFound(BTAdvertisedDevice *pDevice)
{
    if (settings.debugBluetooth == true)
        systemPrintf("Found a device Name: %s\n\r", pDevice->getName().c_str());

    // Only pair with devices that have the name "BlueSMiRF-Pairing"
    if (strcmp(pDevice->getName().c_str(), "BlueSMiRF-Pairing") == 0)
    {
        // Convert "94:e6:86:b6:89:0a" to {0x94, 0xE6, 0x86, 0xB6, 0x89, 0x0A}
        convertMac((char *)pDevice->getAddress().toString().c_str(), settings.btPairedMac);

        recordSystemSettings(); // Store this MAC

        if (settings.debugBluetooth == true)
            systemPrintf("Found a friendly device MAC: %s", stringMac(settings.btPairedMac));

        friendlyDeviceFound = true; // Indicate we can stop scanning
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

    // Move to passive mode with buffers
    bluetoothSerial->begin("BlueSMiRF-Pairing", false, settings.btRxSize, settings.btTxSize);

    if (settings.debugBluetooth == true)
        systemPrintln("Device now discoverable as BlueSMiRF-Pairing");

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

    // TODO if user exits pairing mode, we need to do so gracefully

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

bool bluetoothConnected()
{
#ifdef BT_COMPILE
    if (bluetoothSerial->connected())
        return (true);
#endif
    return (false);
}