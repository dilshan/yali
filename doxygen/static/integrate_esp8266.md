Integration with ESP8266
========================

The following integration steps work with ESP8266 projects which are built on top of [Espressif Systems RTOS SDK](https://github.com/espressif/ESP8266_RTOS_SDK).

1. Copy esp8266-conf.h, unilcd.cpp, and unilcd.h files to the project source directory.
2. In default configiration YALI library reserved P12, P13, and P14 to communicate with the LCD module. To change these pins modify the following definitions in the esp8266-conf.h file.

 - `SHIFTREG_CLK_PIN` - Clock output which is connected to the *CLK* terminal of the YALI module.
 - `SHIFTREG_DATA_PIN` - Data output connected to the *DAT* terminal of the YALL module.
 - `SHIFTREG_LATCH_PIN` - Latch control pin which is connected to the *LAT* terminal of the YALI module.

3. Connect the above mention outputs to the *CLK*, *DAT*, and *LAT* terminals of the YALI module.
4. Change the voltage setting of the 3.3V.
5. Connect the external power supply or system power terminals to the 3.3V DC input terminal of the YALI module.
6. To verify the connectivity flash the following sample program to the MCU:

```c

#include "stm32-libopencm3-conf.h"
#include "unilcd.h"

int main()
{
	initLCDInterface();
	delayMiliSec(100);

	initLCD();  

	clearLCD();
	printString("Hello World");

	while(1);

	return 0;
}

```
