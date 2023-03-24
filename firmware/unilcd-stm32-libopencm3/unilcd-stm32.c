/**
 * @file unilcd-stm32.c
 * @author Dilshan R Jayakody (jayakody2000lk@gmail.com)
 * @brief STM32F103C8 demo with LibOpenCM3.
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

#include "stm32-libopencm3-conf.h"
#include "unilcd.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

unsigned char animPos = 0;
unsigned char loadProgress = 0;

unsigned char row1Pos = 0;
unsigned char row2Pos = 12;

char row1Direction = 1;
char row2Direction = (char)-1;

char msg1[16], msg2[16];
const char* displayMsg = " This is a test ";

void resetMessage(void)
{
    unsigned char pos = 0;

    for(pos = 0; pos < 16; pos++)
    {
        msg1[pos] = displayMsg[pos];
        msg2[pos] = displayMsg[pos];
    }
}

void assignShade(char *msg, unsigned char pos)
{
    msg[pos] = 0xFF;
    msg[pos + 1] = 0xFF;
    msg[pos + 2] = 0xFF; 
}

void updateDirection(unsigned char *pos, char *dir)
{
    *pos = (*pos) + (*dir);
  
    if((*pos) > 12)
    {
        *dir = (char)-1;
    }

    if((*pos) == 0)
    {
        *dir = 1;
    }  
}

int main()
{
    unsigned char hourglass1[8] = {0x1f,0x1f,0xe,0x4,0xa,0x11,0x1f,0x0};
    unsigned char hourglass2[8] = {0x1f,0x11,0xe,0x4,0xa,0x1f,0x1f,0x0};
    unsigned char hourglass3[8] = {0x1f,0x11,0xa,0x4,0xe,0x1f,0x1f,0x0};
    
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_HSI_48MHZ]);

    initLCDInterface();
    delayMiliSec(100);

    initLCD();  

    setCustomChar(0, hourglass1);
    setCustomChar(1, hourglass2);
    setCustomChar(2, hourglass3);

    clearLCD();
    printString("LCD Test");

    while(1)
    {
        if(loadProgress < 10)
        {
            gotoLCDPosition(0, 9);
            printChar(animPos);

            if((++animPos) > 2)
            {
                animPos = 0;
            }

            delayMiliSec(1000);
            loadProgress++;
        }
        else if(loadProgress == 10)
        {    
            clearLCD(); 
            loadProgress++;   
        }
        else
        {
            resetMessage();

            assignShade(msg1, row1Pos);
            gotoLCDPosition(0, 0);
            printString(msg1);

            assignShade(msg2, row2Pos);
            gotoLCDPosition(1, 0);
            printString(msg2);

            updateDirection(&row1Pos, &row1Direction);
            updateDirection(&row2Pos, &row2Direction);       
        }
    }
}