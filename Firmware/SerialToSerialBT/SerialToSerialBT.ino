/*
  The most basic implementation of serial over Bluetooth.
  We use local buffers to speed up the data transfers.

  Limitations:
  * No settings (variable, baud rate, AT command interface, etc)
  * No flow control

 */

#include "BluetoothSerial.h" //Built-in library
BluetoothSerial SerialBT;

uint8_t buffer[512];

void setup()
{
  Serial.begin(115200);
  SerialBT.begin("BlueSMiRF");
}

void loop()
{
  if (Serial.available())
  {
    int toWrite = Serial.read(buffer, sizeof(buffer));
    SerialBT.write(buffer, toWrite);
  }
  if (SerialBT.available())
  {
    int toWrite = SerialBT.readBytes(buffer, sizeof(buffer));
    Serial.write(buffer, toWrite);
  }
}
