// Return number of bytes sitting in the serial transmit buffer
uint32_t availableTXBytes()
{
    if (serialTxHead >= serialTxTail)
        return (serialTxHead - serialTxTail);
    return (settings.serialTransmitBufferSize - serialTxTail + serialTxHead);
}

// Return number of bytes sitting in the serial receive buffer
uint32_t availableRXBytes()
{
    if (serialRxHead >= serialRxTail)
        return (serialRxHead - serialRxTail);
    return (settings.serialReceiveBufferSize - serialRxTail + serialRxHead);
}

// Returns true if CTS is asserted (low = host says it's ok to send data)
bool isCTS()
{
    if (pin_cts == PIN_UNDEFINED)
        return (true); // CTS not implmented on this board

    if (settings.flowControl == false)
        return (true); // CTS turned off

    // The SAMD21 specification (page 448) indicates that CTS is low when data is flowing
    // "Character transmission will start only if CTS = 0. When CTS is set, the transmitter will complete the
    // ongoing transmission and stop transmitting.
    return (digitalRead(pin_cts) == LOW) ^ settings.invertCts;
}

void rtsAssert()
{
    updateRTS(true);
}

void rtsDeassert()
{
    updateRTS(false);
}

// Update the output of the RTS pin
// BlueSMiRF will drive RTS low when it is ready for data
// Given false, we tell the host we *do not* need more data
// Given true, we tell the host we are ready for more data
void updateRTS(bool assertRTS)
{
    rtsAsserted = assertRTS;
    if (settings.flowControl && (pin_rts != PIN_UNDEFINED))
        // The SAMD21 specification (page 448) indicates that RTS is low to enable data flow
        digitalWrite(pin_rts, (assertRTS ? 0 : 1) ^ settings.invertRts);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Command RX - Remote command data received from a remote system
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Return number of bytes sitting in the serial receive buffer
uint16_t availableRXCommandBytes()
{
    if (commandRXHead >= commandRXTail)
        return (commandRXHead - commandRXTail);
    return (sizeof(commandRXBuffer) - commandRXTail + commandRXHead);
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Command TX - Remote command data or command response data to be sent to the remote system
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Return number of bytes sitting in the serial transmit buffer
uint16_t availableTXCommandBytes()
{
    if (commandTXHead >= commandTXTail)
        return (commandTXHead - commandTXTail);
    return (sizeof(commandTXBuffer) - commandTXTail + commandTXHead);
}

// Add given byte to serialTransmitBuffer
// See serialWriteTask for the actual Serial.write
void serialAddToOutputBuffer(uint8_t data)
{
    // Make sure there is enough room in the buffer
    if ((settings.serialTransmitBufferSize - availableTXBytes()) < 32)
    {
        // Print direct to serial port, don't use systemPrintf
        Serial.printf("\r\nserialTransmitBuffer overflow! sizeof(serialTransmitBuffer): %d availableTXBytes(): %d\r\n",
                      settings.serialTransmitBufferSize, availableTXBytes());
    }

    // Add this byte to the serial output buffer
    serialTransmitBuffer[serialTxHead++] = data;
    serialTxHead %= settings.serialTransmitBufferSize;
}

// Restart serial port at user setting baud rate
// Malloc the Tx and Rx buffers
// Calculate RTS thresholds
// Start serial tasks
void serialStart()
{
    Serial.end(); // Close port before setting buffer size

    Serial.setRxBufferSize(settings.uartReceiveBufferSize);
    Serial.setTimeout(settings.serialTimeout); // Requires serial traffic on the UART pins for detection
    Serial.begin(settings.baudRate);           // Restart serial at correct baud rate

    // Reduce threshold value above which RX FIFO full interrupt is generated
    // Allows more time between when the UART interrupt occurs and when the FIFO buffer overruns
    // Serial.setRxFIFOFull(50); //Available in >v2.0.5
    uart_set_rx_full_threshold(0, settings.serialRxFullThreshold); // uart_num, threshold

    // Error check
    if (settings.serialReceiveBufferSize == 0 || settings.serialTransmitBufferSize == 0)
        factoryDefaults(); // NVM is corrupt

    if (serialReceiveBuffer != nullptr)
        free(serialReceiveBuffer);

    serialReceiveBuffer = (uint8_t *)malloc(settings.serialReceiveBufferSize * sizeof(uint8_t));

    if (serialReceiveBuffer == nullptr)
    {
        // Print direct to serial port, don't use systemPrint
        Serial.println("Error: serialReceiveBuffer failed to malloc. Freezing.");
        while (1)
            ;
    }

    if (serialTransmitBuffer != nullptr)
        free(serialTransmitBuffer);

    serialTransmitBuffer = (uint8_t *)malloc(settings.serialTransmitBufferSize * sizeof(uint8_t));

    if (serialTransmitBuffer == nullptr)
    {
        // Print direct to serial port, don't use systemPrint
        Serial.println("Error: serialTransmitBuffer failed to malloc. Freezing.");
        while (1)
            ;
    }

    // Calculate RTS high and low water marks
    rtsStartSendingBytes = settings.serialReceiveBufferSize * ((float)settings.rtsStartSendingPercent / 100.0);
    rtsStopSendingBytes = settings.serialReceiveBufferSize * ((float)settings.rtsStopSendingPercent / 100.0);

    // Reads data from Bluetooth and sends to serialTransmitBuffer
    if (serialReadTaskHandle == nullptr)
        xTaskCreatePinnedToCore(serialReadTask,                  // Function to call
                                "serialRead",                    // Just for humans
                                serialReadTaskStackSize,         // Stack Size
                                nullptr,                         // Task input parameter
                                settings.serialReadTaskPriority, // Priority
                                &serialReadTaskHandle,           // Task handle
                                settings.serialReadTaskCore);    // Core where task should run, 0=core, 1=Arduino

    if (serialWriteTaskHandle == nullptr)
        xTaskCreatePinnedToCore(serialWriteTask,                  // Function to call
                                "serialWrite",                    // Just for humans
                                serialWriteTaskStackSize,         // Stack Size
                                nullptr,                          // Task input parameter
                                settings.serialWriteTaskPriority, // Priority
                                &serialWriteTaskHandle,           // Task handle
                                settings.serialWriteTaskCore);    // Core where task should run, 0=core, 1=Arduino
}

// End serial
// Free the Tx and Rx buffers
// Delete serial tasks
void serialStop()
{
    Serial.end();

    if (serialReceiveBuffer != nullptr)
        free(serialReceiveBuffer);

    if (serialTransmitBuffer != nullptr)
        free(serialTransmitBuffer);

    // Stop tasks
    if (serialReadTaskHandle != nullptr)
    {
        vTaskDelete(serialReadTaskHandle);
        serialReadTaskHandle = nullptr;
    }
    if (serialWriteTaskHandle != nullptr)
    {
        vTaskDelete(serialWriteTaskHandle);
        serialWriteTaskHandle = nullptr;
    }
}