#include <stdio.h>
#include <pic18.h>
#include <picserial.h>

typedef unsigned int uint;
typedef unsigned char uchar;

void initUSART(){

  SPEN = 1;x
  SYNC = 0;

  RX9, TX9 = 0;

  CREN = 1;
  ADDEN = 0;

  BRGH = 1;
  BRG16 = 0;
  SPBRG = 10;

  TRISC7 = 1;
  TRISC6 = 0;

  TXEN = 1;
}

void putch(char c){

  while(!TRMT);
  TXREG = c;
}

char getch(){

  if(OERR){

    CREN = 0;
    CREN = 1;
  }

  while(!RCIF);
  return RCREG;
}
    
