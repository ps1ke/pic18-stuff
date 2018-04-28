#include <stdio.h>
#include <pic18.h>
#include "picI2C.h"

typedef unsigned int uint;
typedef unsigned char uchar;

uchar sSEND;
uchar sRECEIVE;
uchar sCLEAR;

void initI2CMaster(uint sspadd){

  SSPCON1 = 0b00101000;
  SSPCON2 = 0;
  SSPADD = sspadd;
  SSPSTAT = 0;
  TRISC3, TRISC4 = 1;
}

void waitI2CMaster(){
  
  while( (SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void startI2CMaster(){

  waitI2CMaster();
  SEN = 1;
}

void repeatI2CMaster(){

  waitI2CMaster();
  RSEN = 1;
}

void stopI2CMaster(){

  waitI2CMaster();
  PEN = 1;
}

void writeI2CMaster(uchar data){

  waitI2CMaster();
  SSPBUF = data;
}

uchar readI2CMaster(uchar akno){
  
  repeatI2CMaster();
  waitI2CMaster();
  
  uchar temp = SSPBUF;
  
  waitI2CMaster();
  
  if(!akno){
    
    ACKDT = 0;
    ACKEN = 1;
  }
  
  return temp;
}

//=======================

//SLAVE

//========================


void initI2CSlave(uchar adress){

  SSPSTAT = 0x00;
  SSPADD = adress;
  SSPCON1 = 0x36;
  SSPCON2 = 0x01;
  
  TRISC3, TRISC4 = 1;
  
  GIE = 1;
  PEIE = 1;
  
  SSPIF = 0;
  SSPIE = 1;
}

uchar slaveRECEIVED(){

  return sRECEIVE;
}

void slaveSEND(uchar data){ 

  sSEND = data;
}

void interrupt slaveI2C(){

  if(SSPIF == 1){
    
    SSPCON1bits.CKP = 0;
    
    if ((SSPCON1bits.SSPOV) || (SSPCON1bits.WCOL)){
      
      sCLEAR = SSPBUF;
      SSPCON1bits.SSPOV = 0;
      SSPCON1bits.WCOL = 0;
      SSPCON1bits.CKP = 1;
    }
  }
  
  if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW){
    
    sCLEAR = SSPBUF;
    while(!BF);
    sRECEIVE = SSPBUF;
    SSPCON1bits.CKP = 1;
  }
  
  else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
    
    sCLEAR = SSPBUF;
    BF = 0;
    SSPBUF = sSEND ;
    SSPCON1bits.CKP = 1;
    while(SSPSTATbits.BF);
  }
  
  SSPIF = 0;
} 
