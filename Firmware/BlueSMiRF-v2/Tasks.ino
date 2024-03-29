// Read from BT SPP and write to serialTransmitBuffer.
// If the remote device (phone, robot, etc) has new data (NTRIP RTCM, etc), read it in over Bluetooth and pass along to
// serialTransmitBuffer. Scan for escape characters to enter Bluetooth Echo Mode
void btReadTask(void *e)
{
    int remoteEscapeCharsReceived = 0;
    unsigned long lastByteReceived_ms = 0;

    while (true)
    {
        if (bluetoothGetState() == BT_CONNECTED)
        {
            while (btPrintEcho == false && bluetoothDataAvailable())
            {
                // Check stream for escape characters
                byte incoming = bluetoothRead();

                // Check if remote escape character is enabled
                // Command mode cannot be entered if the system has been running for more than setings.maxCommandTime_ms
                if (settings.btEscapeCharacter > 0 && incoming == settings.btEscapeCharacter &&
                    millis() < settings.maxCommandTime_ms)
                {
                    // Ignore escape characters received within 2 seconds of serial traffic
                    if (millis() - lastByteReceived_ms > settings.minEscapeTime_ms)
                    {
                        remoteEscapeCharsReceived++;
                        if (remoteEscapeCharsReceived == settings.maxEscapeCharacters)
                        {
                            printEndpoint = PRINT_ENDPOINT_ALL;

                            lastByteReceived_ms = millis();

                            systemPrintln("\r\nOK");

                            if (settings.debugBluetooth == true)
                                systemPrintln("Echoing all serial to BT device");

                            btPrintEcho = true;

                            inBluetoothCommandMode = true; // Allow AT parsing. All received RF data to be printed.

                            forceRadioReset = false; // Don't reset the radio link unless a setting requires it

                            tempSettings = settings;

                            remoteEscapeCharsReceived = 0;

                            // Prep LED values for fading
                            statusLedBrightness = 0;
                            statusFadeAmount = startingFadeAmount;
                            connectLedBrightness = 0;
                            connectFadeAmount = startingFadeAmount;

                            oldLedState = ledState; // Remember this state so we can return after leaving command mode
                            ledState = LED_CONFIG;

                            // return; // Avoid recording this incoming command char
                        }
                    }
                    else
                    {
                        // Ignore this escape character, pass along to output
                        bluetoothSerialAddToOutputBuffer(incoming);
                        lastByteReceived_ms = millis();
                    }
                }
                else // This is just a character in the stream, ignore
                {
                    // Pass any escape characters that turned out to not be a complete escape sequence
                    while (remoteEscapeCharsReceived-- > 0)
                        bluetoothSerialAddToOutputBuffer(settings.escapeCharacter);

                    // Pass byte to the output buffer, which will get sent to Serial.write
                    bluetoothSerialAddToOutputBuffer(incoming);

                    lastByteReceived_ms = millis();
                    remoteEscapeCharsReceived = 0; // Update timeout check for escape char and partial frame
                }                                  // End just a character in the stream

            } // End btPrintEcho == false && bluetoothRxDataAvailable()

        } // End bluetoothGetState() == BT_CONNECTED

        // if (settings.enableTaskReports == true)
        //     systemPrintf("SerialWriteTask High watermark: %d\r\n", uxTaskGetStackHighWaterMark(nullptr));

        feedWdt();
        taskYIELD();
    } // End while(true)
}

// Read from serialReceiveBuffer and write to SPP.
void btWriteTask(void *e)
{
    uint8_t btFrame[512];
    uint16_t bytesToSend = 0;
    unsigned long lastByteReceived_ms = 0;

    while (true)
    {
        while (availableRXBytes())
        {
            uint8_t incoming = serialReceiveBuffer[serialRxTail++];
            serialRxTail %= settings.serialReceiveBufferSize;

            // Move to chunk'd array
            btFrame[bytesToSend++] = incoming;

            // Send frame if it's filled
            if (bytesToSend == sizeof(btFrame))
            {
                if (bluetoothGetState() == BT_CONNECTED)
                {
                    bluetoothWrite(btFrame, bytesToSend); // Send this chunk to BT radio
                }
                bytesToSend = 0; // Start over
            }
        } // End availableRXBytes()

        // If no new data arrives after X_ms, send out partial frame
        if ((bytesToSend > 0) && ((millis() - lastByteReceived_ms) > settings.serialPartialFrameTimeoutMs))
        {
            bluetoothWrite(btFrame, bytesToSend); // Send this chunk to BT radio

            bytesToSend = 0; // Start over
        }

        // feedWdt();
        taskYIELD();
    } // End while(true)
}

