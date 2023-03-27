/**
 * @file esp8266-conf.h
 * @author Dilshan R Jayakody (jayakody2000lk@gmail.com)
 * @brief ESP8266 RTOS SDK configuration file for YALI module.
 * @version 1.0
 * @date 2023-03-25
 * 
 * @copyright
 * Copyright (c) 2023 Dilshan R Jayakody.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __UNI_LCD_LIB_ESP8266_HEADER__
#define	__UNI_LCD_LIB_ESP8266_HEADER__

/**
 * Flag to indicate the ESP8266 - FreeRTOS project.
 */
#define ESP8266_FREERTOS    1

/**
 * Clock output which connected to the CLK terminal of the YALI module.
 */
#define SHIFTREG_CLK_PIN    12
/**
 * Data output which connected to the DAT terminal of the YALL module.
 */
#define SHIFTREG_DATA_PIN   13
/**
 * Latch control pin which is connected to the LAT terminal of the YALI module.
 */
#define SHIFTREG_LATCH_PIN  14

// Data type and constant mappings.
/**
 * Mapping for Unsigned char.
 */
#define UCHAR unsigned char
/**
 * Mapping for char. 
 */
#define CHAR  char
/**
 * Mapping for void.
 */
#define VOID  void

/**
 * Maximum string length allowed by the YALI library.
 */
#define MAX_STR_LEN 16

// System function mappings.
/**
 * Function mapping for long delay.
 */
#define DELAY_LONG()  usleep(6 * 1000)
/**
 * Function mapping for short delay.
 */
#define DELAY_SHORT() usleep(64)

#endif /* __UNI_LCD_LIB_ESP8266_HEADER__ */