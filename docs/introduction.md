
The [SparkFun BlueSMiRF v2](https://www.sparkfun.com/products/24113) is a wireless Bluetooth&reg; serial link. This version of the popular BlueSMiRF uses the ESP32. These boards work as a wireless serial UART pipe and are a great wireless replacement for serial cables. Simply pair, connect, and transmit serial data between your TX/RX lines! Any serial stream from 2400 to 921600 baud can be passed seamlessly between two devices.

<center>
<div class="grid cards col-2" markdown>

-   <a href="https://www.sparkfun.com/products/24113">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/r/600-600/assets/parts/2/4/4/3/8/24113-BlueSMiRF-ESP32-NoHeaders-Feature-NEW.jpg" style="width:140px; height:140px; object-fit:contain;" alt="SparkFun BlueSMiRF v2">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/24113">
      <b>SparkFun BlueSMiRF v2</b>
      <br />
      WRL-24113
      <br />
      <center>[Purchase from SparkFun :fontawesome-solid-cart-plus:](https://www.sparkfun.com/products/23288){ .md-button .md-button--primary }</center>
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/23287">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/r/600-600/assets/parts/2/3/4/8/3/23287-BlueSMiRF-ESP32-WithHeaders-Feature-NEW.jpg" style="width:140px; height:140px; object-fit:contain;" alt="SparkFun BlueSMiRF v2 - Headers">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/23287">
      <b>SparkFun BlueSMiRF v2 - Headers</b>
      <br />
      WRL-23287
      <br />
      <center>[Purchase from SparkFun :fontawesome-solid-cart-plus:](https://www.sparkfun.com/products/23288){ .md-button .md-button--primary }</center>
    </a>

</div>
</center>

<div style="text-align: center;">
  <iframe width="560" height="315" src="https://www.youtube.com/embed/i8u3W0jVFTw?si=9iwrsCm9Ih9n9VCz" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>
</div>

In this tutorial, we'll go over the hardware and how to hookup the breakout board. We will also go over how to connect to a smartphone and a basic Arduino example to get started!



### Required Materials

To follow along with this tutorial, you will need the following materials. You may not need everything though depending on what you have. Add it to your cart, read through the guide, and adjust the cart as necessary. We recommend the board with headers to minimize the amount of soldering to your application.

* 2x [SparkFun BlueSMiRF v2 - Headers [WRL-23287]](https://www.sparkfun.com/products/23287)
* 2x [Jumper Wires Premium 6" M/F Pack of 10 [PRT-09140]](https://www.sparkfun.com/products/9140)
* 2x [SparkFun Serial Basic Breakout - CH340C and USB-C [DEV-15096]](https://www.sparkfun.com/products/15096)
* 2x [Reversible USB A to C Cable - 0.8m [CAB-15425]](https://www.sparkfun.com/products/15425)

<div class="grid cards col-4" markdown>

<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/19177">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/r/600-600/assets/parts/2/3/4/8/3/23287-BlueSMiRF-ESP32-WithHeaders-Feature-NEW.jpg" style="width:140px; height:140px; object-fit:contain;" alt="SparkFun BlueSMiRF v2 - Headers">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/23287">
      <b>SparkFun BlueSMiRF v2 - Headers</b>
      <br />
      WRL-23287
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/9140">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/2/5/5/7/09140-02-L.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Jumper Wires Premium 6" M/F Pack of 10">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/9140">
      <b>Jumper Wires Premium 6" M/F Pack of 10</b>
      <br>
      PRT-09140
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/15096">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/1/3/4/5/2/15096-SparkFun_Serial_Basic_Breakout_-_CH340C_and_USB-C-01.jpg" style="width:140px; height:140px; object-fit:contain;" alt="SparkFun Serial Basic Breakout - CH340C and USB-C">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/15096">
      <b>SparkFun Serial Basic Breakout - CH340C and USB-C</b>
      <br />
      DEV-15096
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/15425">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/1/3/9/8/4/15425-Reversible_USB_A_to_C_Cable_-_0.8m-02.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Reversible USB A to C Cable - 0.8m">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/15425">
      <b>Reversible USB A to C Cable - 0.8m</b>
      <br />
      CAB-15425
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
</div>







### Tools &nbsp;_(Optional)_

You will need a soldering iron, solder, and [general soldering accessories](https://www.sparkfun.com/categories/49) for a secure connection when using the plated through holes. You may also need to solder headers or wires to any devices that the BlueSMiRF v2 is connecting to.

* [Soldering Iron [TOL-14456]](https://www.sparkfun.com/products/14456)
* [Solder Lead Free - 15-gram Tube [TOL-9163]](https://www.sparkfun.com/products/9163)
* [Flush Cutters - Xcelite [TOL-14782]](https://www.sparkfun.com/products/14782)
* [Hook-Up Wire - Assortment (Stranded, 22 AWG) [PRT-11375]](https://www.sparkfun.com/products/11375)
* [Wire Strippers - 20-30 AWG [TOL-24771]](https://www.sparkfun.com/products/24771)

<div class="grid cards col-4" markdown>

-   <a href="https://www.sparkfun.com/products/14456">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/1/2/4/9/0/14456-01.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Soldering Iron - 60W (Adjustable Temperature)">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/14456">
      <b>Soldering Iron - 60W (Adjustable Temperature)</b>
      <br />
      TOL-14456
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/9163">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/2/5/8/7/09162-02-L.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Solder Lead Free - 15-gram Tube">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/9163">
      <b>Solder Lead Free - 15-gram Tube</b>
      <br>
      TOL-09163
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/11375">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/7/1/2/0/11375-Hook-Up_Wire_-_Assortment__Solid_Core__22_AWG_-01.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Hook-Up Wire - Assortment (Stranded, 22 AWG)">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/11375">
      <b>Hook-Up Wire - Assortment (Stranded, 22 AWG)</b>
      <br />
      PRT-11375
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/24771">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/2/3/9/4/7/24771-Wire-Strippers-Feature.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Wire Strippers - 20-30 AWG">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/24771">
      <b>Wire Strippers - 20-30 AWG</b>
      <br />
      TOL-24771
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/14782">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/1/3/0/3/6/14782-Flush_Cutters_-_Xcelite-02.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Flush Cutters - Xcelite">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/14782">
      <b>Flush Cutters - Xcelite</b>
      <br />
      TOL-14782
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
</div>



### Prototyping Accessories &nbsp;_(Optional)_

For those using the PTH version, you will need to connect to the PTHs. You could use IC hooks and a breadboard for a temporary connection depending on your setup and what you have available. Of course, you will want to the solder header pins for a secure connection. We'll assume that you will want to solder a female header since there is already a BlueSMiRF v2 with the male headers available. Then again, you can still solder wire or even your own male headers if you prefer. Below are a few prototyping accessories that you may want to consider.

* [Breadboard - Self-Adhesive (White) [PRT-12002]](https://www.sparkfun.com/products/12002)
* [IC Hook with Pigtail [CAB-09741]](https://www.sparkfun.com/products/9741)
* [Header - 6-pin Female (PTH, 0.1") [PRT-11894]](https://www.sparkfun.com/products/11894)
* [Arduino Stackable Header - 6 Pin [PRT-09280]](https://www.sparkfun.com/products/9280)
* [Break Away Headers - Straight [PRT-00116]](https://www.sparkfun.com/products/116)
* [Break Away Headers - 40-pin Male (Long Centered, PTH, 0.1") [PRT-12693]](https://www.sparkfun.com/products/12693)
* [Jumper Wires Premium 6" M/F Pack of 10 [PRT-09140]](https://www.sparkfun.com/products/9140)
* [Jumper Wires Premium 6" F/F Pack of 10 [PRT-08430]](https://www.sparkfun.com/products/8430)

<div class="grid cards col-4" markdown>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/12002">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/assets/parts/8/5/0/3/12002-Breadboard_-_Self-Adhesive__White_-01.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Breadboard - Self-Adhesive (White)">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/12002">
      <b>Breadboard - Self-Adhesive (White)</b>
      <br />
      PRT-12002
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/9741">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/assets/parts/3/6/9/6/09741-01.jpg" style="width:140px; height:140px; object-fit:contain;" alt="IC Hook with Pigtail">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/9741">
      <b>IC Hook with Pigtail</b>
      <br>
      CAB-09741
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/11894">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/8/9/7/11894-02.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Header - 6-pin Female (PTH, 0.1") ">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/11894">
      <b>Female Headers</b>
      <br />
      PRT-00115
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/9280">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/2/7/8/1/09280-1.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Arduino Stackable Header - 6 Pin">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/9280">
      <b>Arduino Stackable Header - 6 Pin</b>
      <br />
      PRT-09280
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/116">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/assets/parts/1/0/6/00116-02-L.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Break Away Headers - Straight">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/116">
      <b>Break Away Headers - Straight</b>
      <br />
      PRT-00116
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/12693">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/9/4/2/7/12693-02.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Break Away Headers - 40-pin Male (Long Centered, PTH, 0.1")">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/12693">
      <b>Break Away Headers - 40-pin Male (Long Centered, PTH, 0.1")</b>
      <br />
      PRT-12693
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/9140">
      <figure markdown>
        <img src="https://cdn.sparkfun.com//assets/parts/2/5/5/7/09140-02-L.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Jumper Wires Premium 6" M/F Pack of 10">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/9140">
      <b>Jumper Wires Premium 6" M/F Pack of 10</b>
      <br>
      PRT-09140
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
-   <a href="https://www.sparkfun.com/products/8431">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/assets/parts/1/1/8/1/JumperWire-Male-01-L.jpg" style="width:140px; height:140px; object-fit:contain;" alt="Jumper Wires Premium 6" M/M Pack of 10">
      </figure>
    </a>

    ---

    <a href="https://www.sparkfun.com/products/8431">
      <b>Jumper Wires Premium 6" M/M Pack of 10</b>
      <br />
      PRT-08431
    </a>
<!-- ----------WHITE SPACE BETWEEN PRODUCTS---------- -->
</div>

### You Will Also Need

Depending on your setup or what you are doing, you may need the following as well.

* 2.4GHz WiFi Network for firmware updates
* Smartphone with an Internet Service


### Suggested Reading

If you aren’t familiar with the following concepts, we also recommend checking out a few of these tutorials before continuing.

<div class="grid cards col-4" markdown>
<!-- ----------WHITE SPACE BETWEEN GRID CARDS---------- -->
-   <a href="https://learn.sparkfun.com/tutorials/bluetooth-basics">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/assets/learn_tutorials/1/1/7/blut.jpg" style="width:264px; height:148px; object-fit:contain;" alt="Bluetooth Basics">
      </figure>
    </a>

    ---

    <a href="https://learn.sparkfun.com/tutorials/bluetooth-basics">
      <b>Bluetooth Basics</b>
    </a>
<!-- ----------WHITE SPACE BETWEEN GRID CARDS---------- -->
-   <a href="https://learn.sparkfun.com/tutorials/terminal-basics">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/assets/learn_tutorials/1/1/2/terminalThumb.jpg" style="width:264px; height:148px; object-fit:contain;" alt="Serial Terminal Basics">
      </figure>
    </a>

    ---

    <a href="https://learn.sparkfun.com/tutorials/terminal-basics">
      <b>Serial Terminal Basics</b>
    </a>
<!-- ----------WHITE SPACE BETWEEN GRID CARDS---------- -->
-   <a href="https://learn.sparkfun.com/tutorials/serial-communication">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/assets/7/d/f/9/9/50d24be7ce395f1f6c000000.jpg" style="width:264px; height:148px; object-fit:contain;" alt="Serial Communication">
      </figure>
    </a>

    ---

    <a href="https://learn.sparkfun.com/tutorials/serial-communication">
      <b>Serial Communication</b>
    </a>
<!-- ----------WHITE SPACE BETWEEN GRID CARDS---------- -->
-   <a href="https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/assets/learn_tutorials/5/Soldering_Action-01.jpg"style="width:264px; height:148px; object-fit:contain;" alt="How to Solder: Through-Hole Soldering">
      </figure>
    </a>

    ---

    <a href="https://learn.sparkfun.com/tutorials/how-to-solder-through-hole-soldering">
      <b>How to Solder: Through-Hole Soldering</b>
    </a>

<!-- ----------WHITE SPACE BETWEEN GRID CARDS---------- -->
-   <a href="https://learn.sparkfun.com/tutorials/logic-levels">
      <figure markdown>
        <img src="https://cdn.sparkfun.com/assets/learn_tutorials/6/2/Input_Output_Logic_Level_Tolerances_v3.png?_gl=1*647ace*_ga*MTYwMjY5MTgyMy4xNzAwMjQzOTQx*_ga_T369JS7J9N*MTcwNjA3Njc2Ni4xODEuMS4xNzA2MDc5MDc2LjMzLjAuMA.."style="width:264px; height:148px; object-fit:contain;" alt="Logic Levels">
      </figure>
    </a>

    ---

    <a href="https://learn.sparkfun.com/tutorials/logic-levels">
      <b>Logic Levels</b>
    </a>
</div>
