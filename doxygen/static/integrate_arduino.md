Integration with Arduino
========================

The Following integration steps work with any Arduino platform including [Arduino Uno](https://docs.arduino.cc/hardware/uno-rev3), [Arduino Due](https://docs.arduino.cc/hardware/due), [Arduino Mega 2560](https://docs.arduino.cc/hardware/mega-2560), etc.

1. Copy arduino-conf.h, unilcd.cpp, and unilcd.h files to the Arduino sketch directory (where `.ino` file resides).
2. In default configuration YALI library reserved Arduino pins 4, 5, and 6 to communicate with the LCD module. To change these pins modify the following definitions in the arduino-conf.h file.

 - `SHIFTREG_CLK_PIN` - Clock output which is connected to the *CLK* terminal of the YALI module.
 - `SHIFTREG_DATA_PIN` - Data output connected to the *DAT* terminal of the YALL module.
 - `SHIFTREG_LATCH_PIN` - Latch control pin which is connected to the *LAT* terminal of the YALI module.

3. Connect the above mention outputs to the *CLK*, *DAT*, and *LAT* terminals of the YALI module.
4. Change the voltage setting of the YALI module to the appropriate setting based on the Arduino board. For example, the setting should be 5V for *Arduino Uno* and *Arduino Mega 2560* boards. For 8Arduino Due*, the setting must change to a 3.3V position. 
5. Connect the external power supply or Arduino voltage output terminals to the suitable DC input terminal of the YALI module.
6. Run the following Arduino sketch to verify the connectivity and functionality of the module:

```c

#include "Arduino.h"
#include "unilcd.h"

void setup() 
{
	initLCDInterface();
  	delay(100);
  	initLCD();

	clearLCD();
 	printString("Hello World");
}

void loop()
{

}

```
