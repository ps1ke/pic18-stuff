#ifndef PICLCD_H_
#define PICLCD_H_

typedef unsigned int uint;
typedef unsigned char uchar;

void initLCD();
void commandLCD(uchar command);
void writeCharLCD(uchar charLCD);
void stringLCD(const char *string);
void stringLCDXY(char row, char pos, const char *string);
void clearLCD();

#endif 
