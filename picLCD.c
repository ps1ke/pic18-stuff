#include <stdio.h>
#include <pic18.h>
#include "picLCD.h"

typedef unsigned int uint;
typedef unsigned char uchar;

#define RS LATB0
#define EN LATB1
#define low_data LATB
#define portLCD TRISB

void initLCD(){

  portLCD = 0;
  MSdelay(20);
  commandLCD(0x02);
  commandLCD(0x28);
  commandLCD(0x01);
  commandLCD(0x0c);
  commandLCD(0x06);
}

void commandLCD(uchar command){

  low_data = (low_data & 0x0f) | (0xF0 & command);
  RS = 0;
  EN = 1;
  NOP();
  EN = 0;
  MSdelay(1);
  low_data = (low_data & 0x0f) | (command<<4);
  EN = 1;
  NOP();
  EN = 0;
  MSdelay(3);
}

void writeCharLCD(uchar charLCD){

  low_data = (low_data & 0x0f) | (0xF0 & charLCD);
  RS = 1;
  EN = 1;
  NOP();
  EN = 0;
  MSdelay(1);
  low_data = (low_data & 0x0f) | (charLCD<<4);
  EN = 1;
  NOP();
  EN = 0;
  MSdelay(3);
}

void stringLCD(const char *string){

  while((*string) != 0){

    writeCharLCD(*string);
    string++;
  }
}

void stringLCDXY(char row, char pos, const char *string){

  char loc = 0;
  if(!row){

    loc = (0x80) | ((pos) & 0x0f);
    commandLCD(loc);
  }
  else{

    loc = (0xC0) | ((pos) & 0x0f);
    commandLCD(loc);
  }

  stringLCD(string);
}

void clearLCD(){

  commandLCD(0x01);
  MSdelay(3);
}

void MSdelay(uint ms){

  int i,j;

  for(i = 0; i < ms; i++){

    for(j = 0; j < 33; j++);
  }
}
