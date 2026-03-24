In this section, we'll go over how to connect to the BlueSMiRF v2.



### Connecting via BlueSMiRF v2 PTH
For a temporary connection to the PTH BlueSMiRF v2, you could use IC hooks to test out the pins. However, you'll need to solder headers or wires of your choice to the board for a secure connection. You can choose between a combination of [header pins and jumper wires](https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering/all), or [stripping wire and soldering the wire](https://learn.sparkfun.com/tutorials/working-with-wire/all) directly to the board.

<div class="grid cards" markdown style="text-align: center;">

-   <a href="https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering/all">
	<figure markdown>
	![How to Solder: Through Hole Soldering](https://cdn.sparkfun.com/c/178-100/assets/learn_tutorials/5/Soldering_Action-01.jpg)
	</figure>

	---

	**How to Solder: Through Hole Soldering**
	</a>



-   <a href="https://learn.sparkfun.com/tutorials/working-with-wire/all">
	<figure markdown>
	![Working with Wire](https://cdn.sparkfun.com/c/178-100/assets/0/5/0/0/f/5138de3cce395fbb1b000002.JPG)
	</figure>

	---

	**Working with Wire**
	</a>

</div>



### Basic Serial UART Connection
At a minimum, you will need to connect serial TX, serial RX, power, and ground for a basic serial UART connection. This connection is needed to send serial data between the two UART devices, configure settings, or even manually upload binaries to the ESP32. Between each serial device, [always make sure to cross the RX and TX lines between serial devices (i.e. RX-to-TX and TX-to-RX)](https://learn.sparkfun.com/tutorials/serial-communication#common-pitfalls). The table indicates below shows color cells being the same for the TXO-to-RXI and RXI-to-TXO. Note that the order of the pins may be different depending on the design, so you may not be able to make a direct connection with the BlueSMiRF v2's 1x6 header.


<div style="text-align: center;">
	<table>
		<tr>
			<th style="text-align: center; border: solid 1px #cccccc;">Serial Device<br />Pinout
			</th>
			<th style="text-align: center; border: solid 1px #cccccc;">BlueSMiRF v2<br />Pinout
			</th>
		</tr>
		<tr>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#d4edda"><font color="#000000">TXO</font>
			</td>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#d4edda"><font color="#000000">RXI</font>
			</td>
		</tr>
		<tr>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#ffdaaf"><font color="#000000">RXI</font>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#ffdaaf"><font color="#000000">TXO</font>
			</td>
		</tr>
		<tr>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#f2dede"><font color="#000000">3V3</font>
			</td>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#f2dede"><font color="#000000">VCC</font>
			</td>
		</tr>
		<tr>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#DDDDDD"><font color="#000000">GND</font>
			</td>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#DDDDDD"><font color="#000000">GND</font>
			</td>
		</tr>
	</table>
</div>


!!! note
	In some cases, you may only need to just wire one serial wire from your serial device to the BlueSMiRF.



### USB-to-Serial Converter to BlueSMiRF v2
Depending on the USB-to-serial converter that you choose, you may need to install drivers. If you've never connected an FTDI or CH340 to your computer before, you may need to install drivers for the USB-to-serial converter. Check out our <a href="https://learn.sparkfun.com/tutorials/how-to-install-ftdi-drivers">How to Install FTDI Drivers</a> or <a href="https://learn.sparkfun.com/tutorials/sparkfun-serial-basic-ch340c-hookup-guide#drivers-if-you-need-them">How to Install CH340 Drivers</a> tutorial for help with the installation.


<div class="grid cards" markdown style="text-align: center;">

-   <a href="https://learn.sparkfun.com/tutorials/how-to-install-ftdi-drivers">
	<figure markdown>
	![How to Install FTDI Drivers](https://cdn.sparkfun.com/c/178-100/assets/learn_tutorials/7/4/USB-mini-B-FTDI.jpg)
	</figure>

	---

	**How to Install FTDI Drivers**
	</a>


-   <a href="https://learn.sparkfun.com/tutorials/how-to-install-ch340-drivers">
	<figure markdown>
	![How to Install CH340 Drivers](https://cdn.sparkfun.com/c/178-100/assets/learn_tutorials/9/0/8/USB-to-serial_converter_CH340-closeup.jpg)
	</figure>

	---

	**How to Install CH340 Drivers**
	</a>

</div>

To make a connection to a USB-to-serial converter, you will need a basic serial connection. There are several converters available such as the FT232 or CH340. Each of these boards include a different USB connector. You will need to manually wire them up using jumper wires as shown in the table and image below.

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
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#d4edda"><font color="#000000">RXI</font>
			</td>
		</tr>
		<tr>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#d4edda"><font color="#000000">TXO</font>
			</td>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#d4edda"><font color="#000000"></font>
			</td>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#ffdaaf"><font color="#000000"></font>
			</td>
			<td style="text-align: center; border: solid 1px #cccccc;" bgcolor="#ffdaaf"><font color="#000000">TXO</font>
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
	The connection also includes two additional connection for flow control: <span STYLE="text-decoration:overline">RTS</span> and CTS. These two connections are not needed for a basic serial UART connection. However, using all six wires can help make a tighter connection on the 1x6 header. The wire colors also connect TXO-to-RXI and RXI-to-TXO to indicate that it is not a direct connection between the two boards and the 1x6 header.

Below is one example between the serial basic breakout (CH340, USB-C) and the BlueSMiRF v2 Header. Male to female jumper wires were connected between the boards.


<figure markdown>
[![USB-to-Serial Converter (CH340) to BlueSMiRF v2 Header with TX-to-RX and RX-to-TX](./assets/img/CH340_BlueSMiRF-v2.jpg){ width="600" }](./assets/img/CH340_BlueSMiRF-v2.jpg "Click to enlarge")
<figcaption markdown>USB-to-Serial Converter (CH340) to BlueSMiRF v2 Header with TX-to-RX and RX-to-TX</figcaption>
</figure>


Adding a simple 1x6 stackable header between the jumper wires will make a quick adapter with the M/F jumper wires and USB-to-serial converter. You'll just need to match the DTR and GND pins. This is useful for those that need to constantly configure the BlueSMiRF v2's settings and re-reconnect to a USB-to-serial converter.


<figure markdown>
[![USB-to-Serial Converter (CH340) to BlueSMiRF v2 Header with an Additional Stackable Header](./assets/img/CH340_stackable_header_BlueSMiRF-v2.jpg){ width="600" }](./assets/img/CH340_stackable_header_BlueSMiRF-v2.jpg "Click to enlarge")
<figcaption markdown>USB-to-Serial Converter (CH340) to BlueSMiRF v2 Header with an Additional Stackable Header</figcaption>
</figure>


!!! tip
	To make it easier to connect visually, try adding a polarity marker with whiteout, Sharpie, or paint. You can even try rotating one of the jumper wires so that the metal tabs is not facing the same direction on one or both ends.


Remember, for those that are using the PTH version, you will need to solder either male headers, female headers, or wires. The type of header or wire will depend on your personal preference and project needs. In this case, we used a 1x6 female header to the board. At the time of writing, there were only female to male jumper wires available so extra long headers were placed between the female header pins. The male header was connected to another serial basic (CH340).


<figure markdown>
[![USB-to-Serial Converter (CH340) to BlueSMiRF v2 PTH](./assets/img/CH340_BlueSMiRF-v2_PTH_female_header.jpg){ width="600" }](./assets/img/CH340_BlueSMiRF-v2_PTH_female_header.jpg "Click to enlarge")
<figcaption markdown>USB-to-Serial Converter (CH340) to BlueSMiRF v2 PTH</figcaption>
</figure>



### BlueSMiRF v2 to Standard Serial UART Port
For boards that already include the footprint for a standard serial UART port, you can connect directly to the pins. You will find these on a few Arduino development boards. The Arduino Pro, Arduino Pro Mini, and LilyPad Arduino 328 Main Board are just a few boards that have the standard port. You will also notice certain boards will have the standard serial UART port labeled as the RTCM Correction Port on SparkFun high precision GNSS breakout boards. For certain boards that have a male header soldered, you may need to consider soldering a 1x6 female header on the BlueSMiRF v2 PTH.


<div class="grid cards" markdown>

<figure markdown>
[![BlueSMiRF v2 Replacing Serial Connection on the Arduino Pro Mini 3.3V Serial Header Port](./assets/img/24113-BlueSMiRF_v2_Arduino_Pro_Mini_3V3_Power_Supply.jpg){ width="600" }](./assets/img/24113-BlueSMiRF_v2_Arduino_Pro_Mini_3V3_Power_Supply.jpg "Click to enlarge")
<figcaption markdown>BlueSMiRF v2 Replacing Serial Connection on the Arduino Pro Mini 3.3V Serial Header Port</figcaption>
</figure>


<figure markdown>
[![RedBoard IoT Development Board ESP32 Connected to the ZED-F9P with the BlueSMiRF v2 Connected to the ZED-F9P's RTCM Correction Port](./assets/img/24113-BlueSMiRF_v2_Arduino_RedBoard_IoT_ESP32_ZED-F9P_RTCM_Correction_Port.jpg){ width="600" }](./assets/img/24113-BlueSMiRF_v2_Arduino_RedBoard_IoT_ESP32_ZED-F9P_RTCM_Correction_Port.jpg "Click to enlarge")
<figcaption markdown>BlueSMiRF v2 Connected to the ZED-F9P's RTCM Correction Port</figcaption>
</figure>


<figure markdown>
[![High Precision GNSS UM980 with the BlueSMiRF v2 Connected to the UM980's RTCM Correction Port](./assets/img/24113-BlueSMiRF_V2_High_Precision_GNSS_UM980_RTCM_Correction_Port.jpg){ width="600" }](./assets/img/24113-BlueSMiRF_V2_High_Precision_GNSS_UM980_RTCM_Correction_Port.jpg "Click to enlarge")
<figcaption markdown>UM980 with the BlueSMiRF v2 Connected to the UM980's RTCM Correction Port</figcaption>
</figure>

</div>


!!! note
	There are older boards that may have a serial port labeled as BlueSMiRF. You will need to wire the connection manually with jumper wires. One example is the SparkFun Arduino ProtoShield where the board uses the older BlueSMiRF pinout. There are jumpers that you can cut on the board and additional PTHs to rewire the pins if you decide to connect directly to the 1x6 header.


	<figure markdown>
	[![SparkFun Arduino ProtoShield Serial Port Highlighted](https://cdn.sparkfun.com/assets/learn_tutorials/7/6/7/SparkFun_ProtoShield-TopView_SoftwareSerialUART.jpg){ width="300" }](https://cdn.sparkfun.com/assets/learn_tutorials/7/6/7/SparkFun_ProtoShield-TopView_SoftwareSerialUART.jpg "Click to enlarge")
	<figcaption markdown>SparkFun Arduino ProtoShield Serial Port Highlighted</figcaption>
	</figure>
