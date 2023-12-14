void buttonBegin()
{
    if(pin_pairButton == PIN_UNDEFINED)
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

  while (true)
  {
    if (pairButton != nullptr)
      pairButton->read();

    if (pairButton != nullptr && pairButton->pressedFor(5000))
    {
      buttonFactoryDefaults();
    }

    feedWdt();
    taskYIELD();
  }
}

// Reset system to defaults and blink LEDs until button is released
void buttonFactoryDefaults()
{
  factoryDefaults(); // Set settings struct to defaults
  recordSystemSettings();  // Record current settings struct to NVM

  systemPrintln("Factory defaults applied");

  //Pre-set LEDs ready for blink
  ledStatusOn();
  ledConnectOff();
  
  while (readPairButton() == LOW)
  {
    ledStatusBlink();
    ledConnectBlink();
    delay(100);
  }

  //Ensure LEDs are off
  ledStatusOff();
  ledConnectOff();
 
  systemPrintln("System resetting");
  delay(50); //Allow print to complete

  ESP.restart();
}

uint8_t readPairButton()
{
  if (pin_pairButton == PIN_UNDEFINED)
    return (HIGH);
  return (digitalRead(pin_pairButton));
}