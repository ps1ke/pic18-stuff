#ifndef _PICSERIAL_H
#define _PICSERIAL_H

typedef unsigned int uint;
typedef unsigned char uchar;

void initUSART();
void putch(char);
char getch();

#endif
