void ledBegin()
{
  if (pin_connectLED != PIN_UNDEFINED)
    pinMode(pin_connectLED, OUTPUT);
  if (pin_statusLED != PIN_UNDEFINED)
    pinMode(pin_statusLED, OUTPUT);

  ledConnectOff();
  ledStatusOff();
}


void ledUpdate()
{
    if (settings.ledStyle == LEDS_CLASSIC)
    {
    }
    else if (settings.ledStyle == LEDS_SERIAL_TRAFFIC)
    {
    }
}

// Turn on TX (aka Connect) LED
void ledTxOn()
{
    if (settings.ledStyle == LEDS_SERIAL_TRAFFIC)
    {
        ledConnectOn();
    }
    else if (settings.ledStyle == LEDS_CLASSIC)
    {
        ledConnectBlink(); // Blink the connect LED during serial traffic
    }
}
void ledTxOff()
{
    if (settings.ledStyle == LEDS_SERIAL_TRAFFIC)
    {
        ledConnectOff();
    }
    else if (settings.ledStyle == LEDS_CLASSIC)
    {
        ledConnectOff();
    }
}

// Turn on RX (aka Status) LED
void ledRxOn()
{
    if (settings.ledStyle == LEDS_SERIAL_TRAFFIC)
    {
        ledStatusOn();
    }
    else if (settings.ledStyle == LEDS_CLASSIC)
    {
        ledConnectBlink(); // Blink the connect LED during serial traffic
    }
}
void ledRxOff()
{
    if (settings.ledStyle == LEDS_SERIAL_TRAFFIC)
    {
        ledStatusOff();
    }
    else if (settings.ledStyle == LEDS_CLASSIC)
    {
        ledConnectOff();
    }
}

bool isConnectOn()
{
  if (pin_connectLED == PIN_UNDEFINED)
    return (LOW);
  return (digitalRead(pin_connectLED));
}
void ledConnectOn()
{
  if (pin_connectLED != PIN_UNDEFINED)
    digitalWrite(pin_connectLED, HIGH);
}
void ledConnectOff()
{
  if (pin_connectLED != PIN_UNDEFINED)
    digitalWrite(pin_connectLED, LOW);
}
void ledConnectBlink()
{
  if (pin_connectLED != PIN_UNDEFINED)
    digitalWrite(pin_connectLED, !digitalRead(pin_connectLED));
}

bool isStatusOn()
{
  if (pin_statusLED == PIN_UNDEFINED)
    return (LOW);
  return (digitalRead(pin_statusLED));
}
void ledStatusOn()
{
  if (pin_statusLED != PIN_UNDEFINED)
    digitalWrite(pin_statusLED, HIGH);
}
void ledStatusOff()
{
  if (pin_statusLED != PIN_UNDEFINED)
    digitalWrite(pin_statusLED, LOW);
}
void ledStatusBlink()
{
  if (pin_statusLED != PIN_UNDEFINED)
    digitalWrite(pin_statusLED, !digitalRead(pin_statusLED));
}