In this example, we will connect two BlueSMiRF v2 boards to two separate serial ports. We will then send characters from one serial terminal to a second serial terminal.

The image below on the left shows the Serial Basic (CH340, USB-C) connected to the BlueSMiRF v2 Header using M/F jumper wires. Headers were used to easily remove and reconnect the BlueSMiRF v2 with headers. The image to the right shows the Serial Basic (CH340, micro-B) connected to the BlueSMiRF v2 PTH using M/F jumper wires. A row of female headers were soldered on the board. Extra long headers were placed between the female headers to easily remove and reconnect the BlueSMiRF v2 PTH as well.


<div class="grid cards" markdown>

<figure markdown>
[![USB-to-Serial Converter (CH340) to BlueSMiRF v2 Header with an Additional Stackable Header](./assets/img/assembly-smd-uart_adapter-alt.jpg){ width="600" }](./assets/img/assembly-smd-uart_adapter-alt.jpg "Click to enlarge")
<figcaption markdown>USB-to-Serial Converter (CH340) to BlueSMiRF v2 Header with an Additional Stackable Header</figcaption>
</figure>


<figure markdown>
[![USB-to-Serial Converter (CH340) to BlueSMiRF v2 PTH](./assets/img/assembly-pth-uart_adapter.jpg){ width="600" }](./assets/img/assembly-pth-uart_adapter.jpg "Click to enlarge")
<figcaption markdown>USB-to-Serial Converter (CH340) to BlueSMiRF v2 PTH</figcaption>
</figure>

</div>


!!! note
	To distinguish between the two BlueSMiRFs, try labeling the two board. In this case, we chose had the one with male headers and the other one with female headers.

Connect the first BlueSMiRF v2 to your computer's COM port. In this case, it was **COM13**. Press and hold the ++"PAIR"++ button between **4 to 8 seconds**. The Status and Connect LEDs will slowly blink back and forth. The Connect LED will begin to fade in and out after a few seconds. Open a serial terminal and connect to the first BlueSMiRF at **115200 baud**.


<figure markdown>
[![First Serial Terminal](./assets/img/example-terminal_a-open.jpg){ width="600" }](./assets/img/example-terminal_a-open.jpg "Click to enlarge")
<figcaption markdown>First Serial Terminal</figcaption>
</figure>


At this point, connect the second BlueSMiRF v2 to your computer's COM port. In this case, it was **COM18**. Press and hold the second BlueSMiRF's ++"PAIR"++ button between **4 to 8 seconds**. The second BlueSMiRF will scan the area for another BlueSMiRF and connect. Once connected, the **Connect** LEDs on both boards will remain solid. Open a second serial terminal, and connect to the second BlueSMiRF at **115200 baud**. Move both serial terminals side by side.


<figure markdown>
[![Second Serial Terminal](./assets/img/example-terminal_b-open.jpg){ width="600" }](./assets/img/example-terminal_b-open.jpg "Click to enlarge")
<figcaption markdown>Second Serial Terminal</figcaption>
</figure>


Start typing characters in the first serial terminal. You should see them in the second serial terminal!


<div class="grid cards" markdown>

<figure markdown>
[![Sending Characters through First Terminal](./assets/img/example-terminal_a-open.jpg){ width="600" }](./assets/img/example-terminal_a-open.jpg "Click to enlarge")
<figcaption markdown>Sending Characters through First Terminal</figcaption>
</figure>


<figure markdown>
[![Receiving Characters through Second Terminal](./assets/img/example-terminal_b-receive.jpg){ width="600" }](./assets/img/example-terminal_b-receive.jpg "Click to enlarge")
<figcaption markdown>Receiving Characters through Second Terminal</figcaption>
</figure>

</div>


Type a message in the second terminal window. You should see them in the first serial terminal!


<div class="grid cards" markdown>

<figure markdown>
[![Receiving Characters through First Serial TerminalSending Characters through First Terminal](./assets/img/example-terminal_a-receive.jpg){ width="600" }](./assets/img/example-terminal_a-receive.jpg "Click to enlarge")
<figcaption markdown>Receiving Characters through First Serial Terminal</figcaption>
</figure>


<figure markdown>
[![Sending Characters through Second Terminal](./assets/img/example-terminal_b-receive.jpg){ width="600" }](./assets/img/example-terminal_b-receive.jpg "Click to enlarge")
<figcaption markdown>Sending Characters through Second Terminal</figcaption>
</figure>

</div>
