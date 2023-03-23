/**
 * @file unilcd-config.h
 * @author Dilshan R Jayakody (jayakody2000lk@gmail.com)
 * @brief PIC16F877A configuration file for YALI demo.
 * @version 1.0
 * @date 2023-03-23
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

#ifndef __UNI_LCD_DEMO_CONFIG_HEADER__
#define	__UNI_LCD_DEMO_CONFIG_HEADER__

#define _XTAL_FREQ 4000000

// PIC16F877A Configuration Bit Settings

#pragma config FOSC = XT  
#pragma config WDTE = OFF 
#pragma config PWRTE = ON 
#pragma config BOREN = ON
#pragma config LVP = OFF  
#pragma config CPD = OFF  
#pragma config WRT = OFF  
#pragma config CP = OFF

#include <xc.h>

#endif /* __UNI_LCD_DEMO_CONFIG_HEADER__ */