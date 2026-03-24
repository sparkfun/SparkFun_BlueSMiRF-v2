!!! note
	Bluetooth classic (Serial Port Profile or SPP) is primarily supported. This Bluetooth protocol is supported on Android phones, most desktops, and laptops. The BlueSMiRF v2 also supports the BLE protocol, available on all Apple phones.

In this example, we will connect a BlueSMiRF v2 to a smartphone and send serial data using the Bluetooth classic protocol (also known as Serial Port Profile or SPP).

The image below shows the Serial Basic (CH340, USB-C) connected to the BlueSMiRF v2 Header using M/F jumper wires. Headers were used to easily remove and reconnect the BlueSMiRF v2 with headers.


<figure markdown>
[![BlueSMiRF v2 to SmartPhone Bluetooth Classic Serial Terminal](./assets/img/24113-BlueSMiRF_V2_Smartphone_Bluetooth_Classic_Serial_Terminal.jpg){ width="600" }](./assets/img/24113-BlueSMiRF_V2_Smartphone_Bluetooth_Classic_Serial_Terminal.jpg "Click to enlarge")
<figcaption markdown>BlueSMiRF v2 to SmartPhone Bluetooth Classic Serial Terminal with the RedBoard Plus</figcaption>
</figure>



### Download the Serial Bluetooth Terminal App
Head to your smartphone's app store. In this case, we were on an Android smartphone and used Google Play Store to download the [**Serial Bluetooth Terminal** app](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en_US&gl=US&pli=1). This app is great for development, debugging, and general use when using the BlueSMiRF's SPP and BLE protocols.


<article style="text-align: center;" markdown>
[Google Play: Serial Bluetooth Terminal](https://play.google.com/store/apps/details?id=de.kai_morich.serial_bluetooth_terminal&hl=en_US&gl=US&pli=1){ .md-button .md-button--primary }
</article>


!!! note
	If you have a different phone OS, there are many apps like the Serial Bluetooth Terminal available for different smartphones. Just do a search in your app store.



### Pair the BlueSMiRF v2 with your Smartphone
Once downloaded, turn on your Bluetooth and open your Bluetooth settings. Scroll down until you see the available devices. With BlueSMiRF powered up and in range, you should be able to see the device in discoverable mode listed as **BlueSMiRF-ABCD**, where **ABCD** is the last four hex digits of the Bluetooth MAC. In this case, it was **BlueSMiRF-5A66**.


<figure markdown>
[![](./assets/img/Bluetooth_Connect_BlueSMiRF_V2_a.jpg){ width="300" }](./assets/img/Bluetooth_Connect_BlueSMiRF_V2_a.jpg "Click to enlarge")
<figcaption markdown>BlueSMiRF Discovered on Android Smartphone</figcaption>
</figure>


Click on the device to begin pairing. A message will pop up asking if you want to pair with the device. At this point, select `Pair`.


<figure markdown>
[![](./assets/img/Bluetooth_Connect_BlueSMiRF_V2_b.jpg){ width="300" }](./assets/img/Bluetooth_Connect_BlueSMiRF_V2_b.jpg "Click to enlarge")
<figcaption markdown>BlueSMiRF Discovered on Android Smartphone</figcaption>
</figure>


Scroll up to your Paired devices and look for the BlueSMiRF to verify that it has paired with your phone.


<figure markdown>
[![BlueSMiRF-5A66 Showing Up as a Paired Bluetooth Device](./assets/img/Bluetooth_Connect_BlueSMiRF_V2_c.jpg){ width="300" }](./assets/img/Bluetooth_Connect_BlueSMiRF_V2_c.jpg "Click to enlarge")
<figcaption markdown>BlueSMiRF-5A66 Showing Up as a Paired Bluetooth Device</figcaption>
</figure>



### Sending Characters Between a BlueSMiRF and Smartphone
Open the Serial Bluetooth Terminal app.


<figure markdown>
[![Serial Bluetooth Terminal Opened](./assets/img/BlueSMiRF_v2_Serial_Terminal_2_a.jpg){ width="300" }](./assets/img/BlueSMiRF_v2_Serial_Terminal_2_a.jpg "Click to enlarge")
<figcaption markdown>Serial Bluetooth Terminal Opened</figcaption>
</figure>


Click on the connect icon to the left of the trash can icon. If all is well, you will get a message indicating that the BlueSMiRF is connected.


<figure markdown>
[![Connected to BlueSMiRF-5A66](./assets/img/BlueSMiRF_v2_Serial_Terminal_2_b.jpg){ width="300" }](./assets/img/BlueSMiRF_v2_Serial_Terminal_2_b.jpg "Click to enlarge")
<figcaption markdown>Connected to BlueSMiRF-5A66</figcaption>
</figure>


Open a serial terminal, and connect to the BlueSMiRF at **115200 baud**. In this case, it was connected to **COM13**. Start typing characters in the serial terminal. You should see them in the Serial Bluetooth Terminal app!


<div class="grid" markdown style="place-items: center;">

<figure markdown>
[![First Serial Terminal](./assets/img/BlueSMiRF_v2_Serial_Terminal_1_a.JPG){ width="600" }](./assets/img/BlueSMiRF_v2_Serial_Terminal_1_a.JPG "Click to enlarge")
<figcaption markdown>Serial Terminal Connected to BlueSMiRF v2</figcaption>
</figure>


<figure markdown>
[![](./assets/img/BlueSMiRF_v2_Serial_Terminal_2_c.jpg){ width="300" }](./assets/img/BlueSMiRF_v2_Serial_Terminal_2_c.jpg "Click to enlarge")
<figcaption markdown>Receiving Characters through the Serial Bluetooth Terminal</figcaption>
</figure>

</div>


Type a message and send them using the Serial Bluetooth Terminal app. You should see the message in the serial terminal!


<div class="grid" markdown style="place-items: center;">

<figure markdown>
[![](./assets/img/BlueSMiRF_v2_Serial_Terminal_1_d.JPG){ width="600" }](./assets/img/BlueSMiRF_v2_Serial_Terminal_1_d.JPG "Click to enlarge")
<figcaption markdown>Receiving Characters through First Serial Terminal</figcaption>
</figure>


<figure markdown>
[![](./assets/img/BlueSMiRF_v2_Serial_Terminal_2_d.jpg){ width="300" }](./assets/img/BlueSMiRF_v2_Serial_Terminal_2_d.jpg "Click to enlarge")
<figcaption markdown>Sending Characters through Serial Bluetooth Terminal</figcaption>
</figure>

</div>


Sending serial data between the BlueSMiRF and smartphone using the Serial Bluetooth Terminal app is only the start! For example, you can use BlueSMiRF v2 and a smartphone to send/receive correction data to/from a high precision GNSS module. Try looking at the following methods to send data between the BlueSMiRF v2 and a smartphone. Just make sure to adjust the baud rate of the BlueSMiRF to match the high precision GNSS module's baud rate (for the u-blox modules, the correction port's default is typically set to **38400 baud**). These are only a few ways to connect a high precision GNSS module to your smartphone's GNSS app to achieve an RTK Fixed Mode.

- [Connecting the ZED-F9P to a Correction Source using an NTRIP Client](https://learn.sparkfun.com/tutorials/gps-rtk2-hookup-guide#connecting-the-zed-f9p-to-a-correction-source)
- [Setting the ZED-F9P as a Correction Source](https://learn.sparkfun.com/tutorials/gps-rtk2-hookup-guide#setting-the-zed-f9p-as-a-correction-source)
