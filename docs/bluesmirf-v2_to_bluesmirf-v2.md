In this example, we will connect two BlueSMiRF v2 boards to two separate serial ports. We will then send characters from one serial terminal to a second serial terminal.

The image below on the left shows the Serial Basic (CH340, USB-C) connected to the BlueSMiRF v2 Header using M/F jumper wires. Headers were used to easily remove and reconnect the BlueSMiRF v2 with headers. The image to the right shows the Serial Basic (CH340, micro-B) connected to the BlueSMiRF v2 PTH using M/F jumper wires. A row of female headers were soldered on the board. Extra long headers were placed between the female headers to easily remove and reconnect the BlueSMiRF v2 PTH as well.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/CH340_stackable_header_BlueSMiRF-v2.jpg"><img src="../assets/img/CH340_stackable_header_BlueSMiRF-v2.jpg" width="600px" height="600px" alt="USB-to-Serial Converter (CH340) to BlueSMiRF v2 Header with an Additional Stackable Header"></a></td>
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/CH340_BlueSMiRF-v2_PTH_female_header.jpg"><img src="../assets/img/CH340_BlueSMiRF-v2_PTH_female_header.jpg" width="600px" height="600px" alt="USB-to-Serial Converter (CH340) to BlueSMiRF v2 PTH"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><i>USB-to-Serial Converter (CH340) to BlueSMiRF v2 Header with an Additional Stackable Header</i>
     </td>
     <td style="text-align: center; vertical-align: middle;"><i>USB-to-Serial Converter (CH340) to BlueSMiRF v2 PTH</i>
     </td>
    </tr>
  </table>
</div>

!!! note
    To distinguish between the two BlueSMiRFs, try labeling the two board. In this case, we chose had the one with male headers and the other one with female headers.

Connect the first BlueSMiRF v2 to your computer's COM port. In this case, it was **COM13**. Press and hold the PAIR button between **4 to 8 seconds**. The Status and Connect LEDs will slowly blink back and forth. The Connect LED will begin to fade in and out after a few seconds. Open a serial terminal and connect to the first BlueSMiRF at **115200 baud**.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_a.JPG"><img src="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_a.JPG" width="600px" height="600px" alt="First Serial Terminal"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;">
       <i>First Serial Terminal</i>
     </td>
    </tr>
  </table>
</div>

At this point, connect the second BlueSMiRF v2 to your computer's COM port. In this case, it was **COM18**. Press and hold the second BlueSMiRF's PAIR button between **4 to 8 seconds**. The second BlueSMiRF will scan the area for another BlueSMiRF and connect. Once connected, the **Connect** LEDs on both boards will remain solid. Open a second serial terminal, and connect to the second BlueSMiRF at **115200 baud**. Move both serial terminals side by side.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_B.JPG"><img src="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_b.JPG" width="600px" height="600px" alt="Second Serial Terminal"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;">
       <i>Second Serial Terminal</i>
     </td>
    </tr>
  </table>
</div>

Start typing characters in the first serial terminal. You should see them in the second serial terminal!

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_a.JPG"><img src="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_a.JPG" width="600px" height="600px" alt="Sending Characters through First Terminal"></a></td>
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_c.JPG"><img src="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_c.JPG" width="600px" height="600px" alt="Receiving Characters through Second Terminal"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><i>Sending Characters through First Terminal</i>
     </td>
     <td style="text-align: center; vertical-align: middle;"><i>Receiving Characters through Second Terminal</i>
     </td>
    </tr>
  </table>
</div>

Type a message in the second terminal window. You should see them in the first serial terminal!

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_d.JPG"><img src="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_d.JPG" width="600px" height="600px" alt=""></a></td>
     <td style="text-align: center; vertical-align: middle;"><a href="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_c.JPG"><img src="../assets/img/BlueSMiRF_v2_Serial_Terminal_1_c.JPG" width="600px" height="600px" alt="Sending Characters through Second Terminal"></a></td>
    </tr>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle;"><i>Receiving Characters through First Serial Terminal</i>
     </td>
     <td style="text-align: center; vertical-align: middle;"><i>Sending Characters through Second Terminal</i>
     </td>
    </tr>
  </table>
</div>
