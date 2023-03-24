/**
 * @file stm32_delay.c
 * @author Dilshan R Jayakody (jayakody2000lk@gmail.com)
 * @brief Support library to provide delay functions using SysTick.
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

#include "stm32_delay.h"

#include <libopencm3/cm3/systick.h>

#define SYSTICK_RELOAD_VAL ((F_CPU/1000) - 1)

// Milliseconds counter since system startup.
static volatile unsigned int systemMillis;

void sys_tick_handler(void)
{
    systemMillis++;
}

void delayMiliSec(unsigned int delay)
{
    unsigned int targetTime = systemMillis + delay;
	while (targetTime > systemMillis);
}

// This implementation is based on Arduino Delay functions.
static unsigned int micros(void)
{
  volatile unsigned int _ulTickCount2 = 0 ;
  _ulTickCount2 = (1000 * systemMillis);
  _ulTickCount2 += ((SYSTICK_RELOAD_VAL - systick_get_value()) / (SYSTICK_RELOAD_VAL / 1000));
  return _ulTickCount2;
}

__inline__ void delayMicroSec(unsigned int delay)
{
    unsigned int start = micros();
    while ( micros() - start < delay) ;
}

void setupSysTick()
{
    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);

    // Setup SysTick to trigger in 1ms intervals.
    systick_clear(); 
    systick_set_reload(SYSTICK_RELOAD_VAL);

    // Activate SysTick interrupt.
    systick_interrupt_enable();
    systick_counter_enable(); 
}