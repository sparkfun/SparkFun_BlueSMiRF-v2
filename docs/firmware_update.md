# Updating BlueSMiRF Firmware

From time to time SparkFun will release new firmware for the BlueSMiRF product line to add and improve functionality.  For most users, firmware can be upgraded over WiFi using the [OTA method](firmware_update.md#updating-firmware-over-the-air).

## Updating Firmware Over-The-Air

Once the `AT-WiFiSSID` and `AT-WiFiPassword` settings have been entered for your local WiFi network, the `ATC` command can be issued to check for new firmware. If new firmware is available, send the `ATU` command to begin an update. 

## Updating Firmware Over Serial

Because it's much easier to use, we recommend the OTA firmware update process. If that fails for some reason, the following CLI method can be used.

### Entering Bootload Mode

Hold the **Pair** button while powering the BlueSMiRF. This will cause the ESP32 to enter bootload mode. Once the BlueSMiRF is in bootloader mode, the **Status** LED will be dimly lit and the **Connect** LED will be off. 

We recommend using a [breadboard](https://www.sparkfun.com/products/12002) or [jumper wires](https://www.sparkfun.com/products/11026) to connect the BlueSMiRF to a [USB-to-Serial](https://www.sparkfun.com/products/15096) connection. The TX and RX connections must be crossed over:

* VCC of USB-to-Serial -> VCC of BlueSMiRF 
* TX of USB-to-Serial -> **RX** of BlueSMiRF
* RX of USB-to-Serial -> **TX** of BlueSMiRF
* GND of USB-to-Serial -> GND of BlueSMiRF

### Windows

Identify the COM port the USB-to-Serial device enumerated at. The easiest way to do this is to open the Device Manager:

![CH340 is on COM6 as shown in Device Manager](img/Serial/RTK_Surveyor_-_Firmware_Update_COM_Port.jpg)

*CH340 is on COM6 as shown in Device Manager*

If the COM port is not showing be sure the unit is turned **On**. If an unknown device is appearing, you’ll need to [install drivers for the CH340](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all). Once you know the COM port, open a command prompt (Windows button + r then type ‘cmd’).

![batch_program.bat running esptool](img/Terminal/SparkFun%20RTK%20Firmware%20Update%20CLI.png)

*batch_program.bat running esptool*

Once the correct COM is identified, run 'batch_program.bat' along with the binary file name and COM port. For example *batch_program.bat BlueSMiRF_Firmware_v1_0.bin COM6*. COM6 should be replaced by the COM port you identified earlier.

The batch file runs the following commands:

```
esptool.exe --chip esp32 --port COM3 --baud 921600  --before default_reset --after hard_reset write_flash  -z --flash_mode dio --flash_freq 80m --flash_size 8MB 0x1000 bins/bootloader.bin 0x8000 bins/partitions.bin 0xe000 bins/boot_app0.bin 0x10000 BlueSMiRF_Firmware_v1_0.bin 
```

Where *COM3* is replaced with the COM port that the RTK product enumerated at and *BlueSMiRF_Firmware_vx_x.bin* is the firmware you would like to load.

**Note:** Some users have reported the 921600bps baud rate does not work. Decrease this to 115200 as needed.

Upon completion, the BlueSMiRF must be power cycled to exit bootload mode. Once power cycled, the BlueSMiRF will start running the new firmware.

### macOS / Linux

Get [esptool.py](https://github.com/espressif/esptool). Connect a USB A to C cable from your computer to the USB-to-Serial. Now identify the COM port the RTK enumerated at.

If an unknown device is appearing, you’ll need to [install drivers for the CH340](https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers/all). Once you know the COM port, run the following command:

```
py esptool.py --chip esp32 --port /dev/ttyUSB0 --baud 921600  --before default_reset --after hard_reset write_flash  -z --flash_mode dio --flash_freq 80m --flash_size 8MB 0x1000 bins/bootloader.bin 0x8000 bins/partitions.bin 0xe000 bins/boot_app0.bin 0x10000 BlueSMiRF_Firmware_vx_x.bin 
```

Where */dev/ttyUSB0* is replaced with the port that the USB-to-Serial board enumerated at and *BlueSMiRF_Firmware_vx_x.bin* is the firmware you would like to load.

**Note:** Some users have reported the 921600bps baud rate does not work. Decrease this to 115200 as needed.

Upon completion, the BlueSMiRF must be power cycled to exit bootload mode. Once power cycled, the BlueSMiRF will start running the new firmware.