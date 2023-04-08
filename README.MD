
# "Hello world" program for the T-Dongle-S3

Simple project to demonstrate the use of [LilyGo T-Dongle-S3](https://github.com/Xinyuan-LilyGO/T-Dongle-S3).

![T-Dongle-S3](img/t-dongle-s3.png)

It uses:

* The TFT Display
* The Multicolor LED
* The Serial Port
* The Button

After you compile and upload the project, the display will cycle though showing "Red", "Green" and "Blue" on the TFT screen. The multicolour led will also iluminate with the corresponding colour. If you press and hold the button on the back of the dongle, the screen will turn yellow and the TFT and led will also act accordingly. The colour being shown is always written to the serial port.

As a plus, the handler for the button is installed as a separate task in the ESP32S3 processor.

Enjoy!
