void ledBegin()
{
    Serial.println("LED begin");

    if (pin_connectLED != PIN_UNDEFINED)
        pinMode(pin_connectLED, OUTPUT);
    if (pin_statusLED != PIN_UNDEFINED)
        pinMode(pin_statusLED, OUTPUT);

    // Turn LEDs on to indicate system power-up
    ledConnectOn();
    ledStatusOn();
    ledState = LED_ON;

    // Create a task to handle LED updates
    if (ledTaskHandle == nullptr)
        xTaskCreatePinnedToCore(ledUpdate,        // Function to call
                                "ledUpdate",      // Just for humans
                                ledTaskStackSize, // Stack Size
                                nullptr,          // Task input parameter
                                0,                // Priority 0 = lowest, 3 = highest
                                &ledTaskHandle,   // Task handle
                                1);               // Core where task should run, 0=core, 1=Arduino
}

// The status (red) and connect (green) LEDs are lit based on the bluetoothState
// There are two styles of LED blinking, Classic and Serial Traffic
//  Classic is the original RN-41 behavior. Connect blinks while waiting for BT connect, solid when connected.
//  Status LED off waiting for BT connect, blinks with TX/RX traffic.
//  Serial traffic is where the Status LED blinks with RX traffic, Connect LED blinks with TX traffic
//  Taken care of during task
void ledUpdate(void *e)
{
    while (true)
    {
        if (ledState == LED_OFF)
        {
            ledConnectOff();
            ledStatusOff();
        }
        else if (ledState == LED_ON)
        {
            ledConnectOn();
            ledStatusOn();
        }
        else if (ledState == LED_NOTCONNECTED)
        {
            // Blink Connect LED at 1Hz while waiting for connection
            if (millis() - lastLedUpdate > 1000)
            {
                lastLedUpdate = millis();
                ledConnectBlink();
                ledStatusOff();
            }
        }
        else if (ledState == LED_CONNECTED)
        {
            if (settings.ledStyle == LEDS_CLASSIC)
            {
                // Status LED controlled by serial traffic
                ledConnectOn();
            }
            else if (settings.ledStyle == LEDS_SERIAL_TRAFFIC)
            {
                // Status and Connect LEDs are controlled by serial traffic
            }
        }

        // S-1/C-0: Entered if a board is connecting to a paired MAC
        else if (ledState == LED_CONNECTING)
        {
            ledStatusOn();
            ledConnectOff();
        }

        // S-Fade/C-0: Device is actively scanning for friendly devices to pair with
        else if (ledState == LED_SCANNING)
        {
            if (millis() - lastLedUpdate > fadeUpdateTimeMs) // Update fade every 30ms
            {
                lastLedUpdate = millis();
                ledConnectOff();

                statusLedBrightness += statusFadeAmount;
                if (statusLedBrightness > 255)
                    statusFadeAmount *= -1; // Switch directions

                ledStatusFade(statusLedBrightness);
            }
        }
        else if (ledState == LED_DISCOVERABLE)
        {
            // Status off, Connect fade on/off
            if (millis() - lastLedUpdate > fadeUpdateTimeMs) // Update fade every 30ms
            {
                lastLedUpdate = millis();
                ledStatusOff();

                connectLedBrightness += connectFadeAmount;
                if (connectLedBrightness > 255)
                    connectFadeAmount *= -1; // Switch directions

                ledConnectFade(connectLedBrightness);
            }
        }

        // Blink S/C back/forth at 2Hz. Entered when user holds button for > 3 second
        else if (ledState == LED_BUTTON_3S_HOLD)
        {
            if (millis() - lastLedUpdate > 500)
            {
                lastLedUpdate = millis();
                ledStatusBlink();
                ledConnectBlink();
            }
        }

        // Blink S/C back/forth at 10Hz. Entered when user holds button for > 8 seconds
        else if (ledState == LED_BUTTON_8S_HOLD)
        {
            if (millis() - lastLedUpdate > 100)
            {
                lastLedUpdate = millis();
                ledStatusBlink();
                ledConnectBlink();
            }
        }

        else
        {
            Serial.println("Unknown LED state"); // We should not be here
        }
        feedWdt();
        taskYIELD();
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
void ledConnectFade(uint8_t fadeAmount)
{
    if (pin_connectLED != PIN_UNDEFINED)
        analogWrite(pin_connectLED, fadeAmount);
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
void ledStatusFade(uint8_t fadeAmount)
{
    if (pin_statusLED != PIN_UNDEFINED)
        analogWrite(pin_statusLED, fadeAmount);
}
