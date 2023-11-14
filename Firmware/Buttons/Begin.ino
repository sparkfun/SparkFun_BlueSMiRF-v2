void buttonBegin()
{
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