// Read from UART and write to serialReceiveBuffer.
// Standard mode: check for escape characters.
// Command mode: parse AT commands
void serialReadTask(void *e)
{
    while (true)
    {
        if (inLocalCommandMode == true || inBluetoothCommandMode == true)
            serialReadCommandMode();
        else
            serialReadStandardMode();

        feedWdt();
        taskYIELD();
    } // End while(true)
}

// Check for escape characters from UART. Move any character to the serialReceiveBuffer.
void serialReadStandardMode()
{
    static unsigned long lastByteReceived_ms = 0;
    static unsigned long lastEscapeCharEntered_ms;
    static uint8_t escapeCharsReceived = 0; // Used to enter command mode

    int availableBufferSpace = settings.serialReceiveBufferSize - 1 - availableRXBytes();

    // Assert RTS when there is enough space in the receive buffer
    if (rtsAsserted == false && availableBufferSpace >= rtsStartSendingBytes)
    {
        rtsAssert(); // Tell the external system that we're ready for more data
        if (settings.debugSerial)
            systemPrintln("serialReceiveBuffer is open again");
    }

    if (Serial.available())
    {
        ledRxOn(); // Turn on LED during serial reception

        // Scan while there are characters available and there is room to store them
        while (Serial.available() && availableBufferSpace--)
        {
            byte incoming = systemRead();

            // Command mode cannot be entered if the system has been running for more than setings.maxCommandTime_ms
            if (incoming == settings.escapeCharacter && millis() < settings.maxCommandTime_ms)
            {
                // Ignore escape characters received within 2 seconds of serial traffic
                // Allow escape characters received within first 2 seconds of power on
                if ((millis() - lastByteReceived_ms > settings.minEscapeTime_ms) ||
                    (millis() < settings.minEscapeTime_ms))
                {
                    escapeCharsReceived++;
                    lastEscapeCharEntered_ms = millis();

                    if (escapeCharsReceived == settings.maxEscapeCharacters)
                    {
                        systemPrintln("\r\nOK");

                        inLocalCommandMode = true; // Allow AT parsing. Prevent received RF data from being printed.
                        forceRadioReset = false;   // Don't reset the radio link unless a setting requires it

                        tempSettings = settings;

                        escapeCharsReceived = 0;

                        // Prep LED values for fading
                        statusLedBrightness = 0;
                        statusFadeAmount = startingFadeAmount;
                        connectLedBrightness = 0;
                        connectFadeAmount = startingFadeAmount;

                        oldLedState = ledState; // Remember this state so we can return after leaving command mode
                        ledState = LED_CONFIG;

                        return; // Avoid recording this incoming command char
                    }
                }
                else
                {
                    // Ignore this escape character, passing along to serialReceiveBuffer
                    // serialAddToOutputBuffer(incoming);
                    serialReceiveBuffer[serialRxHead++] = settings.escapeCharacter;
                    serialRxHead %= settings.serialReceiveBufferSize; // Wrap as needed

                    lastByteReceived_ms = millis(); // Mark so that we will send partial buffer as needed
                }
            } // End incoming == settings.escapeCharacter

            else // This is just a character in the stream, move it to the serialReceiveBuffer
            {
                lastByteReceived_ms = millis(); // Mark so that we will send partial buffer as needed

                // Push any incomplete escape sequence to holding buffer
                while (escapeCharsReceived)
                {
                    escapeCharsReceived--;

                    serialReceiveBuffer[serialRxHead++] = settings.escapeCharacter;
                    serialRxHead %= settings.serialReceiveBufferSize; // Wrap as needed
                }

                serialReceiveBuffer[serialRxHead++] = incoming;   // Push incoming char to holding buffer
                serialRxHead %= settings.serialReceiveBufferSize; // Wrap as needed
            }

            // Deassert RTS when the buffer gets full
            if (rtsAsserted == true && availableBufferSpace <= rtsStopSendingBytes)
            {
                rtsDeassert();
            }
        }           // End Serial.available()
        ledRxOff(); // Turn off LED
    }               // End Serial.available()

    // Check if more than two seconds have elapsed without entering
    // command mode. The escape characters must be part of the input stream but were
    // the last characters entered. Send these characters over the radio.
    if (escapeCharsReceived && (millis() - lastEscapeCharEntered_ms > settings.minEscapeTime_ms))
    {
        // Replay the escape characters
        while (escapeCharsReceived)
        {
            escapeCharsReceived--;

            serialReceiveBuffer[serialRxHead++] = settings.escapeCharacter; // Push char to holding buffer
            serialRxHead %= settings.serialReceiveBufferSize;               // Wrap as needed
        }
    }
}

