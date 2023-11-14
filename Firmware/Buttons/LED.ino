void ledBegin()
{
  if (pin_connectLED != 255)
    pinMode(pin_connectLED, OUTPUT);
  if (pin_statusLED != 255)
    pinMode(pin_statusLED, OUTPUT);

  ledConnectOff();
  ledStatusOff();
}

bool isConnectOn()
{
  if (pin_connectLED == 255)
    return (LOW);
  return (digitalRead(pin_connectLED));
}
void ledConnectOn()
{
  if (pin_connectLED != 255)
    digitalWrite(pin_connectLED, HIGH);
}
void ledConnectOff()
{
  if (pin_connectLED != 255)
    digitalWrite(pin_connectLED, LOW);
}
void ledConnectBlink()
{
  if (pin_connectLED != 255)
    digitalWrite(pin_connectLED, !digitalRead(pin_connectLED));
}

bool isStatusOn()
{
  if (pin_statusLED == 255)
    return (LOW);
  return (digitalRead(pin_statusLED));
}
void ledStatusOn()
{
  if (pin_statusLED != 255)
    digitalWrite(pin_statusLED, HIGH);
}
void ledStatusOff()
{
  if (pin_statusLED != 255)
    digitalWrite(pin_statusLED, LOW);
}
void ledStatusBlink()
{
  if (pin_statusLED != 255)
    digitalWrite(pin_statusLED, !digitalRead(pin_statusLED));
}
