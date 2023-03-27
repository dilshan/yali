Integration with 8-bit PIC
==========================

The following integration steps work with 8-bit *PIC* MCU projects built using the [MPLAB XC8](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers) toolchain.

1. Copy xc8-pic-conf.h, unilcd.cpp, and unilcd.h files to the project source directory.
2. In default configiration YALI library reserved PB0, PB1, and PB2 to communicate with the LCD module. To change these pins modify the following definitions in the xc8-pic-conf.h file.

 - `SHIFTREG_CLK_PIN` - Clock output which is connected to the *CLK* terminal of the YALI module.
 - `SHIFTREG_DATA_PIN` - Data output connected to the *DAT* terminal of the YALL module.
 - `SHIFTREG_LATCH_PIN` - Latch control pin which is connected to the *LAT* terminal of the YALI module.

3. Connect the above mention outputs to the *CLK*, *DAT*, and *LAT* terminals of the YALI module.
4. Change the voltage setting of the YALI module to the appropriate setting based on the MCU supply voltage.
5. Connect the external power supply or system power terminals to the suitable DC input terminal of the YALI module.
6. To verify the connectivity flash the following sample program to the MCU:

```c

#include "unilcd.h"
#include <xc.h> 

int main()
{
	initLCDInterface();
	__delay_ms(100);

	initLCD();  

	clearLCD();
	printString("LCD Test");

	while(1);

	return 0;
}

```
