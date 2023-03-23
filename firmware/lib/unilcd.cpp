/**
 * @file unilcd.cpp
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

#include "unilcd.h"

static UCHAR lcdCmdBuffer;
static UCHAR lcdConfig;

#define LINE1_OFFSET  0x80  
#define LINE2_OFFSET  (LINE1_OFFSET + 0x40)
#define LINE3_OFFSET  0x94
#define LINE4_OFFSET  (LINE3_OFFSET + 0x40)

#define LCD_CONFIG_BACKLIGHT  0x80

VOID writeLCDInterface(UCHAR *data)
{
  CHAR pos;

#ifdef ARDUINO_AVR
  
  digitalWrite(SHIFTREG_LATCH_PIN, LOW);
  
  // Load data into the shift register.
  for(pos = 7; pos != 0xFF; pos--)
  {
    digitalWrite(SHIFTREG_CLK_PIN, LOW);
    digitalWrite(SHIFTREG_DATA_PIN, (*data) & (1 << pos)); 
    DELAY_SHORT();
    digitalWrite(SHIFTREG_CLK_PIN, HIGH);
    DELAY_SHORT();    
  }

  digitalWrite(SHIFTREG_CLK_PIN, LOW);
   
  // Latch output and feed data to LCD.
  DELAY_SHORT();  
  digitalWrite(SHIFTREG_LATCH_PIN, HIGH); 
  DELAY_SHORT();  
  digitalWrite(SHIFTREG_LATCH_PIN, LOW);  
  
#elif XC8_PIC_MID 
  
  SHIFTREG_PORT = SHIFTREG_PORT & (~(1 << SHIFTREG_LATCH_PIN));
 
  // Load data into the shift register.
  for(pos = 7; pos != 0xFF; pos--)
  {
    SHIFTREG_PORT = SHIFTREG_PORT & (~(1 << SHIFTREG_CLK_PIN));
    
    if(((*data) & (1 << pos)) != 0x00)
    {
        SHIFTREG_PORT = SHIFTREG_PORT | (1 << SHIFTREG_DATA_PIN);
    }
    else
    {
        SHIFTREG_PORT = SHIFTREG_PORT & (~(1 << SHIFTREG_DATA_PIN));
    }
    
    DELAY_SHORT();
    SHIFTREG_PORT = SHIFTREG_PORT | (1 << SHIFTREG_CLK_PIN);
    DELAY_SHORT();
  }
  
  SHIFTREG_PORT = SHIFTREG_PORT & (~(1 << SHIFTREG_CLK_PIN));
  
  // Latch output and feed data to LCD.
  DELAY_SHORT();
  SHIFTREG_PORT = SHIFTREG_PORT | (1 << SHIFTREG_LATCH_PIN);
  DELAY_SHORT();
  SHIFTREG_PORT = SHIFTREG_PORT & (~(1 << SHIFTREG_LATCH_PIN));
  
#endif  
}

/**
 * @brief Initialize LCD interface.
 * 
 * This function initializes the MCU's I/O pins used by the LCD interface. 
 * The I/O pins used in this function are defined in the platform 
 * configuration header file (e.g: arduino-conf.h).
 * 
 * @return VOID 
 */
VOID initLCDInterface(VOID)
{
#ifdef ARDUINO_AVR
    
  // Configure CLK, DATA and LATCH pins to output mode.
  pinMode(SHIFTREG_CLK_PIN, OUTPUT);
  pinMode(SHIFTREG_DATA_PIN, OUTPUT);
  pinMode(SHIFTREG_LATCH_PIN, OUTPUT);

  // Set all output pins to known state.
  digitalWrite(SHIFTREG_CLK_PIN, LOW);
  digitalWrite(SHIFTREG_DATA_PIN, LOW);  
  digitalWrite(SHIFTREG_LATCH_PIN, LOW);  
  
#elif XC8_PIC_MID

  // Configure CLK, DATA and LATCH pins to output mode.
  SHIFTREG_TRIS = SHIFTREG_TRIS & (~((1 << SHIFTREG_CLK_PIN) | (1 << SHIFTREG_DATA_PIN) | (1 << SHIFTREG_LATCH_PIN)));
  
  // Set all output pins to known state.
  SHIFTREG_PORT = SHIFTREG_PORT & (~((1 << SHIFTREG_CLK_PIN) | (1 << SHIFTREG_DATA_PIN) | (1 << SHIFTREG_LATCH_PIN)));
  
#endif  

  lcdCmdBuffer = 0x00;
  writeLCDInterface(&lcdCmdBuffer);  
}

// LCD interface buffer format:
// | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 |
// | RS | EN | D4 | D5 | D6 | D7 | BK | -- |

