# Introduction
<div class="grid cards desc" markdown>

<div markdown>

<article class="video-container" style="margin: auto;" markdown>
<iframe width="560" height="315" src="https://www.youtube.com/embed/i8u3W0jVFTw?si=9iwrsCm9Ih9n9VCz" title="Product Showcase: SparkFun BlueSMiRF v2" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>
</article>

</div>


The [SparkFun BlueSMiRF v2](https://www.sparkfun.com/products/24113) is a wireless Bluetooth&reg; serial link. This version of the popular BlueSMiRF uses the ESP32. These boards work as a wireless serial UART pipe and are a great wireless replacement for serial cables. Simply pair, connect, and transmit serial data between your TX/RX lines! Any serial stream from 2400 to 921600 baud can be passed seamlessly between two devices. In this tutorial, we'll go over the hardware and how to hookup the breakout board. We will also go over how to connect to a smartphone and a basic Arduino example to get started!


<div class="grid cards" markdown>

-   <a href="https://www.sparkfun.com/products/24113">
	**SparkFun BlueSMiRF v2 - PTH Pins**<br>
	**SKU:** WRL-24113

	---

	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com/assets/parts/2/4/4/3/8/24113-BlueSMiRF-ESP32-NoHeaders-Feature-NEW.jpg)
	</figure></a>


	<article style="text-align: center;" markdown>
	[Purchase from SparkFun :fontawesome-solid-cart-plus:](https://www.sparkfun.com/products/24113){ .md-button .md-button--primary }
	</article>


-   <a href="https://www.sparkfun.com/products/23287">
	**SparkFun BlueSMiRF v2 - Male Header**<br>
	**SKU:** WRL-23287

	---

	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com/assets/parts/2/3/4/8/3/23287-BlueSMiRF-ESP32-WithHeaders-Feature-NEW.jpg)
	</figure></a>


	<article style="text-align: center;" markdown>
	[Purchase from SparkFun :fontawesome-solid-cart-plus:](https://www.sparkfun.com/products/23287){ .md-button .md-button--primary }
	</article>

</div>



## Required Materials
To follow along with the examples in this tutorial, you will need the following materials. You may not need everything though depending on what you have. Add it to your cart, read through the guide, and adjust the cart as necessary. We recommend the board with headers to minimize the amount of soldering to your application.

- 2x [SparkFun BlueSMiRF v2 - Headers [WRL-23287]](https://www.sparkfun.com/products/23287)
- 2x [Jumper Wires Premium 6" M/F Pack of 10 [PRT-09140]](https://www.sparkfun.com/products/9140)
- 2x [SparkFun Serial Basic Breakout - CH340C and USB-C [DEV-15096]](https://www.sparkfun.com/products/15096)
- 2x [Reversible USB A to C Cable - 0.8m [CAB-15425]](https://www.sparkfun.com/products/15425)

<div class="grid cards" markdown>

-   <a href="https://www.sparkfun.com/products/23287">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com/r/600-600/assets/parts/2/3/4/8/3/23287-BlueSMiRF-ESP32-WithHeaders-Feature-NEW.jpg)
	</figure>

	---

	**SparkFun BlueSMiRF v2 - Headers**

	WRL-23287
	</a>


-   <a href="https://www.sparkfun.com/products/9140">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/2/5/5/7/09140-02-L.jpg)
	</figure>

	---

	**Jumper Wires Premium 6" M/F Pack of 10**

	PRT-09140
	</a>


-   <a href="https://www.sparkfun.com/products/15096">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/1/3/4/5/2/15096-SparkFun_Serial_Basic_Breakout_-_CH340C_and_USB-C-01.jpg)
	</figure>

	---

	**SparkFun Serial Basic Breakout - CH340C and USB-C**

	DEV-15096
	</a>


-   <a href="https://www.sparkfun.com/products/15425">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/1/3/9/8/4/15425-Reversible_USB_A_to_C_Cable_-_0.8m-02.jpg)
	</figure>

	---

	**Reversible USB A to C Cable - 0.8m**

	CAB-15425
	</a>


</div>



### Tools *(Optional)*

You will need a soldering iron, solder, and [general soldering accessories](https://www.sparkfun.com/categories/49) for a secure connection when using the plated through holes. You may also need to solder headers or wires to any devices that the BlueSMiRF v2 is connecting to.

- [Soldering Iron [TOL-14456]](https://www.sparkfun.com/products/14456)
- [Solder Lead Free - 15-gram Tube [TOL-9163]](https://www.sparkfun.com/products/9163)
- [Flush Cutters - Xcelite [TOL-14782]](https://www.sparkfun.com/products/14782)
- [Hook-Up Wire - Assortment (Stranded, 22 AWG) [PRT-11375]](https://www.sparkfun.com/products/11375)
- [Wire Strippers - 20-30 AWG [TOL-24771]](https://www.sparkfun.com/products/24771)

<div class="grid cards" markdown>

-   <a href="https://www.sparkfun.com/products/14456">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/1/2/4/9/0/14456-01.jpg)
	Soldering Iron - 60W (Adjustable Temperature)">
	</figure>

	---

	**Soldering Iron - 60W (Adjustable Temperature)**

	TOL-14456
	</a>


-   <a href="https://www.sparkfun.com/products/9163">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/2/5/8/7/09162-02-L.jpg)
	Solder Lead Free - 15-gram Tube">
	</figure>

	---

	<a href="https://www.sparkfun.com/products/9163">
	**Solder Lead Free - 15-gram Tube**

	TOL-09163
	</a>


-   <a href="https://www.sparkfun.com/products/11375">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/7/1/2/0/11375-Hook-Up_Wire_-_Assortment__Solid_Core__22_AWG_-01.jpg)
	Hook-Up Wire - Assortment (Stranded, 22 AWG)">
	</figure>

	---

	<a href="https://www.sparkfun.com/products/11375">
	**Hook-Up Wire - Assortment (Stranded, 22 AWG)**

	PRT-11375
	</a>


-   <a href="https://www.sparkfun.com/products/24771">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/2/3/9/4/7/24771-Wire-Strippers-Feature.jpg)
	Wire Strippers - 20-30 AWG">
	</figure>

	---

	<a href="https://www.sparkfun.com/products/24771">
	**Wire Strippers - 20-30 AWG**

	TOL-24771
	</a>


-   <a href="https://www.sparkfun.com/products/14782">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/1/3/0/3/6/14782-Flush_Cutters_-_Xcelite-02.jpg)
	Flush Cutters - Xcelite">
	</figure>

	---

	<a href="https://www.sparkfun.com/products/14782">
	**Flush Cutters - Xcelite**

	TOL-14782
	</a>


</div>



### Prototyping Accessories *(Optional)*

For those using the PTH version, you will need to connect to the PTHs. You could use IC hooks and a breadboard for a temporary connection depending on your setup and what you have available. Of course, you will want to the solder header pins for a secure connection. We'll assume that you will want to solder a female header since there is already a BlueSMiRF v2 with the male headers available. Then again, you can still solder wire or even your own male headers if you prefer. Below are a few prototyping accessories that you may want to consider.

* [Breadboard - Self-Adhesive (White) [PRT-12002]](https://www.sparkfun.com/products/12002)
* [IC Hook with Pigtail [CAB-09741]](https://www.sparkfun.com/products/9741)
* [Header - 6-pin Female (PTH, 0.1") [PRT-11894]](https://www.sparkfun.com/products/11894)
* [Arduino Stackable Header - 6 Pin [PRT-09280]](https://www.sparkfun.com/products/9280)
* [Break Away Headers - Straight [PRT-00116]](https://www.sparkfun.com/products/116)
* [Break Away Headers - 40-pin Male (Long Centered, PTH, 0.1") [PRT-12693]](https://www.sparkfun.com/products/12693)
* [Jumper Wires Premium 6" M/F Pack of 10 [PRT-09140]](https://www.sparkfun.com/products/9140)
* [Jumper Wires Premium 6" F/F Pack of 10 [PRT-08430]](https://www.sparkfun.com/products/8430)

<div class="grid cards" markdown>

-   <a href="https://www.sparkfun.com/products/12002">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com/assets/parts/8/5/0/3/12002-Breadboard_-_Self-Adhesive__White_-01.jpg)
	</figure>

	---

	**Breadboard - Self-Adhesive (White)**

	PRT-12002
	</a>


-   <a href="https://www.sparkfun.com/products/9741">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com/assets/parts/3/6/9/6/09741-01.jpg)
	</figure>

	---

	**IC Hook with Pigtail**

	CAB-09741
	</a>


-   <a href="https://www.sparkfun.com/products/11894">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/8/9/7/11894-02.jpg)
	</figure>

	---

	**Female Headers**

	PRT-11894
	</a>


-   <a href="https://www.sparkfun.com/products/9280">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/2/7/8/1/09280-1.jpg)
	</figure>

	---

	**Arduino Stackable Header - 6 Pin**

	PRT-09280
	</a>


-   <a href="https://www.sparkfun.com/products/116">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com/assets/parts/1/0/6/00116-02-L.jpg)
	</figure>

	---

	**Break Away Headers - Straight**

	PRT-00116
	</a>


-   <a href="https://www.sparkfun.com/products/12693">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/9/4/2/7/12693-02.jpg)
	</figure>

	---

	**Break Away Headers - 40-pin Male (Long Centered, PTH, 0.1")**

	PRT-12693
	</a>


-   <a href="https://www.sparkfun.com/products/9140">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com//assets/parts/2/5/5/7/09140-02-L.jpg)
	</figure>

	---

	**Jumper Wires Premium 6" M/F Pack of 10**

	PRT-09140
	</a>


-   <a href="https://www.sparkfun.com/products/8431">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com/assets/parts/1/1/8/1/JumperWire-Male-01-L.jpg)
	</figure>

	---

	**Jumper Wires Premium 6" M/M Pack of 10**

	PRT-08431
	</a>


-   <a href="https://www.sparkfun.com/products/553">
	<figure markdown>
	![Product thumbnail](https://cdn.sparkfun.com/r/455-455/assets/parts/3/7/8/00553-03-L.jpg)
	</figure>

	---

	**Break Away Male Headers - Right Angle**

	PRT-00553
	</a>

</div>



### You Will Also Need
Depending on your setup or what you are doing, you may need the following as well.

- 2.4GHz WiFi Network for firmware updates
- Smartphone with an Internet Service



## Suggested Reading
If you aren’t familiar with the following concepts, we also recommend checking out a few of these tutorials before continuing.

<div class="grid cards" markdown style="text-align: center;">

-   <a href="https://learn.sparkfun.com/tutorials/bluetooth-basics">
	<figure markdown>
	![Bluetooth Basics](https://cdn.sparkfun.com/c/178-100/assets/learn_tutorials/1/1/7/blut.jpg)
	</figure>

	---

	**Bluetooth Basics**
	</a>


-   <a href="https://learn.sparkfun.com/tutorials/terminal-basics">
	<figure markdown>
	![Serial Terminal Basics](https://cdn.sparkfun.com/c/178-100/assets/learn_tutorials/1/1/2/terminalThumb.jpg)
	</figure>

	---

	**Serial Terminal Basics**
	</a>


-   <a href="https://learn.sparkfun.com/tutorials/serial-communication">
	<figure markdown>
	![Serial Communication](https://cdn.sparkfun.com/c/178-100/assets/7/d/f/9/9/50d24be7ce395f1f6c000000.jpg)
	</figure>

	---

	**Serial Communication**
	</a>


-   <a href="https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering">
	<figure markdown>
	![How to Solder: Through-Hole Soldering](https://cdn.sparkfun.com/c/178-100/assets/learn_tutorials/5/Soldering_Action-01.jpg)
	</figure>

	---

	**How to Solder: Through-Hole Soldering**
	</a>


-   <a href="https://learn.sparkfun.com/tutorials/logic-levels">
	<figure markdown>
	![Logic Levels](https://cdn.sparkfun.com/c/178-100/assets/learn_tutorials/6/2/Input_Output_Logic_Level_Tolerances_v3.png)
	</figure>

	---

	**Logic Levels**
	</a>

</div>
