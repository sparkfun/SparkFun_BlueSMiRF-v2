# Button Control

The **PAIR** button on the BlueSMiRF v2 allows the device to enter a few different states.

* [Pairing Mode](../button/#pairing-mode)
* [Factory Reset Mode](../button/#factory-reset-mode)
* [Bootloader Mode](../button/#bluetooth-mode)



## Pairing Mode

Pairing mode is used to connect two BlueSMiRF v2 devices for direct communication. This mode is *not* needed for general discovery; a phone or a laptop can simply discover the BlueSMiRF v2 in its default state.

Holding the Pair button between **4 to 8 seconds** will cause the **Status** and **Connect** LEDs to slowly blink back and forth. If the Pair button is released at this time, the device will enter Pairing mode.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/BlueSMiRF-_v2_Pair_Mode.gif"><img src="../assets/img/BlueSMiRF-_v2_Pair_Mode.gif" width="600px" height="600px" alt="GIF Setting BlueSMiRF v2 in  Pairing Mode"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;">
       <i>GIF Setting BlueSMiRF v2 in Pairing Mode </i>
     </td>
    </tr>
  </table>
</div>

Generally speaking, to create a serial bridge between two BlueSMiRFs, one device needs to be in discoverable mode and the other device needs to discover it. This means, one device needs to have its Pair button held for 4 to 8 seconds then released. It will then fail to discover any compatible devices then enter *Discoverable* mode. Once this is done, the second device needs to have its Pair button held for 4 to 8 seconds, then released. The second device will then scan and discover the first device and pair with it. From this point on, the second device will always try to connect to the first device at power on.

Once a BlueSMiRF has entered Pairing Mode, it will scan for other compatible BlueSMiRF devices. If no other compatible device is found after a few seconds, the BlueSMiRF will enter *Discoverable* mode. The device will broadcast the name '**BlueSMiRF-Pairing**' and wait for an incoming connection.

If a second device enters Pairing Mode, it will scan for other compatible BlueSMiRF devices broadcasting the name (you guessed it) '**BlueSMiRF-Pairing**'. If a device is detected, the second device will connect to the first device, store the MAC address of the first device, and attempt to connect to it at every future power on. The first device will not be aware of or connect to the first device at power on.



## Factory Reset Mode

Holding the Pair button for **more than 8 seconds** will cause the **Status** and **Connect** LEDs to quickly blink back and forth. If the Pair button is released at this time, the device will enter Factory Reset mode.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/BlueSMiRF_V2_Factory_Reset_.gif"><img src="../assets/img/BlueSMiRF_V2_Factory_Reset_.gif" width="600px" height="600px" alt="GIF Factory Reset"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;">
       <i>GIF Factory Reset</i>
     </td>
    </tr>
  </table>
</div>

<!-- A Factor Reset can also -->

After a Factory Reset, all settings are reset to default and/or erased in the following way:

* The baud rate is set to **115200** bps.
* The escape character is set to '`$`' and a count of 3.
* The WiFi **SSID** and **password** are erased.
* Flow control is disabled.
* All the other system settings are returned to default.



## Bootloader Mode

Hold down the PAIR button when the BlueSMiRF v2 is not powered. Applying power will set the microcontroller to bootloader mode. The STATUS LED will be dim indicating that we are in Bootloader Mode. After uploading the firmware binaries to the ESP32, you will need to cycle power to the device as this does not automatically exit the bootloader mode.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/BlueSMiRF_Bootloader_Mode_LED_Dim.gif"><img src="../assets/img/BlueSMiRF_Bootloader_Mode_LED_Dim.gif" width="600px" height="600px" alt="GIF Setting the BlueSMiRF in Bootloader Mode"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;">
       <i>GIF Setting the BlueSMiRF in Bootloader Mode</i>
     </td>
    </tr>
  </table>
</div>


!!! note
    As stated in the [hardware hookup](../hardware_hookup/#usb-to-serial-converter-to-bluesmirf-v2) when connecting a USB-to-serial converter, you will need to manually wire the TX-to-RX and RX-to-TX to a USB-to-serial converter with jumper wires.
