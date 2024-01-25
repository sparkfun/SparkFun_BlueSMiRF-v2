From time to time, SparkFun will release new firmware for the BlueSMiRF v2 product line to add and improve functionality.  For most users, firmware can be upgraded over a 2.4GHz WiFi network using the [OTA method](firmware_update.md#updating-firmware-over-the-air). Users can also update the firmware manually using a Command Line Interface (CLI)



### Updating Firmware Over-The-Air (OTA)

Once the `AT-WiFiSSID` and `AT-WiFiPassword` settings have been entered for your local WiFi network, the `ATC` command can be issued to check for new firmware. If new firmware is available, send the `ATU` command to begin an update.

# Manually Updating Firmware Over Serial

Because it's much easier to use, we recommend the OTA firmware update process. If that fails for some reason, the following CLI method can be used.



### Entering Bootloader Mode

Hold the **PAIR** button while powering the BlueSMiRF v2. This will cause the ESP32 to enter bootloader mode. Once the BlueSMiRF v2 is in bootloader mode, the **STATUS** LED will be dimly lit and the **CONNECT** LED will be off.

We recommend using a [breadboard](https://www.sparkfun.com/products/12002) or [jumper wires](https://www.sparkfun.com/products/11026) to connect the BlueSMiRF to a [USB-to-Serial](https://www.sparkfun.com/products/15096) connection. At a minimum, you will need to connect the UART pins, power, and ground as stated in the hardware hookup. Remember, the TX and RX connections must be crossed over.

<div style="text-align: center;">
    <table>
        <tr>
            <th style="text-align: center; border: solid 1px #cccccc;">USB-to-Serial Converter<br />Pinout
            </th>
            <th style="text-align: center; border: solid 1px #cccccc;" colspan="2">Intermediate Wire Connection</th>
            <th style="text-align: center; border: solid 1px #cccccc;">BlueSMiRF v2<br />Pinout
            </th>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#fff3cd"><font color="#000000">DTR</font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#fff3cd"><font color="#000000"></font>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#fff3cd"><font color="#000000"></font>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#fff3cd"><font color="#000000"><span STYLE="text-decoration:overline">RTS</span></font>
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#ffdaaf"><font color="#000000">RXI</font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#ffdaaf"><font color="#000000"></font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#d4edda"><font color="#000000"></font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#d4edda"><font color="#000000"><b>RXI</b></font>
            </td>
        </tr>
        <tr>        
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#d4edda"><font color="#000000">TXO</font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#d4edda"><font color="#000000"></font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#ffdaaf"><font color="#000000"></font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#ffdaaf"><font color="#000000"><b>TXO</b></font>
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#f2dede"><font color="#000000">3V3</font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#f2dede"><font color="#000000"></font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#f2dede"><font color="#000000"></font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#f2dede"><font color="#000000">VCC</font>
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#cce5ff"><font color="#000000">CTS</font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#cce5ff"><font color="#000000"></font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#cce5ff"><font color="#000000"></font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#cce5ff"><font color="#000000">CTS</font>
            </td>
        </tr>
        <tr>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#DDDDDD"><font color="#000000">GND</font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#DDDDDD"><font color="#000000"></font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#DDDDDD"><font color="#000000"></font>
            </td>
            <td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#DDDDDD"><font color="#000000">GND</font>
            </td>
        </tr>
    </table>
</div>

!!! note
    The connection also includes two additional connection for flow control: <span STYLE="text-decoration:overline">RTS</span> and <span STYLE="text-decoration:overline">CTS</span>. These two connections are not needed for a basic serial UART connection. However, using all six wires can help make a tighter connection on the 1x6 header. The wire colors also connect TXO-to-RXI and RXI-to-RXO to indicate that it is not a direct connection between the two boards and the 1x6 header.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/CH340_stackable_header_BlueSMiRF-v2.jpg"><img src="../assets/img/CH340_stackable_header_BlueSMiRF-v2.jpg" width="600px" height="600px" alt="USB-to-Serial Converter (CH340) to BlueSMiRF v2 Header with an Additional Stackable Header"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><i>USB-to-Serial Converter (CH340) to BlueSMiRF v2 Header with an Additional Stackable Header</i>
     </td>
    </tr>
  </table>
</div>

### Windows

Identify the COM port the USB-to-Serial device enumerated at. The easiest way to do this is to open the Device Manager under the **Ports (COM & LPT)** tree:

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/Device_Manager_CH340_COM_Port.jpg"><img src="../assets/img/Device_Manager_CH340_COM_Port.jpg" width="300px" height="300px" alt="CH340 is on COM10 as shown in Device Manager"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><i>CH340 is on COM10 as shown in Device Manager</i></td>
     </tr>
  </table>
</div>

If the COM port is not showing, be sure the unit is turned **On**. If an unknown device is appearing, you’ll need to install drivers for your USB-to-serial device ([we'll assume that you are using the CH340](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all)).

Once the correct COM port is identified, head to the [GitHub repo for the BlueSMiRF v2 binaries](https://github.com/sparkfun/SparkFun_BlueSMiRF-v2_Binaries) and download all the contents. Unzip the contents in a known directory and copy the path.

<div style="text-align: center"><a href="https://github.com/sparkfun/SparkFun_BlueSMiRF-v2_Binaries/archive/main.zip" class="md-button">Download BlueSMiRF V2 Binaries GitHub Repo (ZIP)</a></div>

Open a command prompt (Windows button + <kbd>r</kbd> then type ‘ <kbd>cmd</kbd> ’). Head to the directory where you unzipped the folder. You'll need to use the `cd` commmand, paste the path where you unzipped the folder, and hit the <kbd>enter</kbd> key.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/Change_Path_Blue_SMiRF_Binaries_Folder.JPG"><img src="../assets/img/Change_Path_Blue_SMiRF_Binaries_Folder.JPG" width="600px" height="600px" alt="Change Path to BlueSmiRF Binaries Folder"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><i>Change Path to BlueSmiRF Binaries Folder</i></td>
    </tr>
  </table>
</div>



You'll then need to run the '**batch_program.bat**' along with the binary file name and COM port. Enter the following command below, where **COM4** should be replaced by the COM port you identified earlier and **BlueSMiRF_Firmware_v1_0.bin** is the firmware that you are updating to. Make sure to send an additional key to run the batch file.

``` bash
batch_program.bat BlueSMiRF_Firmware_v1_0.bin COM4
```

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/batch_running_esptool.JPG"><img src="../assets/img/batch_running_esptool.JPG" width="600px" height="600px" alt="batch_program.bat running esptool"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><i>batch_program.bat running esptool</i></td>
    </tr>
  </table>
</div>

After about 20 seconds, you should see the following message: `Done programming! Ready for next board.`

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/Successfully_Programmed_BlueSMiRF_ESP32.JPG"><img src="../assets/img/Successfully_Programmed_BlueSMiRF_ESP32.JPG" width="600px" height="600px" alt="Successfully Programmed BlueSMiRF V2 - ESP32"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><i>Successfully Programmed BlueSMiRF V2 - ESP32</i></td>
    </tr>
  </table>
</div>

The batch file runs the following commands, where *COM4* is replaced with the COM port that the BlueSMiRF product enumerated at and *BlueSMiRF_Firmware_vx_x.bin* is the firmware you would like to load.

<pre>
    <code class="language-bash" style="white-space: pre-wrap;">esptool.exe --chip esp32 --port COM4 --baud 921600 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 80m --flash_size 8MB 0x1000 bins/bootloader.bin 0x8000 bins/partitions.bin 0xe000 bins/boot_app0.bin 0x10000 BlueSMiRF_Firmware_v1_0.bin</code>
</pre>

!!! note
    Some users have reported the `921600` baud rate does not work. Decrease this to `115200` as needed.

!!! tip
    Finished programming the ESP32? Type <kbd>CTRL</kbd> + <kbd>C</kbd> , <kbd>Y</kbd> , and <kbd>ENTER</kbd> to exit the batch file. You can also close the window.

Upon completion, the BlueSMiRF V2 must be power cycled to exit bootloader mode. Once power cycled, the BlueSMiRF will start running the new firmware.

!!! note
    We recommend disconnecting the USB cable from the USB-to-Serial Converter or your computer's COM port.



### macOS / Linux

Get [esptool.py](https://github.com/espressif/esptool). Connect a USB A to C cable from your computer to the USB-to-Serial. Now identify the COM port the USB-to-serial device enumerated at.

If the COM port is not showing, be sure the unit is turned **On**. If an unknown device is appearing, you’ll need to install drivers for your USB-to-serial device ([we'll assume that you are using the CH340](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all)).

Once the correct COM port is identified, head to the [GitHub repo for the BlueSMiRF v2 binaries](https://github.com/sparkfun/SparkFun_BlueSMiRF-v2_Binaries) and download all the contents. Unzip the contents in a known directory and copy the path.

<div style="text-align: center"><a href="https://github.com/sparkfun/SparkFun_BlueSMiRF-v2_Binaries/archive/main.zip" class="md-button">Download BlueSMiRF V2 Binaries GitHub Repo (ZIP)</a></div>


Open a Terminal window and run the following command, where */dev/ttyUSB0* is replaced with the port that the USB-to-Serial board enumerated at and *BlueSMiRF_Firmware_vx_x.bin* is the firmware you would like to load.

<pre>
    <code class="language-bash" style="white-space: pre-wrap;">py esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 921600 --before default_reset --after hard_reset write_flash  -z --flash_mode dio --flash_freq 80m --flash_size 8MB 0x1000 bins/bootloader.bin 0x8000 bins/partitions.bin 0xe000 bins/boot_app0.bin 0x10000 BlueSMiRF_Firmware_vx_x.bin</code>
</pre>

!!! note
    Some users have reported the `921600` baud rate does not work. Decrease this to `115200` as needed.

!!! tip
    Finished programming the ESP32? Type <kbd>CTRL</kbd> + <kbd>C</kbd> , <kbd>Y</kbd> , and <kbd>ENTER</kbd> to exit the batch file. You can also close the window.

Upon completion, the BlueSMiRF must be power cycled to exit bootloader mode. Once power cycled, the BlueSMiRF will start running the new firmware.

!!! note
    We recommend disconnecting the USB cable from the USB-to-Serial Converter or your computer's COM port.
