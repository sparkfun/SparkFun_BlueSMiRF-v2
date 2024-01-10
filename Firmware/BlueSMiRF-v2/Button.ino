void buttonBegin()
{
    if (pin_pairButton == PIN_UNDEFINED)
        return;

    pinMode(pin_pairButton, INPUT_PULLUP);

    pairButton = new Button(pin_pairButton); // Create the button in memory
    // Allocation failure handled in ButtonCheckTask

    // Starts task for monitoring button presses
    if (ButtonCheckTaskHandle == nullptr)
        xTaskCreate(ButtonCheckTask,
                    "BtnCheck",          // Just for humans
                    buttonTaskStackSize, // Stack Size
                    nullptr,             // Task input parameter
                    ButtonCheckTaskPriority,
                    &ButtonCheckTaskHandle); // Task handle
}

// Check the state of the setup (Pair) button
void ButtonCheckTask(void *e)
{
    if (pairButton != nullptr)
        pairButton->begin();

    if (pairButton == nullptr)
    {
        systemPrintln("Button failed to start");
        while (1) // Park and do nothing
        {
            feedWdt();
            taskYIELD();
        }
    }

    bool buttonPressed = false;
    bool buttonWasPressed = false;
    uint32_t deltaTime;
    uint32_t buttonPressedTime = 0;

    while (true)
    {
        buttonPressed = pairButton->read();

        // Determine the current button state
        if (buttonWasPressed)
        {
            deltaTime = millis() - buttonPressedTime;

            // Check for pair mode or factory reset
            if (deltaTime >= 8000)
            {
                if (ledState != LED_BUTTON_8S_HOLD)
                {
                    // Move to 8s LED state
                    // Setup LEDs for blink back/forth
                    ledStatusOn();
                    ledConnectOff();
                    lastLedUpdate = millis();
                    ledState = LED_BUTTON_8S_HOLD;
                }
            }
            else if (deltaTime >= 3000)
            {
                if (ledState != LED_BUTTON_3S_HOLD)
                {
                    // Move to 3s LED state
                    // Setup LEDs for blink back/forth
                    ledStatusOn();
                    ledConnectOff();
                    lastLedUpdate = millis();
                    ledState = LED_BUTTON_3S_HOLD;
                }
            }

            if (buttonPressed == false)
            {
                // Button just released
                if (deltaTime >= 8000)
                {
                    buttonFactoryDefaults();
                }
                else if (deltaTime >= 3000)
                {
                    if (settings.debugBluetooth == true)
                        systemPrintln("Button initiated pairing");

                    // You can't pair if radio is off or in BLE mode
                    if (settings.btType == BLUETOOTH_RADIO_OFF)
                    {
                        // Fall through and continue task
                    }
                    else if (settings.btType == BLUETOOTH_RADIO_BLE)
                    {
                        if (settings.debugBluetooth == true)
                            systemPrintln("Button pairing not supported in BLE mode.");

                        // Reset LED state
                        if (bluetoothState == BT_CONNECTED)
                            ledState = LED_CONNECTED;

                        // Fall through and continue task
                    }
                    else
                    {
                        if (bluetoothConnected() == true)
                        {
                            // We can't initiate a discovery after the Bluetooth stack has connected
                            // See issue: https://github.com/espressif/arduino-esp32/issues/8448
                            // Workaround is to set a flag and reset

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
                    }
                }
                else if (bluetoothState == BT_PAIRING)
                {
                    if (settings.debugBluetooth == true)
                        systemPrintln("Exit bluetooth pairing. Return to normal BT passive mode.");

                    // Clear any paired MAC
                    settings.btPairedMac[0] = '\0';

                    // Restart radio
                    bluetoothBegin();
                }
            }
        }

        // The button was not previously pressed
        else // buttonWasPressed == false
        {
            // Determine if the button is pressed
            if (buttonPressed)
            {
                buttonPressedTime = millis(); // Mark the start time
            }
        }

        // Save the current button state
        buttonWasPressed = buttonPressed;

        feedWdt();
        taskYIELD();
    }
}

// Reset system to defaults
void buttonFactoryDefaults()
{
    factoryDefaults();      // Set settings struct to defaults
    recordSystemSettings(); // Record current settings struct to NVM

    systemPrintln("Factory defaults applied");

    systemPrintln("System resetting");
    delay(50); // Allow print to complete

    ESP.restart();
}

uint8_t readPairButton()
{
    if (pin_pairButton == PIN_UNDEFINED)
        return (HIGH);
    return (digitalRead(pin_pairButton));
}