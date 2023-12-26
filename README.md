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

This repo houses the [BlueSMiRF Product Manual](https://docs.sparkfun.com/SparkFun_RTK_Firmware) and the firmware that runs on the SparkFun BlueSMiRF ESp32 product line including:

* [SparkFun BlueSMiRF - ESP32](https://www.sparkfun.com/products/24113)
* [SparkFun BlueSMiRF - ESP32 with Headers](https://www.sparkfun.com/products/23287)

For compiled binaries of the firmware, please see [SparkFun BlueSMiRF ESP32 Firmware Binaries](https://github.com/sparkfun/SparkFun_BlueSMiRF-ESP32_Binaries).

If you're interested in the PCB, enclosure, or overlay on each product please see the hardware repos:

* [SparkFun RTK Facet L-Band Hardware](https://github.com/sparkfun/SparkFun_RTK_Facet)
* [SparkFun RTK Facet Hardware](https://github.com/sparkfun/SparkFun_RTK_Facet)
* [SparkFun RTK Reference Station Hardware](https://github.com/sparkfun/SparkFun_RTK_Reference_Station)
* [SparkFun RTK Express Plus Hardware](https://github.com/sparkfun/SparkFun_RTK_Express_Plus)
* [SparkFun RTK Express Hardware](https://github.com/sparkfun/SparkFun_RTK_Express)
* [SparkFun RTK Surveyor Hardware](https://github.com/sparkfun/SparkFun_RTK_Surveyor)

Thanks:

* Special thanks to [Avinab Malla](https://github.com/avinabmalla) for the creation of [SW Maps](https://play.google.com/store/apps/details?id=np.com.softwel.swmaps&hl=en_US&gl=US) and for pointers on handling the ESP32 read/write tasks.

Documentation
--------------

* **[RTK Product Manual](https://docs.sparkfun.com/SparkFun_RTK_Firmware/)** - A detail guide describing all the various software features of the RTK product line.   Essentially it is a manual for the firmware in this repository.
* **[RTK Facet L-Band Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-rtk-facet-l-band-hookup-guide)** - Hookup guide for the SparkFun RTK Facet L-Band.
* **[RTK Facet Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-rtk-facet-hookup-guide)** - Hookup guide for the SparkFun RTK Facet.
* **[RTK Reference Station Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-rtk-reference-station-hookup-guide)** - Hookup guide for the SparkFun RTK Reference Station.
* **[RTK Express Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-rtk-express-hookup-guide)** - Hookup guide for the SparkFun RTK Express and Express Plus.
* **[RTK Surveyor Hookup Guide](https://learn.sparkfun.com/tutorials/sparkfun-rtk-surveyor-hookup-guide)** - Hookup guide for the SparkFun RTK Surveyor.

Repository Contents
-------------------

* **/Firmware** - Source code for SparkFun RTK firmware as well as various feature unit tests
* **/Graphics** - Original bitmap icons for the display
* **/docs** - Markdown pages for the [RTK Product Manual](https://docs.sparkfun.com/SparkFun_RTK_Firmware/)

Repository Branch Structure
---------------------------

This repository has two long-term branches: `main` and `release_candidate`.

With respect to the firmware, `main` is a branch where only changes that are appropriate for all users are applied. Thus, following `main` means updating to normal releases, and perhaps bugfixes to those releases.

In contrast, `release_candidate` is where new code is added as it is developed.

The documentation source code is in docs/ on `main`.  It is built automatically on push and stored in the branch `gh-pages`, from which it is served at the above URL. Documentation changes are pushed directly to main.

Release Process
---------------

A release is made by merging `release_candidate` back to `main`, and then applying a tag to that commit on `main`.

A pre-release is often created using the latest stable release candidate. These binaries will have extra debug statements turned on that will not be present in a formal release, but should not affect behavior of the firmware.

Building from Source
--------------------

For building the firmware, see the [Firmware README](Firmware/readme.md).

For the documentation, see [mkdocs.yml](https://github.com/sparkfun/SparkFun_RTK_Firmware/blob/main/mkdocs.yml) and [/workflows/mkdocs.yml](https://github.com/sparkfun/SparkFun_RTK_Firmware/blob/main/.github/workflows/mkdocs.yml).

For building the Uploader_GUI see the header comments of [RTK_Firkware_Uploader_GUI.py](https://github.com/sparkfun/SparkFun_RTK_Firmware/blob/main/Uploader_GUI/RTK_Firmware_Uploader_GUI.py)

For building the u-blox_Update_GUI see the header comments of [RTK_u-blox_Update_GUI.py](https://github.com/sparkfun/SparkFun_RTK_Firmware/blob/main/u-blox_Update_GUI/RTK_u-blox_Update_GUI.py)

License Information
-------------------

This product is _**open source**_!  Please feel free to [contribute](https://docs.sparkfun.com/SparkFun_RTK_Firmware/contribute/) to both the firmware and documentation.

Various bits of the code have different licenses applied. Anything SparkFun wrote is beerware; if you see me (or any other SparkFun employee) at the local, and you've found our code helpful, please buy us a round!

Please use, reuse, and modify these files as you see fit. Please maintain attribution to SparkFun Electronics and release anything derivative under the same license.

Distributed as-is; no warranty is given.

- Your friends at SparkFun.
