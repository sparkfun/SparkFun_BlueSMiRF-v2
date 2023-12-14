static volatile BTState bluetoothState = BT_OFF;

#ifdef COMPILE_BT
BTSerialInterface *bluetoothSerial;

// Call back for when BT connection event happens (connected/disconnect)
// Used for updating the bluetoothState state machine
void bluetoothCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
{
    if (event == ESP_SPP_SRV_OPEN_EVT)
    {
        if (settings.debugBluetooth)
            systemPrintln("BT client Connected");
        bluetoothState = BT_CONNECTED;
    }

    if (event == ESP_SPP_CLOSE_EVT)
    {
        if (settings.debugBluetooth)
            systemPrintln("BT client disconnected");

        btPrintEcho = false;
        btPrintEchoExit = true; // Force exit command mode
        printEndpoint = PRINT_ENDPOINT_SERIAL;

        bluetoothState = BT_NOTCONNECTED;
    }
}

#endif // COMPILE_BT

// Get MAC, start radio
// Tack device's MAC address to end of friendly broadcast name
// This allows multiple units to be on at same time
void bluetoothStart()
{
#ifdef COMPILE_BT
    if (bluetoothState == BT_OFF)
    {
        char deviceName[70]; // The serial string that is broadcast. Ex: 'BlueSMiRF-BC61'

        if (strlen(settings.btNickname) == 0)
        {
            // Default to 'BlueSMiRF-BC61'
            snprintf(settings.btNickname, sizeof(settings.btNickname), "%s-%02X%02X", platformPrefix, btMACAddress[4], btMACAddress[5]);
        }

        snprintf(deviceName, sizeof(deviceName), "%s", settings.btNickname);

        // Select Bluetooth setup
        if (settings.btType == BLUETOOTH_RADIO_OFF)
            return;
        else if (settings.btType == BLUETOOTH_RADIO_SPP)
            bluetoothSerial = new BTClassicSerial();
        else if (settings.btType == BLUETOOTH_RADIO_BLE)
            bluetoothSerial = new BTLESerial();

        if (settings.debugBluetooth == true)
        {
            systemPrintf("settings.btRxSize: %d\r\n", settings.btRxSize);
            systemPrintf("settings.btTxSize: %d\r\n", settings.btTxSize);
        }
        
        if (bluetoothSerial->begin(deviceName, false, settings.btRxSize, settings.btTxSize) ==
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

        bluetoothSerial->register_callback(bluetoothCallback); // Controls Bluetooth state machine
        bluetoothSerial->setTimeout(settings.btTimeout);

        if (settings.debugBluetooth)
        {
            systemPrint("Bluetooth broadcasting as: ");
            systemPrintln(deviceName);
        }

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

        bluetoothState = BT_NOTCONNECTED;
    }
#endif // COMPILE_BT
}

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
