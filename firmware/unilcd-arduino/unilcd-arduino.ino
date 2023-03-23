#include "Arduino.h"
#include "unilcd.h"

unsigned char animPos = 0;
unsigned char loadProgress = 0;

unsigned char row1Pos = 0;
unsigned char row2Pos = 12;

char row1Direction = 1;
char row2Direction = -1;

char msg1[16], msg2[16];
const char* displayMsg = " This is a test ";

void resetMessage()
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
      *dir = -1;
    }

    if((*pos) == 0)
    {
      *dir = 1;
    }  
}

void setup() 
{
  unsigned char hourglass1[8] = {0x1f,0x1f,0xe,0x4,0xa,0x11,0x1f,0x0};
  unsigned char hourglass2[8] = {0x1f,0x11,0xe,0x4,0xa,0x1f,0x1f,0x0};
  unsigned char hourglass3[8] = {0x1f,0x11,0xa,0x4,0xe,0x1f,0x1f,0x0};

  initLCDInterface();
  delay(100);
  initLCD();

  setCustomChar(0, hourglass1);
  setCustomChar(1, hourglass2);
  setCustomChar(2, hourglass3);

  clearLCD();
  printString("LCD Test");
}

void loop() 
{
  if(loadProgress < 10)
  {
    gotoLCDPosition(0, 9);
    printChar(animPos);

    if((++animPos) > 2)
    {
      animPos = 0;
    }
    
    delay(1000);
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
