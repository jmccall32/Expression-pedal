# Expression-pedal
Arduino project to get MIDI output from an analog expression or volume pedal

The original purpose of this project was to build a swell pedal to use with an organ emulator.  I used a Yamaha EP-1 pedal which includes an audio taper pot, but I wanted linear output, so a "de-tapering" function is included.

This project requires a board with native USB.  This includes ATmega32u4 boards such as the Arduino Leonardo, Arduino Micro, or SparkFun Pro Micro.

To wire your pedal up, the wiper of the pedal potentiometer should go to the analog input you're using (A2 by default).  One end of the pot should connect to GND and the other to VCC.  Ground should be the end with low resistance to the wiper when the pedal is all the way back (toe up).  Don't worry too much if you get this backwards - you can easily modify the code to reverse the pedal in software.

It's also a good idea to wire a capacitor, e.g. 0.1 uF, between signal and ground, especially if the pot's nominal resistance is higher than 10-20 kOhm.

If you're wiring your board up to a TRS jack instead of hardwiring it into a pedal, note that different pedals often use different pinouts for the TRS jack. it's a good idea to wire some resistance, e.g. 1kOhm, in series with the signal to prevent shorting the power supply of your board if someone plugs in the wrong polarity pedal.  You can also install a DPDT switch to allow for both common pedal polarities.