// Read incoming characters from UART and store in command buffer
// Process command when a \r or ; is seen
void serialReadCommandMode()
{
    while (systemAvailable())
    {
        byte incoming = systemRead();

        // Always echo characters in command mode
        systemWrite(incoming); // Write character to serialTransmitBuffer

        // Check for end of command
        if ((incoming == '\r') || (incoming == ';'))
        {
            // Ignore end of command if no command in the buffer
            if (commandLength > 0)
            {
                systemPrintln();
                checkCommand(); // Process command buffer
                break;
            }
        }
        else if (incoming == '\n')
            ; // Do nothing
        else
        {
            if (incoming == 8) // Backspace
            {
                if (commandLength > 0)
                {
                    // Remove this character from the command buffer
                    commandLength--;

                    // Erase the previous character
                    systemWrite(' ');
                    systemWrite(incoming);
                }
                else
                    systemWrite(7);
            }
            else
            {
                // Move this character into the command buffer
                commandBuffer[commandLength++] = incoming;

                // Don't allow the command to overflow the command buffer
                // Process the long command instead
                // Save room for the zero termination
                if (commandLength >= (sizeof(commandBuffer) - 1))
                {
                    // Let's not change the endpoint here as a remote unit may be using BT to send command
                    // printEndpoint = PRINT_ENDPOINT_SERIAL;
                    systemPrintln();
                    if (settings.debugSerial)
                    {
                        systemPrint("processSerialInput moved ");
                        systemPrint(commandLength);
                        systemPrintln(" from serialReceiveBuffer into commandBuffer");
                    }
                    checkCommand(); // Process command buffer
                    break;
                }
            }
        }
    }
}

// Move the serial data from serialTransmitBuffer to the
// selected endpoints (aka serial port, serial port + Bluetooth, etc)
// This allows us to echo the command interface over the Bluetooth link
void serialWriteTask(void *e)
{
    while (true)
    {
        // To maximize throughput, send chunks of data
        // CTS is only checked after every chunk is sent
        while (availableTXBytes() && isCTS())
        {
            ledTxOn(); // Turn on LED during serial transmissions

            int bytesToSend = availableTXBytes();

            // Break chunk if we're at the end of the buffer. We'll get it in the next pass.
            if ((serialTxTail + bytesToSend) > settings.serialTransmitBufferSize)
            {
                if (settings.debugSerial == true)
                {
                    systemPrintln();
                    systemPrintln("Wrapping tail");
                    systemPrintln();
                }
                bytesToSend = settings.serialTransmitBufferSize - serialTxTail;
            }

            int bytesSent = 0;

            if (printEndpoint == PRINT_ENDPOINT_ALL)
            {
                bytesSent = Serial.write(&serialTransmitBuffer[serialTxTail],
                                         bytesToSend); // We care more about local bytesSent
                bluetoothWrite(&serialTransmitBuffer[serialTxTail], bytesToSend);
            }
            else if (printEndpoint == PRINT_ENDPOINT_BLUETOOTH)
                bytesSent = bluetoothWrite(&serialTransmitBuffer[serialTxTail], bytesToSend);
            else
                bytesSent = Serial.write(&serialTransmitBuffer[serialTxTail], bytesToSend);

            // systemFlush(); // Prevent serial hardware from blocking more than this one write

            serialTxTail += bytesSent;
            serialTxTail %= settings.serialTransmitBufferSize;

            ledTxOff(); // Turn off LED
        }

        feedWdt();
        taskYIELD();
    } // End while(true)
}

// Normally a delay(1) will feed the WDT but if we don't want to wait that long, this feeds the WDT with a minimum delay
void feedWdt()
{
    vTaskDelay(1);
}
