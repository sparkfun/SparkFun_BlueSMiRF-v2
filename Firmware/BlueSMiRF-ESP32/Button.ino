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
                    ledState = LED_BUTTON_3S_HOLD;
                }
            }

            if (buttonPressed == false)
            {
                // Button just released
                if (deltaTime >= 8000)
                {
                    Serial.println("Factory defaults");
                    // buttonFactoryDefaults();
                }
                else if (deltaTime >= 3000)
                {
                    if(settings.debugBluetooth == true)
                        systemPrintln("Button started pairing");

                    bluetoothBeginPairing(); 
                }
                else if(bluetoothState == BT_PAIRING)
                {
                    if(settings.debugBluetooth == true)
                        systemPrintln("Exit bluetooth pairing. Return to normal BT passive mode.");

                    //Clear any paired MAC
                    settings.btPairedMac[0] = '\0';

                    //Resart radio
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