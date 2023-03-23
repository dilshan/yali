/**
 * @file unilcd.h
 * @author Dilshan R Jayakody (jayakody2000lk@gmail.com)
 * @brief YALI (Yet Another LCD Interface) library.
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

#ifndef __UNI_LCD_LIB_HEADER__
#define __UNI_LCD_LIB_HEADER__

#if defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_SAM_DUE)
// Arduino
#include "arduino-conf.h"
#elif __PICC__
// MPLAB XC C for PIC.
#include "xc8-pic-conf.h"
#else
#error "Unsupported board or microcontroller."
#endif

/**
 * Clears entire display and reset DDRAM address.
 */
#define LCD_CMD_CLEAR   0x01
/**
 * Return cursor to the home location and shift display to the original position. 
 */
#define LCD_CMD_HOME    0x02

/**
 * Set cursor move direction and specifies display shift.
 */
#define LCD_CMD_ENTRY_MODE          0x04
/**
 * Auto increment the DDRAM address by 1 when a character is written.
 */
#define LCD_CMD_ENTRY_INC_ADDRESS   0x02
/**
 * Shift the entire display to the left.
 */
#define LCD_CMD_ENTRY_SHIFT_LEFT    0x01

/**
 * Display and cursor control.
 */
#define LCD_CMD_DISPLAY               0x08
/**
 * Turn on the entire LCD display.
 */
#define LCD_CMD_DISPLAY_ON            0x04
/**
 * Display cursor as 5×8 block.
 */
#define LCD_CMD_DISPLAY_CUSROR        0x02
/**
 * Enable blinking cursor.
 */
#define LCD_CMD_DISPLAY_CURSOR_BLINK  0x01

/**
 * Moves cursor or shifts display.
 */
#define LCD_CMD_SHIFT           0x10
/**
 * Shift display to the right.
 */
#define LCD_CMD_SHIFT_RIGHT     0x04
/**
 * Shift display.
 */
#define LCD_CMD_SHIFT_DISPLAY   0x08

/**
 * Function mode to set data length, number of display lines and 
 * character font.
 */
#define LCD_CMD_FUNCTION          0x20
/**
 * Interface data length is 8-bits. (This mode is not 
 * supported by YALI module.)
 */
#define LCD_CMD_FUNC_8BIT_LENGTH  0x10
/**
 * Number of display lines.
 */
#define LCD_CMD_FUNC_LINES        0x04
/**
 * Set the character font.
 */
#define LCD_CMD_FUNC_FONT         0x08

/**
 * CGRAM (character pattern buffer) command.
 */
#define LCD_CMD_CG_RAM    0x40
/**
 * DDRAM (display data buffer) command.
 */
#define LCD_CMD_DDRAM     0x80

// Instruction modes.

/**
 * Command (instruction) mode.
 */
#define INSTRUCTION_MODE_CMD  0x00
/**
 * Data (character) mode.
 */
#define INSTRUCTION_MODE_CHAR 0x01

/**
 * @brief This macro send data to the HD44780 controller.
 */
#define sendLCDData(d)    sendLCDInstruction(d, INSTRUCTION_MODE_CHAR)
/**
 * @brief This macro send instructions (commands) to the HD44780 controller.
 */
#define sendLCDCommand(c) sendLCDInstruction(c, INSTRUCTION_MODE_CMD)

VOID initLCDInterface(VOID);
VOID sendLCDInstruction(UCHAR data, UCHAR mode);

VOID initLCD(VOID);
VOID printStringLen(const CHAR *str, UCHAR maxLength);
VOID gotoLCDPosition(UCHAR x, UCHAR y);
VOID setDisplayState(UCHAR onState);  
VOID setCursorState(UCHAR cursorState);
VOID setCursorBlinkState(UCHAR blinkState);
VOID setCustomChar(UCHAR addr, UCHAR *buffer);

VOID setBacklightState(UCHAR backLightState);

/**
 * @brief Macro to clear LCD display and reset DDRAM address.
 */
#define clearLCD()      sendLCDCommand(LCD_CMD_CLEAR)
/**
 * @brief Macro to move cursor to the home location.
 */
#define returnToHome()  sendLCDCommand(LCD_CMD_HOME)

/**
 * @brief Macro to print a single character on the LCD.
 */
#define printChar(c)    sendLCDData(c)
/**
 * @brief Macro to print a null terminate string on the LCD.
 */
#define printString(s)  printStringLen(s, MAX_STR_LEN)

#endif /* __UNI_LCD_LIB_HEADER__ */