/**
 * @brief Send instructions or data to the HD44780 controller.
 * 
 * This function sends instructions or data to the HD44780 controller. 
 * The transfer type (such as instructions or data) can select using the 
 * \p mode parameter. This function support all WRITE instructions 
 * provided by the HD44780 controller.
 * 
 * @param data 8-bit data or instruction code.
 * @param mode Transfer mode, such as \p INSTRUCTION_MODE_CMD or \p INSTRUCTION_MODE_CHAR.
 * @return VOID 
 */
VOID sendLCDInstruction(UCHAR data, UCHAR mode)
{
  // Set LCD backlight.
  lcdCmdBuffer = ((lcdConfig & LCD_CONFIG_BACKLIGHT) >> 1);
  
  // Select upper nibble from the specified data.
  lcdCmdBuffer = (lcdCmdBuffer & 0xC3) | ((data & 0xF0) >> 2);

  // Select instruction mode (RS = 0 for command, 1 = data/character).
  lcdCmdBuffer = (lcdCmdBuffer & 0xFC) | mode;

  // Toggle EN.
  lcdCmdBuffer = lcdCmdBuffer | 0x02;
  writeLCDInterface(&lcdCmdBuffer);

  DELAY_SHORT();

  lcdCmdBuffer = (lcdCmdBuffer & 0xFD);
  writeLCDInterface(&lcdCmdBuffer);  

  // Select lower nibble from the specified data.
  lcdCmdBuffer = (lcdCmdBuffer & 0xC3) | (UCHAR)((data & 0x0F) << 2);

  // Select instruction mode (RS = 0 for command, 1 = data/character).
  lcdCmdBuffer = (lcdCmdBuffer & 0xFC) | mode;

  // Toggle EN.
  lcdCmdBuffer = lcdCmdBuffer | 0x02;
  writeLCDInterface(&lcdCmdBuffer);

  DELAY_SHORT();

  lcdCmdBuffer = (lcdCmdBuffer & 0xFD);
  writeLCDInterface(&lcdCmdBuffer);   
}

/**
 * @brief Initialize HD44780 controller.
 * 
 * Initialize the LCD controller and clear the screen. This function 
 * initializes the LCD controller into the following configuration.
 * 
 *  - Disable the blinking cursor.
 *  - Hide the cursor from the LCD.
 *  - Turn on the LCD backlight. 
 * 
 * @return VOID 
 */
VOID initLCD(VOID)
{  
  // Special Function Set for power on initialization.
  DELAY_LONG();
  DELAY_LONG();
  DELAY_LONG();
  sendLCDCommand(0x33);
  DELAY_LONG(); 
  sendLCDCommand(0x33);
  DELAY_SHORT();
  sendLCDCommand(0x33);
  DELAY_LONG();
  sendLCDCommand(0x32);

  // LCD configuration byte format:
  // | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 |
  // | BL | CU | DO | -- | -- | -- | -- | BK |
  //
  // BL - Cursor blink state. 1 = Blink; 0 = Static.  [LCD_CMD_DISPLAY_CURSOR_BLINK]
  // CU - Cursor display state. 1 = ON; 0 = OFF.      [LCD_CMD_DISPLAY_CUSROR]
  // DO - Display ON status. 1 = ON; 0 = OFF.         [LCD_CMD_DISPLAY_ON]
  // BK - Backlight configuration. 1 = ON; 0 = OFF.   [LCD_CONFIG_BACKLIGHT]
  // -- - Reserved for expansions.
  
  lcdConfig = LCD_CMD_DISPLAY_ON | LCD_CONFIG_BACKLIGHT;  

  // Start actual initializing of the LCD controller.
  sendLCDCommand(LCD_CMD_FUNCTION | LCD_CMD_FUNC_FONT);  
  sendLCDCommand(LCD_CMD_DISPLAY | (lcdConfig & 0x07));
  sendLCDCommand(LCD_CMD_CLEAR); 
  sendLCDCommand(LCD_CMD_ENTRY_MODE | LCD_CMD_ENTRY_INC_ADDRESS);

  DELAY_LONG();   
}

/**
 * @brief Print string on LCD.
 * 
 * Print the content of the specified string buffer on the LCD screen. 
 * This function print contents starting from the current cursor position.
 * 
 * @param str String buffer.
 * @param maxLength Length of the string buffer.
 * @return VOID 
 */
VOID printStringLen(const CHAR *str, UCHAR maxLength)
{
  UCHAR strPos;

  for(strPos = 0; strPos < maxLength; strPos++)
  {
    if(str[strPos] == '\0')
    {
      // Found null character, reached end of the string?
      break;
    }

    printChar(str[strPos]);
  }
}

