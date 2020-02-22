This is a first rough cut of an Arduino library for the IKEA FREKVENS LED panels developed jointly with Teenage Engineering.

Contributions welcome.

Arduino requirements: Must be type with 3.3V logic levels. If you want to try hooking this up through 8-bit 5V AVR antiques like an Arduino Uno, then you must use level shifters. 

Recommendation: Use Teensy 3+, Adafruit Feather M0 or Sparkfun SAMD21 mini breakouts. Should also work with 32U4 based boards as well, so
long as they're 3.3V. Haven't tried with ESP8266 yet. 

Library dependencies:
- Adafruit GFX library must be installed.

Soldering instructions:
- Open & disassemble the LED cube. 

- Extract the mainboard.

- Desolder the original controller daughterboard (green color).
  * Use flux and solder wick. 

- Attach wires to the six solder points.
  * The outermost solder points are marked VCC and GND. 
  * Let GND be (1) and VCC be (6). The middle four are as follows:
  * (2) LATCH - connect to a digital output pin. 
  * (3) CLOCK - connect to a digital output pin.
  * (4) DATA - connect to a digital output pin.
  * (5) !ENABLE. This one is optional. 
        If you DON'T need to be able to control brightness
        of the display, then just solder a wire from this pin
        to GND. 
        If you DO want to control brightness, then connect this
        pin to a PWM ("analog") output pin on your Arduino.

  * Solder the GND wire to a GND pin on the Arduino.

  * Leave the VCC wire unconnected until you're done programming
  * The VCC wire has 4 volts on it coming from the isolated power
  * supply of the Frekvens cube.
  * While programming, the Arduino should be powered through USB.
  * After programming, disconnect USB cable and attach VCC wire
  * from Frekvens panel to battery input or "USB" voltage pin on
  * the Arduino. The Frekvens panel will now supply the Arduino
  * board voltages.

- Optionally - hook up the red and yellow buttons on the back.
  * RED wire is common so connect this to GND or VCC of the
  * Arduino. BLACK wire is RED button, WHITE wire is YELLOW button. 

- Put the whole thing back together.

- To use the library, add #include "Frekvenspanel.h" statement, and instantiate a FrekvensPanel object. See examples.

- Library has several un-documented experimental modes, including
  multiple bit planes (intensity dithering) and support for daisy-
  chaining several modules. Needs more work. At the moment the daisy-
  chain is mapped vertically which seems wrong. 

- Happy hacking

