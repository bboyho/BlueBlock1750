BlueBlock1750
-------------------

Arduino code to control the [SparkFun Purpletooth Jamboree - BC127 Audio Bluetooth Development Board](https://www.sparkfun.com/products/11924). This code is also used for a custom wireless audio Bluetooth adapter in older speaker systems. It has been tested and used since 2016:

 * in my car
 * with a mixer and studio monitor's at Block1750
 * portable audio bluetooth device when teaching at different studios

<div align="center"><a href="https://cdn.sparkfun.com/assets/learn_tutorials/4/6/1/Wireless_Bluetooth_Speaker_Project-15.jpg"><img src="https://cdn.sparkfun.com/r/600-600/assets/learn_tutorials/4/6/1/Wireless_Bluetooth_Speaker_Project-15.jpg" title="All three wireless audio bluetooth adapters"></a></div>

Repository Contents
-------------------

* _/BlueBlock1750v1 - Initial code to control BC127 by resetting and making the Bluetooth discoverable._
* _/BlueBlock1750v2 - Same code as v1 but includes button states to check when a button has been pressed. The button states help by sending the commands once per button press._
* **/BlueBlock1750v3 - Stable code used for the Bluetooth audio adapters. Includes an additional modular function to automate the default configuration and resetting the Bluetooth.**
* _/BlueBlock1750v4 - Beta testing code to check the state of the Bluetooth (connected or not) and control the blue "Discoverable" status LED._
* _/array test - Beta testing arrays for BlueBlock1750v4._

Documentation
-------------------
* [Project Tutorial](https://learn.sparkfun.com/tutorials/wireless-audio-bluetooth-adapter-w-bc127) - Tutorial to follow along with the code used in this project.
* [BC127 Arduino Library](https://github.com/sparkfun/SparkFun_BC127_Bluetooth_Module_Arduino_Library)
* [BC127 Hookup Guide](https://learn.sparkfun.com/tutorials/understanding-the-bc127-bluetooth-module)
* [BC127 Melody_v5.0_User Manual](https://cdn.sparkfun.com/datasheets/Wireless/Bluetooth/Melody_5.0_Manual-RevD-RC10-Release.pdf)

License Information
-------------------

This project is _**open source**_! 

Please review the [LICENSE.md](https://github.com/bboyho/BlueBlock1750/blob/master/LICENSE.md) file for license information. 

Distributed as-is; no warranty is given.

- Your friends at SparkFun.
