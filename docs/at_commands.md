# AT Commands

BlueSMiRF radios are very flexible. By default, the radio is looking for serial communication at **115200**bps. Open the terminal of your choice and enter $$$ and wait for an `OK`. The radio is now ready for an AT command.

**Note:** The device can also be configured by connecting over Bluetooth and entering $$$.

**Note:** Command mode cannot be entered 60 seconds after power-on. This setting can be configured with the command `AT-MaxCommandTimeMs`.

Below is a brief list of commands:

| AT Command | Command Description                      |
|------------|------------------------------------------|
|+++         | Enter command mode                       |
|AT          | Reports OK                               |
|AT?         | Display this help text                   |
|ATA         | Display all settings                     |
|ATB         | Display Bluetooth settings               |
|ATC         | Check for new firmware                   |
|ATD         | Display the debug settings               |
|ATF         | Restore factory settings                 |
|ATM         | Display MAC address                      |
|ATP         | Start pairing process                    |
|ATS         | Display serial settings                  |
|ATU         | Update firmware                          |
|ATV         | Display firmware version                 |
|ATW         | Save current settings to NVM             |
|ATX         | Exit command mode                        |
|ATY         | Display system settings                  |
|ATZ         | Reboot the system                        |
|AT-Param=xxx| Set parameter's value to xxx by name (Param)|
|AT-Param?   | Print parameter's current value by name (Param)|
|AT-?        | Display the setting values               |

*Table of AT Commands*

A parameter is set using the **AT-** prefix, followed by the name of the command with an equals sign and the value to set. For example, sending **AT-SerialSpeed=115200** will change the serial interface speed to 115200bps. This setting can be stored in NVM (non-volatile memory) by sending the **ATW** command. To query a setting, send the AT command without a value and the device will respond with the current value. For example, sending **AT-SerialSpeed** will generate the response **115200** followed by **OK**.

The commands are best discussed in groups:

