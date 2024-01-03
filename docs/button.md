# Button Control

The **PAIR** button on the BlueSMiRF allows the device to enter a few different states.

* Pairing Mode
* Factory Reset Mode

## Pairing Mode

Pairing mode is used to connect two BlueSMiRF devices for direct communication. This mode is *not* needed for general discovery; a phone or a laptop can simply discover a BlueSMiRF in its default state.

Holding the Pair button for more than 4 seconds will cause the **Status** and **Connect** LEDs to slowly blink back and forth. If the Pair button is released at this time, the device will enter Pairing mode.

Generally speaking, to create a serial bridge between two BlueSMiRFs, one device needs to be in discoverable mode and the other device needs to discover it. This means, one device needs to have its Pair button held for 4+ seconds then released. It will then fail to discover any compatible devices then enter *Discoverable* mode. Once this is done, the second device needs to have its Pair button held for 4+ seconds, then released. The second device will then scan and discover the first device and pair with it. From this point on, the second device will always try to connect to the first device at power on. 

Once a BlueSMiRF has entered Pairing Mode it will scan for other compatible BlueSMiRF devices. If no other compatible device is found after a few seconds, the BlueSMiRF will enter *Discoverable* mode. The device will broadcast the name 'BlueSMiRF-Pairing' and wait for an incoming connection.

If a second device enters Pairing Mode, it will scan for other compatible BlueSMiRF devices broadcasting the name (you guessed it) 'BlueSMiRF-Pairing'. If a device is detected, the second device will connect to the first device, store the MAC address of the first device, and attempt to connect to it at every future power on. The first device will not be aware of or connect to the first device at power on.

## Factory Reset Mode

Holding the Pair button for more than 8 seconds will cause the **Status** and **Connect** LEDs to quickly blink back and forth. If the Pair button is released at this time, the device will enter Factory Reset mode.

A Factor Reset can also 

After a Factory Reset, all settings are reset to default and/or erased in the following way:

* The baud rate is set to 115200bps.
* The escape character is set to '$' and a count of 3.
* The WiFi SSID and password are erased.
* Flow control is disabled.
* All the other system settings are returned to default.
