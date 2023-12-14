void ledBegin()
{
    if (pin_connectLED != PIN_UNDEFINED)
        pinMode(pin_connectLED, OUTPUT);
    if (pin_statusLED != PIN_UNDEFINED)
        pinMode(pin_statusLED, OUTPUT);

    // Turn LEDs on to indicate system power-up
    ledConnectOn();
    ledStatusOn();
}

void ledUpdate()
{
    if (settings.ledStyle == LEDS_CLASSIC)
    {
        // Original RN-41 behavior. Connect blinks while waiting for BT connect, solid when connected.
        // Status LED off waiting for BT connect, blinks with TX/RX traffic.

        if (bluetoothState == BT_NOTCONNECTED)
        {
            // Blink Connect LED at 1Hz while waiting for connection
            if (millis() - lastLedUpdate > 1000)
            {
                lastLedUpdate = millis();
                ledConnectBlink();
            }
        }
        else if (bluetoothState == BT_CONNECTED)
        {
            ledConnectOn();
        }
        else
        {
            ledConnectOff();
        }

        // Blink Status LED during serial traffic happens during task
    }
    else if (settings.ledStyle == LEDS_SERIAL_TRAFFIC)
    {
        // Status LED blinks with RX traffic, Connect LED blinks with TX traffic
        // Taken care of during task

        // Blink Connect LED at 1Hz while waiting for connection
        if (bluetoothState == BT_NOTCONNECTED)
        {
            if (millis() - lastLedUpdate > 1000)
            {
                lastLedUpdate = millis();
                ledConnectBlink();
            }
        }
        else if (bluetoothState == BT_CONNECTED)
        {
            // Connect is controlled by serial traffic
        }
        else
        {
            ledConnectOff();
        }
    }
    else // LEDS_ALL_OFF
    {
        ledConnectOff();
        ledStatusOff();
    }
}

// Turn on TX (aka Connect) LED
void ledTxOn()
{
    if (settings.ledStyle == LEDS_CLASSIC) // Blink the status LED during serial traffic
    {
        ledStatusBlink();
    }
    else if (settings.ledStyle == LEDS_SERIAL_TRAFFIC) // Connect = TX, Status = RX
    {
        ledConnectOn();
    }
    else
    {
        ledStatusOff();
        ledConnectOff();
    }
}
void ledTxOff()
{
    if (settings.ledStyle == LEDS_CLASSIC) // Blink the status LED during serial traffic
    {
        ledStatusOff();
    }
    else if (settings.ledStyle == LEDS_SERIAL_TRAFFIC) // Connect = TX, Status = RX
    {
        ledConnectOff();
    }
    else
    {
        ledStatusOff();
        ledConnectOff();
    }
}

// Turn on RX (aka Status) LED
void ledRxOn()
{
    if (settings.ledStyle == LEDS_CLASSIC) // Blink the status LED during serial traffic
    {
        ledStatusBlink();
    }
    else if (settings.ledStyle == LEDS_SERIAL_TRAFFIC) // Connect = TX, Status = RX
    {
        ledStatusOn();
    }
    else
    {
        ledStatusOff();
        ledConnectOff();
    }
}
void ledRxOff()
{
    if (settings.ledStyle == LEDS_CLASSIC) // Blink the status LED during serial traffic
    {
        ledStatusOff();
    }
    else if (settings.ledStyle == LEDS_SERIAL_TRAFFIC) // Connect = TX, Status = RX
    {
        ledStatusOff();
    }
    else
    {
        ledStatusOff();
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