* [Bluetooth Commands](http://docs.sparkfun.com/SparkFun_LoRaSerial/at_commands/#bluetooth-commands)
* [Serial Commands](http://docs.sparkfun.com/SparkFun_LoRaSerial/at_commands/#serial-commands)
* [System Commands](http://docs.sparkfun.com/SparkFun_LoRaSerial/at_commands/#serial-commands)
* Firmware Commands
* Debug Commands

## Bluetooth Commands

| AT Command | Command Description                      |
|------------|------------------------------------------|
| AT-BluetoothConnectRetries | Number of retries of a paired connection
| AT-BluetoothConnectTimeoutMs | Milliseconds before a paired connection attempt times out
| AT-BluetoothEscapeCharacter | The character received from the remote system, sought to enter command mode
| AT-BluetoothNickname | User configurable name to broadcast over Bluetooth during discovery
| AT-BluetoothPairedMac | MAC address of the unit that the user wants to connect to at startup
| AT-BluetoothPairedName | Name of the unit that the user wants to connect to at startup
| AT-BluetoothPin | Pin to enter during pairing - only required for older Bluetooth devices
| AT-BluetoothRxSize | Bluetooth receive buffer size
| AT-BluetoothTxSize | Bluetooth write buffer size
| AT-BluetoothType | Bluetooth protocol used for communication

*Table of Bluetooth Commands*

* **BluetoothConnectRetries** - If this device has a paired MAC or name, at power up it will attempt to connect to this paired device. A connection is not guaranteed, and the connection will be re-tried this number of times before going into passive, discoverable mode.

* **BluetoothConnectTimeoutMs** - When this device is connecting to a paired device, if this number of milliseconds expires before a connection is made, the device will attempt to reconnect to the paired device.

* **BluetoothEscapeCharacter** - This is the character that must be transmitted by a remote device to enter command mode remotely over the Bluetooth connection. **Note:** Escape characters are ignored after `MaxCommandTimeMs` number of milliseconds and within `MinEscapeTimeMs` of other incoming characters.

* **BluetoothNickname** - The name that is broadcast when other devices are scanning for devices to pair to.

* **BluetoothPairedMac** - The MAC address of the BlueSMiRF that this device should pair to at power-on. Use the `ATM` command on the remote device to display its MAC address. This command is not normally used; use the button pairing method for an easier way to pair two devices.

* **BluetoothPairedName** - The name of the BlueSMiRF that this device should pair to at power-on. Use the `BluetoothNickname` command on the remote device to change its paired name. This command is not normally used; use the button pairing method for an easier way to pair two devices.

* **BluetoothPin** - The pin that is needed during pairing. Only needed on very old Bluetooth USB dongles. 

* **BluetoothRxSize** - The size of the Bluetooth receive buffer. Increase if a large amount of data is coming into the BlueSMiRF over Bluetooth, before the speed of the serial interface can output it.

* **BluetoothTxSize** - The size of the Bluetooth transmit buffer. Increase if a large amount of data needs to be transmitted over Bluetooth but the connection between devices is poor and multiple retransmissions occur.

* **BluetoothType** - Controls the Bluetooth protocol. Protocol 0 = Serial Port Profile (SPP). 1 = Bluetooth Low-Energy (BLE). 2 = Radio off. Only SPP protocol supports pairing. 

## Serial Commands

| AT Command | Command Description                      |
|------------|------------------------------------------|
| AT-FlowControl | Enable the use of CTS/RTS flow control signals
| AT-InvertCts | Invert the input of CTS
| AT-InvertRts | Invert the output of RTS
| AT-PartialFrameTimeoutMs | Send partial buffer if time expires
| AT-RtsStartSendingPercent | Percent of serialReceiveBuffer that is free when RTS is asserted
| AT-RtsStopSendingPercent | Percent of serialReceiveBuffer that is free when RTS is deasserted
| AT-SerialReceiveBufferSize=51200
| AT-SerialSpeed=115200
| AT-SerialTransmitBufferSize=10240
|

* **FlowControl** - If flow control is enabled, BlueSMiRF will send data when its CTS pin is driven low (the host system is telling the radio to transmit). If flow control is enabled, BlueSMiRF will drive its RTS low if its serial buffer is full (the radio is telling the host system to hold its horses). By default, flow control is turned off.

* **InvertCts** - By default, InvertCts is false and CTS is high when data is allowed to flow. Enable InvertCts to do the opposite.

* **InvertRts** - By default, InvertRts is false and RTS is high when data is allowed to flow. Enable InvertRts to do the opposite.

* **PartialFrameTimeoutMs** - The number of milliseconds of timeout before a partial packet is sent. For example, if a partial frame of 12 bytes is received, the radio will wait this amount for more bytes before initiating a transmission.

* **RtsStartSendingPercent** - Percent of serialReceiveBuffer that is free when RTS is asserted. Default of 25% of serialReceiveBuffer.

* **RtsStopSendingPercent** - Percent of serialReceiveBuffer that is free when RTS is deasserted. Default of 5% of serialReceiveBuffer.

* **SerialReceiveBufferSize** - Buffer size to receive serial data from the serial port, to be sent over Bluetooth.

* **SerialSpeed** - The baud rate that the BlueSMiRF operates at. Discrete values 2400, 4800, 9600, 14400, 19200, 38400, 57600, 115200, 230400, 460800, and 921600bps are allowed.   

* **SerialTransmitBufferSize** - Buffer size to receive bytes from Bluetooth, waiting to be printed out the UART.

## System Commands

| AT Command | Command Description                      |
|------------|------------------------------------------|
| AT-EscapeCharacter | The character sought to enter command mode
| AT-EscapeCharacterCount | The number of escape characters required to enter command mode
| AT-LedStyle | Controls the behavior of the Status and Connect LEDs
| AT-MaxCommandTimeMs | After this time in milliseconds, command mode cannot be entered
| AT-MinEscapeTimeMs | Serial traffic must stop this amount of milliseconds before an escape character is recognized
| AT-WiFiPassword | Password for the SSID, used for over-the-air-updates
| AT-WiFiSSID | SSID used for over-the-air-updates
|

* **EscapeCharacter** - The character that must be entered a number of times (`EscapeCharacterCount`) to enter configuration mode. An escape character must be entered before the max time of `MaxCommandTimeMs` and after `MinEscapeTimeMs`.

* **EscapeCharacterCount** - The number of escape characters needed before command mode is entered. Set to 0 to disable.

* **LedStyle** - Controls how the LEDs behave. CLASSIC = 0, SERIAL_TRAFFIC = 1, OFF = 2. 
  
  In CLASSIC mode (default), the **Status** LED blinks with TX/RX traffic.

    In SERIAL_TRAFFIC mode, the **Connect** LED blinks with TX traffic and the **Status** LED blinks with RX traffic.

    In OFF mode, the **Connect** and **Status** LEDs are turned off.

* **MaxCommandTimeMs** - Once this number of milliseconds has passed, command mode cannot be entered. This is used as a method to prevent a remote system from accidentally entering command mode.

* **MinEscapeTimeMs** - This number of milliseconds must pass between the last serial character received and an escape character. This is used as a method to prevent a remote system from accidentally entering command mode.

* **WiFiPassword** - The password for the local WiFi used for firmware updates.

* **WiFiSSID** - The SSID for the local WiFi used for firmware updates.
