Before we go over the hardware though, let's compare previous SparkFun BlueSMiRF versions with the BlueSMiRF v2!

Back in April 2005, we originally released the BlueSMiRF v1 (short for Bluetooth Serial Miniature RF Link version 1) with BlueRadio's WML-C40AH. They came in two flavors: one with 4-pins for the basic BlueSMiRF consisting of PWR/GND/TX-O/RX-I, and the other with 6-pins for the extended BlueSMiRF consisting of RTS/RX-I/TX-O/GND/PWR/CTS. Over the years, the extended 1x6 pin became the "standard" for the BlueSMiRF.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;""><a href="../assets/img/Main-BlueSMiRF-0.png"><img src="../assets/img/Main-BlueSMiRF-0.png" width="600px" height="600px" alt="Basic BlueSMiRF"></a></td>
     <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;""><a href="../assets/img/Main-BlueSMiRF-Extended-1.png"><img src="../assets/img/Main-BlueSMiRF-Extended-1.png" width="600px" height="600px" alt="Extended BlueSMiRF"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;"><i>Basic BlueSMiRF</i></td>
     <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;"><i>Extended BlueSMiRF</i></td>
    </tr>
  </table>
</div>

We even saw changes in the Bluetooth modems! The BlueRadio's WML-C40AH modems eventually switched over to Roving Network's RN-41 and RN-42. Each version had different ranges and transmit power.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;><a href="../assets/img/12582-BlueSMiRF_Gold_RN-42.jpg"><img src="../assets/img/12582-BlueSMiRF_Gold_RN-42.jpg" width="600px" height="600px" alt="BlueSMiRF Gold (RN-42)"></a></td>
     <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;"><a href="../assets/img/12577-BlueSMiRF_Silver-RN-41.jpg"><img src="../assets/img/12577-BlueSMiRF_Silver-RN-41.jpg" width="600px" height="600px" alt="BlueSMiRF Silver (RN-41)"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;"><i>BlueSMiRF Gold (RN-42)</i></td>
     <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;"><i>BlueSMiRF Silver (RN-41)</i></td>
    </tr>
  </table>
</div>

The 1x6 pins also were rearranged for the SparkFun Bluetooth Mates similar to the USB-to-Serial Converters.

<div style="text-align: center;">
  <table>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;><a href="../assets/img/Header_BlueSMiRF_Bluetooth_Mate_Comparison.jpg"><img src="../assets/img/Header_BlueSMiRF_Bluetooth_Mate_Comparison.jpg" width="600px" height="600px" alt="Header BlueSMiRF & Bluetooth Mate"></a></td>
    </tr>
    <tr style="vertical-align:middle;">
     <td style="text-align: center; vertical-align: middle; border: solid 1px #cccccc;"><i>Back of Bluetooth Mate and BlueSMiRF</i></td>
    </tr>
  </table>
</div>

Fast forward to January 2024 (my how time flies!), the BlueSMiRFs v2 is brought back to life! So what's different from the previous versions? Well, the differences to note with the BlueSMiRF v2 include:

* ESP32-PICO-MINI-02 module
* firmware can be easily updated Over-the-Air or through a command line interface
* the pinout matches the previous Bluetooth Mates and standard USB-to-serial converters: <span STYLE="text-decoration:overline">RTS</span>/RXI/TXO/VCC/<span STYLE="text-decoration:overline">CTS</span>/GND
* labels included on both sides of the board instead of just the bottom
* multi-use button for setting the board in bootloader mode, pairing, and factory reset instead of a PTH PIO4 for factory reset
* jumper to disable the button
* CTS/RTS jumper was removed
* APA2112K 3.3V, 600mA voltage regulator instead of the MIC5205 3.3V, 150mA
* a bypass jumper for the voltage regulator was added
* size is slightly smaller measuring 38.1mm x 15.2mm
