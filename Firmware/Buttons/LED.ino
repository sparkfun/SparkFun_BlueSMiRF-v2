void ledBegin()
{
  if (pin_connectLED != PIN_UNDEFINED)
    pinMode(pin_connectLED, OUTPUT);
  if (pin_statusLED != PIN_UNDEFINED)
    pinMode(pin_statusLED, OUTPUT);

  ledConnectOff();
  ledStatusOff();
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
