Integration with STM32
======================

The following integration steps work with [STM32](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) projects which are built on top of [LibOpenCM3](https://github.com/libopencm3/libopencm3).

1. Copy stm32-libopencm3-conf.h, unilcd.cpp, and unilcd.h files to the project source directory.
2. In default configiration YALI library reserved PA0, PA1, and PA2 to communicate with the LCD module. To change these pins modify the following definitions in the stm32-libopencm3-conf.h file.

 - `SHIFTREG_CLK_PIN` - Clock output which is connected to the *CLK* terminal of the YALI module.
 - `SHIFTREG_DATA_PIN` - Data output connected to the *DAT* terminal of the YALL module.
 - `SHIFTREG_LATCH_PIN` - Latch control pin which is connected to the *LAT* terminal of the YALI module.

3. Connect the above mention outputs to the *CLK*, *DAT*, and *LAT* terminals of the YALI module.
4. Change the voltage setting of the YALI module to the appropriate setting based on the *STM32* supply voltage.
5. Connect the external power supply or system power terminals to the suitable DC input terminal of the YALI module.
6. Run the following sample program to verify the connectivity and functionality of the module:

```c

#include "unilcd.h"

int main()
{
	initLCDInterface();
	delay(100);

	initLCD();  

	clearLCD();
	printString("LCD Test");

	while(1);

	return 0;
}

```