/**
 * @brief Move the cursor to the given coordinates.
 * 
 * Set the current cursor position to the given row and column.
 * 
 * @param x Horizontal (row) position starting from 0.
 * @param y Vertical (column) position.
 * @return VOID 
 */
VOID gotoLCDPosition(UCHAR x, UCHAR y)
{
  switch(x)
  {
    case 1:   // 2nd row.
      sendLCDCommand(LINE2_OFFSET + y);      
      break;
    case 2:   // 3rd row.
      sendLCDCommand(LINE3_OFFSET + y);
      break;
    case 3:   // 4th row.
      sendLCDCommand(LINE4_OFFSET + y);      
      break;
    default:  // 1st row.  
      sendLCDCommand(LINE1_OFFSET + y);          
  }
}

/**
 * @brief Control LCD screen.
 * 
 * This function can turn on or off the entire LCD screen. When turn off,
 * the display data remains in the DDRAM of the LCD controller.
 * 
 * @param onState Set 1 to turn on the LCD display. Set 0 to turn off 
 * the LCD display.
 * @return VOID 
 */
VOID setDisplayState(UCHAR onState)
{
  UCHAR tmpConfig;
  
  if(onState)
  {
    // Turn on LCD display.     
    lcdConfig = lcdConfig | LCD_CMD_DISPLAY_ON;   
  }
  else
  {
    // Turn off LCD display.
    lcdConfig = lcdConfig & (~LCD_CMD_DISPLAY_ON);
  }

  tmpConfig = LCD_CMD_DISPLAY | (lcdConfig & 0x07);
  sendLCDCommand(tmpConfig);  
}

/**
 * @brief Set cursor display mode.
 * 
 * This function can turn on or off the cursor. 
 * 
 * @param cursorState Set 1 to turn on the cursor. Set 0 to turn off 
 * the cursor.
 * @return VOID 
 */
VOID setCursorState(UCHAR cursorState)
{
  UCHAR tmpConfig;
  
  if(cursorState)
  {
    // Turn on cursor.     
    lcdConfig = lcdConfig | LCD_CMD_DISPLAY_CUSROR;   
  }
  else
  {
    // Turn off cursor.
    lcdConfig = lcdConfig & (~LCD_CMD_DISPLAY_CUSROR);
  }

  tmpConfig = LCD_CMD_DISPLAY | (lcdConfig & 0x07);
  sendLCDCommand(tmpConfig); 
}

/**
 * @brief Set cursor blinking mode.
 * 
 * This function can switch the cursor between blinking and static modes.
 * 
 * @param blinkState Set 1 for blinking, or 0 for the static cursor.
 * @return VOID 
 */
VOID setCursorBlinkState(UCHAR blinkState)
{
  UCHAR tmpConfig;

  if(blinkState)
  {
    // Blink cursor.     
    lcdConfig = lcdConfig | LCD_CMD_DISPLAY_CURSOR_BLINK;   
  }
  else
  {
    // Show only the static cursor.
    lcdConfig = lcdConfig & (~LCD_CMD_DISPLAY_CURSOR_BLINK);
  }

  tmpConfig = LCD_CMD_DISPLAY | (lcdConfig & 0x07);
  sendLCDCommand(tmpConfig); 
}

/**
 * @brief Load custom character to the LCD RAM.
 * 
 * Load 5×8 custom character to the specified address of the CGRAM. 
 * 
 * Make sure to call the \p clearLCD function after loading all custom 
 * characters. Without this function call, the custom characters will 
 * not be displayed on the LCD.
 * 
 * To display the custom characters, call the \p printChar function 
 * with the appropriate address.
 * 
 * @param addr RAM address, ranges from 0 to 7.
 * @param buffer 8-byte long custom character buffer.
 * @return VOID 
 */
VOID setCustomChar(UCHAR addr, UCHAR *buffer)
{
  UCHAR tmpPos;

  if(addr < 8)
  {
    sendLCDCommand(LCD_CMD_CG_RAM + (addr * 8));
    for(tmpPos = 0; tmpPos < 8; tmpPos++)
    {
      sendLCDData(buffer[tmpPos]);
    }    
  }
}

/**
 * @brief Turn on or off the LCD backlight.
 * 
 * This function can turn on or off (LED) backlight. 
 * 
 * @param backLightState Set 1 to turn on the LCD backlight. Set 0 to turn off 
 * the LCD backlight.
 * @return VOID 
 */
VOID setBacklightState(UCHAR backLightState)
{
  if(backLightState)
  {
    // Turn on the LCD backlight.
    lcdConfig = lcdConfig | LCD_CONFIG_BACKLIGHT;
  }
  else
  {
    // Turn off the LCD backlight.
    lcdConfig = lcdConfig & (~LCD_CONFIG_BACKLIGHT);
  }    
}
