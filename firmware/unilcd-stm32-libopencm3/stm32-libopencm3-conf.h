/**
 * @file stm32-libopencm3-conf.h
 * @author Dilshan R Jayakody (jayakody2000lk@gmail.com)
 * @brief STM32 - LibOpenCM3 configuration file for YALI module.
 * @version 1.0
 * @date 2023-03-24
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

#ifndef __UNI_LCD_LIB_STM32_LIBOCM3_HEADER__
#define __UNI_LCD_LIB_STM32_LIBOCM3_HEADER__

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "stm32_delay.h"

#define STM32_LIBOPENCM3    1

#define SHIFTREG_PORT       GPIOA
#define SHIFTREG_AHB        RCC_GPIOA

#define SHIFTREG_CLK_PIN    GPIO0
#define SHIFTREG_DATA_PIN   GPIO1
#define SHIFTREG_LATCH_PIN  GPIO2

// Data type and constant mappings.
#define UCHAR unsigned char
#define CHAR  char
#define VOID  void

#define MAX_STR_LEN 16

// Delay function mappings.
#define DELAY_LONG()  delayMiliSec(10)
#define DELAY_SHORT() delayMicroSec(50)

#endif /* __UNI_LCD_LIB_STM32_LIBOCM3_HEADER__ */