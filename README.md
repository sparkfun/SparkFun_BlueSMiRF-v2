SparkFun BlueSMiRF v2 Firmware
===========================================================

<table class="table table-hover table-striped table-bordered">
  <tr align="center">
   <td><a href="https://www.sparkfun.com/products/24113"><img src="https://cdn.sparkfun.com/r/600-600/assets/parts/2/4/4/3/8/24113-BlueSMiRF-ESP32-NoHeaders-Feature-NEW.jpg"></a></td>
   <td><a href="https://www.sparkfun.com/products/23287"><img src="https://cdn.sparkfun.com/r/600-600/assets/parts/2/3/4/8/3/23287-BlueSMiRF-ESP32-WithHeaders-Feature-NEW.jpg"></a></td>
  </tr>
  <tr align="center">
    <td><a href="https://www.sparkfun.com/products/24113">SparkFun BlueSMiRF v2 (WRL-24113)</a></td>
    <td><a href="https://www.sparkfun.com/products/23287">SparkFun BlueSMiRF v2 - Headers (WRL-23287)</a></td>
  </tr>
</table>

The [SparkFun BlueSMiRF v2](https://www.sparkfun.com/products/24113) and [SparkFun BlueSMiRF v2 - Headers](https://www.sparkfun.com/products/23287) are point to point serial cable replacements using Bluetooth. Simply throw serial characters at a BlueSMiRF and the data will arrive at the other radio, with guaranteed packet delivery. Baud rates supported up to 921600bps!

This repo houses the [BlueSMiRF Product Manual](https://docs.sparkfun.com/SparkFun_BlueSMiRF-v2) and the firmware that runs on the SparkFun BlueSMiRF ESP32 product line including:

* [SparkFun BlueSMiRF v2](https://www.sparkfun.com/products/24113)
* [SparkFun BlueSMiRF v2 - Headers](https://www.sparkfun.com/products/23287)

For compiled binaries of the firmware, please see [SparkFun BlueSMiRF ESP32 Firmware Binaries](https://github.com/sparkfun/SparkFun_BlueSMiRF-v2_Binaries).

Repository Contents
-------------------

* **/Firmware** - Source code for SparkFun BlueSMiRF firmware as well as various feature unit tests
* **/Documents** - Datasheets for various components.
* **/docs** - Markdown pages for the [BlueSMiRF Product Manual](https://docs.sparkfun.com/SparkFun_BlueSMiRF-v2/)

Repository Branch Structure
---------------------------

This repository has two long-term branches: `main` and `release_candidate`.

With respect to the firmware, `main` is a branch where only changes that are appropriate for all users are applied. Thus, following `main` means updating to normal releases, and perhaps bugfixes to those releases.

In contrast, `release_candidate` is where new code is added as it is developed.

The documentation source code is in docs/ on `main`.  It is built automatically on push and stored in the branch `gh-pages`, from which it is served at the above URL. Documentation changes are pushed directly to main.

Release Process
---------------

A release is made by merging `release_candidate` back to `main`, and then applying a tag to that commit on `main`.

A pre-release is often created using the latest stable release candidate. These binaries will have extra debug statements turned on that will not be present in a formal release, but should not affect the behavior of the firmware.

The command-line interface is also available. You’ll need to download the [RTK Firmware Binaries](https://github.com/sparkfun/SparkFun_RTK_Firmware_Binaries) repo. This repo contains the binaries but also various supporting tools including esptool.exe and the three binaries required along with the firmware (bootloader, partitions, and app0).

## Updating Firmware From CLI

Because it's much easier to use, we recommend the OTA firmware update process. If that fails for some reason, the following CLI method can be used.

### Entering Bootload Mode

Hold the **Pair** button while powering the BlueSMiRF. This will cause the ESP32 to enter bootload mode. Once the BlueSMiRF is in bootloader mode, the **Status** LED will be dimly lit, the **Connect** LED will be off. 

We recommend using a breadboard or jumper wires to connect the BlueSMiRF to a USB-to-Serial connection. The TX and RX connections must be crossed over:

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

License Information
-------------------

This product is _**open source**_!  Please feel free to [contribute](https://docs.sparkfun.com/SparkFun_BlueSMiRF-v2/contribute/) to both the firmware and documentation.

Various bits of the code have different licenses applied. Anything SparkFun wrote is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!

Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.
