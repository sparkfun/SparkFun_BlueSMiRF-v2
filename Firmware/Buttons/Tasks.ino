// Check the state of the setup (Pair) button
void ButtonCheckTask(void *e)
{
  if (pairButton != nullptr)
    pairButton->begin();

  while (true)
  {
    if (pairButton != nullptr)
      pairButton->read();

    if (pairButton != nullptr && pairButton->pressedFor(1000))
    {
      buttonFactoryDefaults();
    }

    feedWdt();
    taskYIELD();
  }
}

// Normally a delay(1) will feed the WDT but if we don't want to wait that long, this feeds the WDT without delay
void feedWdt()
{
    vTaskDelay(1);
}
