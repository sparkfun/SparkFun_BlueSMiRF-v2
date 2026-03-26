Before we go over the hardware though, let's compare previous SparkFun BlueSMiRF versions with the BlueSMiRF v2!

Back in April 2005, we originally released the BlueSMiRF (Bluetooth Serial Miniature RF) Link version 1 with BlueRadio's WML-C40AH. They came in two flavors: one with 4-pins for the basic BlueSMiRF consisting of PWR/GND/TX-O/RX-I, and the other with 6-pins for the extended BlueSMiRF consisting of RTS/RX-I/TX-O/GND/PWR/CTS. Over the years, the extended 1x6 pin became the "standard" for the BlueSMiRF.


<div class="grid" markdown>

<div markdown>

<figure markdown>
[![Basic BlueSMiRF](./assets/img/revision-original-basic.png){ width="600" }](./assets/img/revision-original-basic.png "Click to enlarge")
<figcaption markdown>Basic BlueSMiRF</figcaption>
</figure>

</div>

<div markdown>

<figure markdown>
[![Extended BlueSMiRF](./assets/img/revision-original-ext.png){ width="550" }](./assets/img/revision-original-ext.png "Click to enlarge")
<figcaption markdown>Extended BlueSMiRF</figcaption>
</figure>

</div>

</div>


We even saw changes in the Bluetooth modems! The BlueRadio's WML-C40AH modems eventually switched over to Roving Network's RN-41 and RN-42. Each version had different ranges and transmit power.


<div class="grid" markdown>

<div markdown>

<figure markdown>
[![BlueSMiRF Gold (RN-41)](./assets/img/revision-gold.jpg){ width="600" }](./assets/img/revision-gold.jpg "Click to enlarge")
<figcaption markdown>BlueSMiRF Gold (RN-41)</figcaption>
</figure>

</div>

<div markdown>

<figure markdown>
[![BlueSMiRF Silver (RN-42)](./assets/img/revision-silver.jpg){ width="600" }](./assets/img/revision-silver.jpg "Click to enlarge")
<figcaption markdown>BlueSMiRF Silver (RN-42)</figcaption>
</figure>

</div>

</div>


The 1x6 pins also were rearranged for the SparkFun Bluetooth Mates similar to the USB-to-Serial Converters.



<div class="grid" markdown>

<div markdown>

<figure markdown>
[![Pin layout between BlueSMiRF & Bluetooth Mate](./assets/img/revision-pinout-mate.jpg){ width="600" }](./assets/img/revision-pinout-mate.jpg "Click to enlarge")
<figcaption markdown>A comparison of the pin layouts between the Bluetooth Mate and regular BlueSMiRF</figcaption>
</figure>

</div>


<div markdown>

<figure markdown>
[![BlueSMiRF mate connected to serial programming headers](./assets/img/example-mate-serial_interface.png){ width="600" }](./assets/img/example-mate-serial_interface.png "Click to enlarge")
<figcaption markdown>BlueSMiRF Mate connected to the headers for the serial programming interface of the Arduino Pro.</figcaption>
</figure>

</div>

</div>

Fast forward to January 2024 (my how time flies!), the BlueSMiRFs v2 is brought back to life! So what's different from the previous versions? Well, the differences to note with the BlueSMiRF v2 include:

- ESP32-PICO-MINI-02 module
- The firmware can be easily updated Over-the-Air or through a command line interface
- The pinout matches the previous Bluetooth Mates and standard USB-to-serial converters: <span style="text-decoration:overline">RTS</span>/RXI/TXO/VCC/<span style="text-decoration:overline">CTS</span>/GND
- Excluding the JST variant, labels included on both sides of the board instead of just the bottom
- Multi-use button for setting the board in bootloader mode, pairing, and factory reset instead of a PTH PIO4 for factory reset
- Jumper to disable the button
- <span style="text-decoration:overline">CTS</span>/<span style="text-decoration:overline">RTS</span> jumper was removed
- APA2112K 3.3V, 600mA voltage regulator instead of the MIC5205 3.3V, 150mA
- A bypass jumper for the voltage regulator was added
- Size is slightly smaller measuring 38.1mm x 15.2mm
