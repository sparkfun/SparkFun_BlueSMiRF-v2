Each BlueSMiRF v2 firmware comes with a set of AT commands to read or change the configuration. The following set of AT commands are similar to previous BlueSMiRF AT commands. Let's go over some of these commands!


## AT Commands

!!! note
    Command mode cannot be entered **60 seconds after power-on or resetting**. This setting can be configured with the command `AT-MaxCommandTimeMs`.

BlueSMiRF radios are very flexible. By default, the radio is looking for serial communication at **115200** bps. Open the [terminal](https://learn.sparkfun.com/tutorials/terminal-basics) of your choice. Then enter `$$$` and wait for an `OK`. Both the CONNECT and STATUS LEDs will fade in and fade out whenever the board is in Command Mode. At this point, the radio is now ready for an AT command.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/BlueSMiRF_v2_AT_Commands_1_b.JPG"><img src="../assets/img/BlueSMiRF_v2_AT_Commands_1_b.JPG" width="600px" height="600px" alt="BlueSMiRF v2 Connected to Serial Terminal and in Command Mode"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><i>BlueSMiRF v2 Connected to Serial Terminal and in Command Mode</i></td>
    </tr>
  </table>
</div>

!!! note
    Depending on your serial terminal's settings, you may not see the characters that are being sent. You can try turning on the local echo to view the characters. However, keep in mind that any characters sent when the BlueSMiRF v2 is in command mode will already be echoed back.

!!! note
     The device can also be configured by connecting over Bluetooth and entering `$$$`.

Below is a brief list of commands. The BlueSMiRF will recognize commands with capital and lower case letters since the commands are not case sensitive.

<div style="text-align: center;">
    <table>
        <tr>
            <th style="text-align: center; border: solid 1px #cccccc; width:150px">AT Command
            </th>
            <th style="text-align: center; border: solid 1px #cccccc;">Command Description
            </th>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>$$$</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Enter Command Mode
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT</code>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Reports OK
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT?</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Display this help text
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATA</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Display all settings
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATB</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Display Bluetooth settings
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATC</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Check for new firmware
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATD</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Display the debug settings
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATF</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Restore factory settings
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATM</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Display MAC address
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATP</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Start pairing process
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATS</code
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Display serial settings
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATU</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Update Firmware
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATV</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Display firmware version
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATW</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Save current settings to NVM
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATX</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Exit command mode
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATY</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Display system settings
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>ATZ</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Reboot the system
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-Param=xxx</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Set parameter's value to xxx by name (Param)
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-Param?</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Print parameter's current value by name (Param)
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-?</code>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Display the setting values
            </td>
        </tr>
        <tr>
          <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;" colspan="2">
            <i>AT Commands</i>
          </td>
        </tr>
    </table>

</div>

A parameter is set using the **AT-** prefix, followed by the name of the command with an equals sign and the value to set. For example, sending **AT-SerialSpeed=115200** followed by the <kbd>ENTER</kbd> key (or a carriage return) will change the serial interface speed to 115200bps. This setting can be stored in NVM (non-volatile memory) by sending the **ATW** command.

To query a setting, send the AT command without a value and the device will respond with the current value. For example, sending **AT-SerialSpeed** followed by the <kbd>ENTER</kbd> key will generate the response **115200** followed by **OK**.

The commands are best discussed in groups:

* [Bluetooth Commands](#bluetooth-commands)
* [Serial Commands](#serial-commands)
* [System Commands](#serial-commands)

<!--
* Firmware Commands
* Debug Commands

-->

## Bluetooth Commands

Below is a table for Bluetooth commands, a short description of the command, and its factory default value (if applicable). Right after the table, there is also a list which provides a detailed explanation of each parameter as well.

<div style="text-align: center;">
    <table>
        <tr>
            <th style="text-align: center; border: solid 1px #cccccc; width:250px">AT Command
            </th>
            <th style="text-align: center; border: solid 1px #cccccc;">Command Description
            </th>
            <th style="text-align: center; border: solid 1px #cccccc;">Factory Default Value
            </th>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-BluetoothConnectRetries</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Number of retries of a paired connection
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              5
            </td>
        </tr>        
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-BluetoothConnectTimeoutMs</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Milliseconds before a paired connection attempt times out
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              3000
            </td>
        </tr>        
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-BluetoothEscapeCharacter</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              The character received from the remote system, sought to enter command mode
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">$
            </td>
        </tr>        
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-BluetoothNickname</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              User configurable name to broadcast over Bluetooth during discovery
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              "BlueSMiRF-ABCD", where ABCD is the last four hex digits of the Bluetooth MAC
            </td>
        </tr>        
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-BluetoothPairedMac</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              MAC address of the unit that the user wants to connect to at startup
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
            </td>
        </tr>        
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-BluetoothPairedName</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Name of the unit that the user wants to connect to at startup
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
            </td>
        </tr>        
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-BluetoothPin</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Pin to enter during pairing - only required for older Bluetooth devices
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">1234
            </td>
        </tr>        
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-BluetoothRxSize</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Bluetooth receive buffer size
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              2048
            </td>
        </tr>        
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-BluetoothTxSize</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Bluetooth write buffer size
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              1024
            </td>
        </tr>        
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-BluetoothType</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Bluetooth protocol used for communication
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              0
            </td>
        </tr>
        <tr>
          <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;" colspan="3">
            <i>Bluetooth Commands</i>
          </td>
        </tr>
    </table>

</div>

* **BluetoothConnectRetries** &mdash; If this device has a paired MAC or name, at power up it will attempt to connect to this paired device. A connection is not guaranteed, and the connection will be re-tried this number of times before going into passive, discoverable mode.

* **BluetoothConnectTimeoutMs** &mdash; When this device is connecting to a paired device, if this number of milliseconds expires before a connection is made, the device will attempt to reconnect to the paired device.

* **BluetoothEscapeCharacter** &mdash; This is the character that must be transmitted by a remote device to enter command mode remotely over the Bluetooth connection.

    !!! note
        Escape characters are ignored after `MaxCommandTimeMs` number of milliseconds and within `MinEscapeTimeMs` of other incoming characters.

* **BluetoothNickname** &mdash; The name that is broadcast when other devices are scanning for devices to pair to.

* **BluetoothPairedMac** &mdash; The MAC address of the BlueSMiRF that this device should pair to at power-on. Use the `ATM` command on the remote device to display its MAC address. This command is not normally used; use the button pairing method for an easier way to pair two devices.

* **BluetoothPairedName** &mdash; The name of the BlueSMiRF that this device should pair to at power-on. Use the `BluetoothNickname` command on the remote device to change its paired name. This command is not normally used; use the button pairing method for an easier way to pair two devices.

* **BluetoothPin** &mdash; The pin that is needed during pairing. Only needed on very old Bluetooth USB dongles.

* **BluetoothRxSize** &mdash; The size of the Bluetooth receive buffer. Increase if a large amount of data is coming into the BlueSMiRF over Bluetooth, before the speed of the serial interface can output it.

* **BluetoothTxSize** &mdash; The size of the Bluetooth transmit buffer. Increase if a large amount of data needs to be transmitted over Bluetooth but the connection between devices is poor and multiple retransmissions occur.

* **BluetoothType** &mdash; Controls the Bluetooth protocol. This parameter accepts a `0`, `1`, and `2` for the Bluetooth Protocol as listed below. Note that only the SPP protocol supports pairing.
    * Protocol `0` = Serial Port Profile (SPP)
    * Protocol `1` = Bluetooth Low-Energy (BLE)
    * Protocol `2` = Radio off



## Serial Commands

Below is a table for serial commands, a short description of the command, and its factory default value (if applicable). Right after the table, there is also a list which provides a detailed explanation of each parameter as well.

<div style="text-align: center;">
    <table>
        <tr>
            <th style="text-align: center; border: solid 1px #cccccc; width:250px">AT Command
            </th>
            <th style="text-align: center; border: solid 1px #cccccc;">Command Description
            </th>
            <th style="text-align: center; border: solid 1px #cccccc;">Factory Default Value
            </th>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-FlowControl</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Enable the use of CTS/RTS flow control signals
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              0
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-InvertCts</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Invert the input of CTS
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              0
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-InvertRts</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Invert the output of RTS
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              0
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-PartialFrameTimeoutMs</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Send partial buffer if time expires
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              50
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-RtsStartSendingPercent</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Percent of serialReceiveBuffer that is free when RTS is asserted
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              25
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-RtsStopSendingPercent</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Percent of serialReceiveBuffer that is free when RTS is deasserted
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              5
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-SerialReceiveBufferSize</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Serial receive buffer size
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              51200
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-SerialSpeed</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              The baud rate that the BlueSmiRF operates at.
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              115200
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;">
              <code>AT-SerialTransmitBufferSize</code>
            </td>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              Buffer size to receive bytes from Bluetooth
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              10240
            </td>
        </tr>
        <tr>
          <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;" colspan="3">
            <i>Serial Commands</i>
          </td>
        </tr>
    </table>

</div>

* **FlowControl** - If flow control is enabled, the BlueSMiRF v2 will send data when its CTS pin is driven low (the host system is telling the radio to transmit). If flow control is enabled, BlueSMiRF v2 will drive its RTS low if its serial buffer is full (the radio is telling the host system to hold its horses). By default, flow control is turned off.

* **InvertCts** - By default, InvertCts is false and CTS is high when data is allowed to flow. Enable InvertCts to do the opposite.

* **InvertRts** - By default, InvertRts is false and RTS is high when data is allowed to flow. Enable InvertRts to do the opposite.

* **PartialFrameTimeoutMs** - The number of milliseconds of timeout before a partial packet is sent. For example, if a partial frame of 12 bytes is received, the radio will wait this amount for more bytes before initiating a transmission.

* **RtsStartSendingPercent** - Percent of serialReceiveBuffer that is free when RTS is asserted. Default of 25% of serialReceiveBuffer.

* **RtsStopSendingPercent** - Percent of serialReceiveBuffer that is free when RTS is deasserted. Default of 5% of serialReceiveBuffer.

* **SerialReceiveBufferSize** - Buffer size to receive serial data from the serial port, to be sent over Bluetooth. The default is 51200.

* **SerialSpeed** - The baud rate that the BlueSMiRF operates at. Discrete values 2400, 4800, 9600, 14400, 19200, 38400, 57600, 115200 (default), 230400, 460800, and 921600bps are allowed.   

* **SerialTransmitBufferSize** - Buffer size to receive bytes from Bluetooth, waiting to be printed out the UART. The default is 10240.



## System Commands

Below is a table for system commands, a short description of the command, and its factory default value (if applicable). Right after the table, there is also a list which provides a detailed explanation of each parameter as well.

<div style="text-align: center;">
    <table>
        <tr>
            <th style="text-align: center; vertical-align: middle; border: solid 1px #cccccc; width:250px">AT Command
            </th>
            <th style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">Command Description
            </th>
            <th style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">Factory Default Value
            </th>
        </tr>
        <tr>        
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              <code>AT-EscapeCharacter</code>
            </td>
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              The character sought to enter command mode
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              $
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              <code>AT-EscapeCharacterCount</code>
            </td>
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              The number of escape characters required to enter command mode
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;">
              3
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              <code>AT-LedStyle</code>
            </td>
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              Controls the behavior of the Status and Connect LEDs
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              0
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              <code>AT-MaxCommandTimeMs</code>
            </td>
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              After this time in milliseconds, command mode cannot be entered
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              60000
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              <code>AT-MinEscapeTimeMs</code>
            </td>
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              Serial traffic must stop this amount of milliseconds before an escape character is recognized

            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              2000
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              <code>AT-WiFiPassword</code>
            </td>
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              Password for the SSID, used for over-the-air-updates
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              <code>AT-WiFiSSID</code>
            </td>
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
              SSID used for over-the-air-updates
            </td>
            <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;">
            </td>
        </tr>
        <tr>
          <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;" colspan="3">
            <i>System Commands</i>
          </td>
        </tr>
    </table>
</div>

* **EscapeCharacter** &mdash; The character that must be entered a number of times (`EscapeCharacterCount`) to enter configuration mode. An escape character must be entered before the max time of `MaxCommandTimeMs` and after `MinEscapeTimeMs`.

* **EscapeCharacterCount** &mdash; The number of escape characters needed before command mode is entered. Set to 0 to disable.

* **LedStyle** - Controls how the LEDs behave: CLASSIC = `0`, SERIAL_TRAFFIC = `1`, OFF = `2`.

    * **CLASSIC mode (default)** = `0` &mdash; The **STATUS** LED blinks with TX/RX traffic.

    * **SERIAL_TRAFFIC mode** = `1` &mdash; The **CONNECT** LED blinks with TX traffic and the **STATUS** LED blinks with RX traffic.

    * **OFF mode** = `2` &mdash; The **CONNECT** and **STATUS** LEDs are turned off.

* **MaxCommandTimeMs** &mdash; Once this number of milliseconds has passed, command mode cannot be entered. This is used as a method to prevent a remote system from accidentally entering command mode.

* **MinEscapeTimeMs** &mdash; This number of milliseconds must pass between the last serial character received and an escape character. This is used as a method to prevent a remote system from accidentally entering command mode.

* **WiFiPassword** &mdash; The password for the local WiFi used for firmware updates.

* **WiFiSSID** &mdash; The SSID for the local WiFi used for firmware updates.
