SparkFun BlueSMiRF ESP32 Firmware
===========================================================
<table class="table table-hover table-striped table-bordered">
  <tr align="center">
   <td><a href="https://www.sparkfun.com/products/23287"><img src="https://cdn.sparkfun.com//assets/parts/2/3/4/8/3/23287-BlueSMiRF-ESP32-WithHeaders-Scale.jpg"></a></td>
   <td><a href="https://www.sparkfun.com/products/24113"><img src="https://cdn.sparkfun.com//assets/parts/2/4/4/3/8/24113-BlueSMiRF-ESP32-NoHeaders-Feature.jpg"></a></td>
  </tr>
  <tr align="center">
    <td><a href="https://www.sparkfun.com/products/23287">SparkFun BlueSMiRF - ESP32 with Headers (WRL-23287)</a></td>
    <td><a href="https://www.sparkfun.com/products/24113">SparkFun BlueSMiRF - ESP32 (WRL-24113)</a></td>
  </tr>
  <tr align="center">
    <td><a href="https://learn.sparkfun.com/tutorials/sparkfun-rtk-facet-l-band-hookup-guide">Hookup Guide</a></td>
    <td><a href="https://learn.sparkfun.com/tutorials/sparkfun-rtk-facet-hookup-guide">Hookup Guide</a></td>
  </tr>
</table>

The [SparkFun BlueSMiRF - ESP32](https://www.sparkfun.com/products/24113) and [SparkFun BlueSMiRF - ESP32 with Headers](https://www.sparkfun.com/products/23287) are point to point serial cable replacements using Bluetooth. Simply throw serial characters at a BlueSMiRF and the data will arrive at the other radio, with guaranteed packet delivery. Baud rates supported up to 921600bps!

This repo houses the [BlueSMiRF Product Manual](https://docs.sparkfun.com/SparkFun_BlueSMiRF-ESP32) and the firmware that runs on the SparkFun BlueSMiRF ESp32 product line including:

* [SparkFun BlueSMiRF - ESP32](https://www.sparkfun.com/products/24113)
* [SparkFun BlueSMiRF - ESP32 with Headers](https://www.sparkfun.com/products/23287)

For compiled binaries of the firmware, please see [SparkFun BlueSMiRF ESP32 Firmware Binaries](https://github.com/sparkfun/SparkFun_BlueSMiRF-ESP32_Binaries).

Repository Contents
-------------------

* **/Firmware** - Source code for SparkFun BlueSMiRF firmware as well as various feature unit tests
* **/Documents** - Datasheets for various components.
* **/docs** - Markdown pages for the [BlueSMiRF Product Manual](https://docs.sparkfun.com/SparkFun_BlueSMiRF-ESP32/)

Repository Branch Structure
---------------------------

This repository has two long-term branches: `main` and `release_candidate`.

With respect to the firmware, `main` is a branch where only changes that are appropriate for all users are applied. Thus, following `main` means updating to normal releases, and perhaps bugfixes to those releases.

In contrast, `release_candidate` is where new code is added as it is developed.

The documentation source code is in docs/ on `main`.  It is built automatically on push and stored in the branch `gh-pages`, from which it is served at the above URL. Documentation changes are pushed directly to main.

Release Process
---------------

A release is made by merging `release_candidate` back to `main`, and then applying a tag to that commit on `main`.

A pre-release is often created using the latest stable release candidate. These binaries will have extra debug statements turned on that will not be present in a formal release, but should not affect the behavior of the firmware.


License Information
-------------------

This product is _**open source**_!  Please feel free to [contribute](https://docs.sparkfun.com/SparkFun_BlueSMiRF-ESP32/contribute/) to both the firmware and documentation.

Various bits of the code have different licenses applied. Anything SparkFun wrote is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!

Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.
