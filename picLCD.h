#ifndef _PICLCD_H
#define _PICLCD_H

typedef unsigned int uint;
typedef unsigned char uchar;

void initLCD();
void commandLCD(uchar);
void writeCharLCD(uchar);
void stringLCD(const char *);
void stringLCDXY(char, char, const char *);
void clearLCD();
void MSdelay(uint);

#endif 
