
#ifndef __UNI_LCD_LIB_XC8_PIC_MID_HEADER__
#define	__UNI_LCD_LIB_XC8_PIC_MID_HEADER__

#include "unilcd-config.h"
#include <xc.h> 

#define XC8_PIC_MID         1

#define SHIFTREG_PORT       PORTB
#define SHIFTREG_TRIS       TRISB

#define SHIFTREG_CLK_PIN    0
#define SHIFTREG_DATA_PIN   1
#define SHIFTREG_LATCH_PIN  2

// Data type and constant mappings.
#define UCHAR unsigned char
#define CHAR  char
#define VOID  void

#define NULL 0
#define MAX_STR_LEN 16

// System function mappings.
#define DELAY_LONG()  __delay_ms(5)
#define DELAY_SHORT() __delay_us(30)

#pragma warning disable 520

#endif	/* __UNI_LCD_LIB_XC8_PIC_MID_HEADER__ */

