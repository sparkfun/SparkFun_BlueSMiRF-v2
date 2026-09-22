## :material-history: Revision History
For a background on the development and design revisions of the BlueSMiRF, check out the [**Board Revision History** page](revision_history.md) of the guide.



## :material-folder-cog: Design Files
The design of the BlueSMiRF is similar to previous generations. However, we have made a few modifications to the design to simplify how users to the board

- Features an ESP32-PICO-MINI-02 module programmed with our open-source firmware
	- Easily [update the firmware](firmware_update.md) Over-the-Air or through the serial interface
	- Remotely configure the settings with a simple [AT-command set](at_commands.md)
- We have three variants with different connections to simplify hooking up the BlueSMiRF to your project
	- The PTH pad and male header variants have fully, adopted the pin layout from the Bluetooth Mate
		- <span style="text-decoration:overline">`RTS`</span>/`RXI`/`TXO`/`VCC`/<span style="text-decoration:overline">`CTS`</span>/`GND`
		- Pin labels are now provided on both sides of the board
	- On the JST variant, the pin layout and JST connector matches the serial radios
- A [user button](hardware_overview.md#button) has been added to simplify pairing, triggering various modes of operation, and resetting the factory defaults
- Upgraded the voltage regulator to the APA2112K 3.3V, 600mA for increased performance


There are no mounting holes for standoffs on the boards.


<!-- Import the component -->
<script type="module" src="https://ajax.googleapis.com/ajax/libs/model-viewer/3.5.0/model-viewer.min.js"></script>


<div class="grid cards desc" markdown>

-   :kicad-primary:{ .enlarge-logo } Design Files

	---

	- :material-folder-zip: [Schematics](./assets/board_files/schematics.zip)
		- :fontawesome-solid-file-pdf: [PTH Pads](./assets/board_files/schematic-pth.pdf)
		- :fontawesome-solid-file-pdf: [Male Header](./assets/board_files/schematic-smd.pdf)
		- :fontawesome-solid-file-pdf: [JST Connector](./assets/board_files/schematic-jst.pdf)
	- :material-folder-zip: [KiCad Files](./assets/board_files/kicad_files.zip)
		- :material-folder-zip: [PTH Pads](./assets/board_files/kicad_files-pth.zip)
		- :material-folder-zip: [Male Header](./assets/board_files/kicad_files-smd.zip)
		- :material-folder-zip: [JST Connector](./assets/board_files/kicad_files-jst.zip)
	- :material-folder-zip: [Board Dimensions](./assets/board_files/dimensions.zip)
		- :fontawesome-solid-file-pdf: [PTH Pads](./assets/board_files/dimensions-pth.pdf):
			- 1.50" x 0.60" (38.1mm x 15.2mm)
		- :fontawesome-solid-file-pdf: [Male Header](./assets/board_files/dimensions-smd.pdf):
			- 1.74" x 0.60" (44.2mm x 15.2mm)
		- :fontawesome-solid-file-pdf: [JST Connector](./assets/board_files/dimensions-jst.pdf):
			- 1.60" x 0.60" (40.8mm x 15.2mm)
	- :material-folder-zip: [STEP Files](./assets/3d_model/step_files.zip)
		- :material-cube-outline: [PTH Pads](./assets/3d_model/cad_model-pth.step)
		- :material-cube-outline: [Male Header](./assets/3d_model/cad_model-smd.step)
		- :material-cube-outline: [JST Connector](./assets/3d_model/cad_model-jst.step)


-   <!-- Boxes in tabs -->

	=== "PTH Pads"
		<article style="margin: auto; text-align: center;" markdown>
		<model-viewer src="../assets/3d_model/web_model-pth.glb" poster="../assets/3d_model/poster-pth.png" camera-controls tone-mapping="neutral" poster="poster.webp" shadow-intensity="1" exposure="1" camera-orbit="0deg 60deg 0.09m" field-of-view="30deg" style="width: 100%; height: 450px;">
		</model-viewer>

		[Download the `*.step` File](./assets/3d_model/cad_model-pth.step "Click download"){ .md-button .md-button--primary width="250px" }

		</article>


	=== "Male Header"
		<article style="margin: auto; text-align: center;" markdown>
		<model-viewer src="../assets/3d_model/web_model-smd.glb" poster="../assets/3d_model/poster-smd.png" camera-controls tone-mapping="neutral" poster="poster.webp" shadow-intensity="1" exposure="1" camera-orbit="0deg 60deg 0.09m" field-of-view="30deg" style="width: 100%; height: 450px;">
		</model-viewer>

		[Download the `*.step` File](./assets/3d_model/cad_model-smd.step "Click download"){ .md-button .md-button--primary width="250px" }

		</article>


	=== "JST Connector"
		<article style="margin: auto; text-align: center;" markdown>
		<model-viewer src="../assets/3d_model/web_model-jst.glb" poster="../assets/3d_model/poster-jst.png" camera-controls tone-mapping="neutral" poster="poster.webp" shadow-intensity="1" exposure="1" camera-orbit="0deg 60deg 0.09m" field-of-view="30deg" style="width: 100%; height: 450px;">
		</model-viewer>


		[Download the `*.step` File](./assets/3d_model/cad_model-jst.step "Click download"){ .md-button .md-button--primary width="250px" }

		</article>


	???+ tip "Manipulate 3D Model"
		<article style="text-align: center;" markdown>

		| Controls       | Mouse                    | Touchscreen    |
		| :------------- | :----------------------: | :------------: |
		| Zoom           | Scroll Wheel             | 2-Finger Pinch |
		| Rotate         | ++"Left-Click"++ & Drag  | 1-Finger Drag  |
		| Move/Translate | ++"Right-Click"++ & Drag | 2-Finger Drag  |

		</article>

</div>


??? tip "Need Dimensions?"
	For more board dimensions, users can download the [KiCad files](./assets/board_files/kicad_files.zip) for these board. These files can be opened in KiCad and measurements can be made with the measuring tool.


	<div class="grid" markdown>

	<div markdown>

	<figure markdown>
	[![Board Dimensions of PTH variant](./assets/board_files/dimensions-pth.png){ width="450" }](./assets/board_files/dimensions-pth.png "Click to enlarge")
	<figcaption markdown>Dimensions of the BlueSMiRF v2 - PTH.</figcaption>
	</figure>

	</div>


	<div markdown>

	<figure markdown>
	[![Board Dimensions of header variant](./assets/board_files/dimensions-smd.png){ width="450" }](./assets/board_files/dimensions-smd.png "Click to enlarge")
	<figcaption markdown>Dimensions of the BlueSMiRF v2 - Header.</figcaption>
	</figure>

	</div>


	<div markdown>

	<figure markdown>
	[![Board Dimensionsof JST variant](./assets/board_files/dimensions-jst.png){ width="450" }](./assets/board_files/dimensions-jst.png "Click to enlarge")
	<figcaption markdown>Dimensions of the BlueSMiRF v2 - JST.</figcaption>
	</figure>

	</div>

	</div>


	!!! info ":octicons-download-16:{ .heart } KiCad - Free Download!"
		KiCad is free, open-source [CAD]("computer-aided design") program for electronics. Click on the button below to download their software. *(\*Users can find out more information about KiCad from their [website](https://www.kicad.org/).)*


		<article style="text-align: center;" markdown>
		[Download :kicad-primary:{ .enlarge-logo }](https://www.kicad.org/download/ "Go to downloads page"){ .md-button .md-button--primary width="250px" }
		</article>


	??? info ":straight_ruler: Measuring Tool"
		This video demonstrates how to utilize the dimensions tool in KiCad, to include additional measurements:


		<article class="video-500px" style="text-align: center; margin: auto;" markdown>
		<iframe src="https://www.youtube.com/embed/-eXuD8pkCYw" title="KiCad Dimension Tool" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
		![QR code to play video](./assets/img/qr_code/dimension_tool.png){ .qr width="85" }
		</article>



## Board Layout
In this section, we will highlight the hardware and pins that are broken out on the SparkFun BlueSMiRF v2. For the scope of the tutorial, we will be referring to the version with the headers.

<div class="grid" markdown>

<figure markdown>
[![SMD with Headers, Top View](./assets/img/headers-top.jpg){ width="600" }](./assets/img/headers-top.jpg "Click to enlarge")
<figcaption markdown>SMD with Headers, Top View</figcaption>
</figure>


<figure markdown>
[![SMD with Headers, Bottom View](./assets/img/headers-bottom.jpg){ width="600" }](./assets/img/headers-bottom.jpg "Click to enlarge")
<figcaption markdown>SMD with Headers, Bottom View</figcaption>
</figure>

</div>


There is also a version with PTHs out in the wild and it is essentially the same. The only differences are that the pins are broken out to PTHs instead of a SMD right angle male header and the silkscreen labels.


<div class="grid" markdown>

<figure markdown>
[![PTH Version, Top View](./assets/img/pth-top.jpg){ width="600" }](./assets/img/pth-top.jpg "Click to enlarge")
<figcaption markdown>PTH Version, Top View</figcaption>
</figure>


<figure markdown>
[![PTH Version, Bottom View](./assets/img/pth-bottom.jpg){ width="600" }](./assets/img/pth-bottom.jpg "Click to enlarge")
<figcaption markdown>PTH Version, Bottom View</figcaption>
</figure>

</div>


For more information, check out our [Resources and Going Further](resources.md) for the board designs and the ESP32.



## ESP32-PICO-MINI-02
The board includes the smaller ESP32-PICO-MINI-02 module from Espressif. The SparkFun BlueSMiRF v2 is perfect for short range applications that require point-to-point communication. We've written some firmware to allow serial UART data to be sent between two Bluetooth devices. The supported protocols include SPP and BLE. Testing a pair of BlueSMiRF v2s and we got about ~110 feet (~33m) in the SparkFun building. The TX (10k) and RX (50k) buffers are also very large to allow for radio delays. The included firmware also includes a set of AT commands to configure the ESP32. This includes the baud rate, flow control, LED mode, and Over-The-Air (OTA) updates over a 2.4GHz WiFi network to name a few. You can also manually reprogram the ESP32 module using the command line interface as well! Just make sure to connect Tx and Rx between the BlueSMiRF and a USB-to-serial converter.


<figure markdown>
[![ESP32-PICO-MINI-02 Module Highlighted](./assets/img/headers-esp32.jpg){ width="600" }](./assets/img/headers-esp32.jpg "Click to enlarge")
</figure>



## Power
Power is broken out on the 1x6 header through the VCC and GND pins. The recommended input voltage can be between **3.3V** to **5V**. Logic level shifting circuitry is included on the TX and RX pins so that they are 3.3V to 5V tolerant.

- **VCC** / **3V3-5V** &mdash; On the top of the board, the input voltage is labeled as **VCC**. On the back of the board, this is labeled as **3V3-5V**. Voltage is regulated down with the AP2112K 3.3V/600mA voltage regulator from this pin. Typically, one would apply either 3.3V or 5V to this pin. Make sure that power you provide to this pin does not exceed *6 volts*. For advanced users, you can bypass this voltage regulator by adding a solder blob on the jumper labeled as **JP2**. Be careful as the input voltage range is smaller and you may run the risk of damaging the ESP32.
- **GND** &mdash; Of course, is the common, ground voltage (0V reference) for the system.


<div class="grid" markdown>

<figure markdown>
[![Power Highlighted, Top View](./assets/img/headers-power_top.jpg){ width="600" }](./assets/img/headers-power_top.jpg "Click to enlarge")
<figcaption markdown>Power, Top View</figcaption>
</figure>


<figure markdown>
[![Power Highlighted, Bottom View](./assets/img/headers-power_bottom.jpg){ width="600" }](./assets/img/headers-power_bottom.jpg "Click to enlarge")
<figcaption markdown>Power, Bottom View</figcaption>
</figure>

</div>


The current and power consumption depends on what it's doing at the time. Here are some of our results after measuring the current and power consumption at 3.3V. The module can get toasty when pushing serial traffic through but not scary-burn-you-hot.

- Idle: 72mA / 238mW
- Connected with no Serial Traffic: 75mA / 248mW
- Constant Duplex Serial Traffic: 140mA / 462mW

!!! note
	There are also test points on the back of the board that are not labeled for VCC and GND. These are not labeled and are used by SparkFun's production for testing & programming the board using test beds.



## Reset
The reset PTH labeled as <span STYLE="text-decoration:overline">RST</span> will restart the ESP32 whenever the pin is grounded.


<div class="grid" markdown>

<figure markdown>
[![Reset Highlighted, Top View](./assets/img/headers-reset_top.jpg){ width="600" }](./assets/img/headers-reset_top.jpg "Click to enlarge")
<figcaption markdown>Reset, Top View</figcaption>
</figure>


<figure markdown>
[![Reset Highlighted, Bottom View](./assets/img/headers-reset_bottom.jpg){ width="600" }](./assets/img/headers-reset_bottom.jpg "Click to enlarge")
<figcaption markdown>Reset, Bottom View</figcaption>
</figure>

</div>



## Serial UART Port

!!! note
	As stated in the [previous section](revision_history.md), the pinout of the BlueSMiRF v2 is different from previous BlueSMiRFs, hence the version 2. Besides the ESP32 module, the pinout has the same pinout as previous Bluetooth Mates and USB-to-serial converters (i.e. FTDI, CH340, etc.). The board is meant to connect directly with an Arduino Pro, Pro Mini, RTCM Correction Ports on high precision GNSS breakout boards, or any board with a standard serial-to-USB port. Below is the back of the Bluetooth Mate, BlueSMiRF, and BlueSMiRF v2 boards.

	<figure markdown>
	[![Back of Bluetooth Mate, BlueSMiRF, and BlueSMiRF v2](./assets/img/revision-pinout-all.jpg){ width="600" }](./assets/img/revision-pinout-all.jpg "Click to enlarge")
	<figcaption markdown>Back of Bluetooth Mate, BlueSMiRF, and BlueSMiRF v2</figcaption>
	</figure>


Both boards include a standard serial UART header seen on many USB-to-serial converters: <span STYLE="text-decoration:overline">RTS</span>/RXI/TXO/VCC/<span STYLE="text-decoration:overline">CTS</span>/GND. Depending on the version that you purchase, one will be PTH while the other includes right angle male headers. Due to spacing, the PTH version will also have slightly different silkscreen labels.


- **<span STYLE="text-decoration:overline">RTS</span>** / **<span STYLE="text-decoration:overline">RT** &mdash; The Ready to Send is an output and is used for hardware flow control in some serial interfaces. This output is not critical for simple serial communication. If flow control is enabled, BlueSMiRF will drive its RTS low if its serial buffer is full (the radio is telling the host system to hold its horses).
- **RXI** / **RI** &mdash; The serial receive is an input. This input pin receives serial data from another serial device. Logic level circuitry is included on this pin. **It should be connected to the TX of the other device.**
- **TXO** / **TO** &mdash;	The serial transmit is an output. This output pin sends serial data to another device. Logic level circuitry is included on this pin. **It should be connected to the RX of the other device.**
- **VCC**/ **V** / **3V3-5V** &mdash; This input voltage supply signal is routed through a AP2112K voltage regulator and brought down 3.3V for the ESP32. We will assume that it is attached to another device's standard serial port and it is providing power to the BlueSMiRF v2. As stated earlier, the recommended input voltage is between **3.3V to 5V**.
- **<span STYLE="text-decoration:overline">CTS</span>** / **<span STYLE="text-decoration:overline">CT</span>** &mdash; The Clear to Send is an input. CTS is another serial flow control signal. Like RTS, it's not required for most, simple serial interfaces. If flow control is enabled, BlueSMiRF will send data when its CTS pin is driven low (the host system is telling the radio that it's ready for more serial data).
- **GND** / **G** &mdash; The 0V reference voltage, common to any other device connected to the Bluetooth modem.


<div class="grid" markdown>

<figure markdown>
[![Serial Header Highlighted, Top View](./assets/img/headers-pinout_top.jpg){ width="600" }](./assets/img/headers-pinout_top.jpg "Click to enlarge")
<figcaption markdown>Serial Header, Top View</figcaption>
</figure>


<figure markdown>
[![Serial Header Highlighted, Bottom View](./assets/img/headers-pinout_bottom.jpg){ width="600" }](./assets/img/headers-pinout_bottom.jpg "Click to enlarge")
<figcaption markdown>Serial Header, Bottom View</figcaption>
</figure>

</div>


<div class="grid" markdown>

<figure markdown>
[![PTH Serial Header Highlighted, Top View](./assets/img/pth-pinout_top.jpg){ width="600" }](./assets/img/pth-pinout_top.jpg "Click to enlarge")
<figcaption markdown>PTH Serial Header, Top View</figcaption>
</figure>


<figure markdown>
[![PTH Serial Header Highlighted, Bottom View](./assets/img/pth-pinout_bottom.jpg){ width="600" }](./assets/img/pth-pinout_bottom.jpg "Click to enlarge")
<figcaption markdown>PTH Serial Header, Bottom View</figcaption>
</figure>

</div>


!!! tip
	For those that are connecting to the old school RS232 serial port, you will need a [RS232 to TTL converter](https://www.sparkfun.com/products/449) for higher voltages. The RS232 to TTL converter can handle larger voltages designed for RS232.

	<div class="grid cards" markdown>

	-   <a href="https://www.sparkfun.com/sparkfun-rs232-shifter-smd.html">
		<figure markdown>
		![Product thumbnail](https://cdn.sparkfun.com/assets/parts/1/4/9/00449-01a.jpg)
		</figure>

		---

		**SparkFun RS232 Shifter - SMD**
		<br>
		PRT-00449
		</a>

	</div>



## Button
The ++"PAIR"++ button is more than meets the eye. This button has more than one function depending on how long it is pushed down.

- **Short Push** &mdash; Press and hold the button down between **4 to 8 seconds** will initiate pairing with another Bluetooth device. During that period of time, the **Status** and **Connect** LEDs will slowly blink back and forth. When the BlueSMiRF v2 fails to discover any compatible devices, it will enter _Discoverable_ mode.
- **Long Push** &mdash; Press and hold the down for **more than 8 seconds** to set the ESP32 back to its factory default settings.


<figure markdown>
[![Pair Button Highlighted](./assets/img/headers-button.jpg){ width="600" }](./assets/img/headers-button.jpg "Click to enlarge")
</figure>


!!! note
	Users can also set the BlueSMiRF v2 in bootloader mode. In this mode, you can update the firmware manually through serial using a command line interface. Users will need to hold down the ++"PAIR"++ button when the BlueSMiRF v2 is not powered. Applying power will put the microcontroller into bootloader mode.

For more information about using the button for each mode, check out the section about the [device operation](operation_modes.md).

<article style="text-align: center;" markdown>
[Device Operation](operation_modes.md){ .md-button .md-button--primary }
</article>



## LEDs
The board includes the following status LEDs as indicated in the image below.

- **CONNECT** &mdash; The connect LED indicates when the ESP32 is connected to another Bluetooth device. The behavior of the LED will depend on the mode:
	- `0` &mdash; By default, the CONNECT LED will blink until it is connect to another Bluetooth device. Once connected, this LED will remain solid.
	- `1` &mdash; When set to a `1`, the CONNECT LED will blink until it is connected to another Bluetooth device. Once connected, this LED will blink with TX traffic.
- **STATUS** &mdash; The status LED indicates when there is UART traffic. The behavior of the LED will depend on the mode.
	- `0` &mdash; By default, the STATUS LED blinks with any TX/RX traffic.
	- `1` &mdash; When set to a `1`, the STATUS LED blinks with only the RX traffic.


<figure markdown>
[![LEDs Highlighted](./assets/img/headers-LEDs.jpg){ width="600" }](./assets/img/headers-LEDs.jpg "Click to enlarge")
</figure>


The LEDs can also blink at different rates, fade, or become dim when the ++"PAIR"++ button is held down. This is used as an indicator to tell when we are entering pairing, factory reset, or bootloader mode. For more information, check out the section about the [device operation](operation_modes.md).

<article style="text-align: center;" markdown>
[Device Operation](operation_modes.md){ .md-button .md-button--primary }
</article>



## Jumpers

!!!note
	If this is your first time working with jumpers, check out the [How to Work with Jumper Pads and PCB Traces](https://learn.sparkfun.com/tutorials/how-to-work-with-jumper-pads-and-pcb-traces/all) tutorial for more information.

The board includes the following jumpers on the top and bottom of the board.

- **JP2** &mdash; Jumper pad 2 is open by default. This jumper is used to bypass the 3.3V voltage regulator. Add a solder blob to close the jumper to connect VCC to 3.3V.
- **BTN** &mdash; The button jumper are closed by default. This connects the [`PAIR` button](#button) to GPIO pin 0. Cut this jumper to disable the button.


<div class="grid" markdown>

<figure markdown>
[![Jumpers Highlighted, Top View](./assets/img/headers-jumper_vcc.jpg){ width="600" }](./assets/img/headers-jumper_vcc.jpg "Click to enlarge")
<figcaption markdown>Jumpers, Top View</figcaption>
</figure>


<figure markdown>
[![Jumpers Highlighted, Bottom View](./assets/img/headers-jumper_btn.jpg){ width="600" }](./assets/img/headers-jumper_btn.jpg "Click to enlarge")
<figcaption markdown>Jumpers, Bottom View</figcaption>
</figure>

</div>
