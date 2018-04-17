#include <stdio.h>
#include <pic18.h>

typedef unsigned int uint;
typedef unsigned char uchar;

#define MY_ADRESS 0
#define SLAVE1 11
#define SLAVE2 12

void i2configMaster(){

  SSPM0 = 1;
  SSPM1 = 1;
  SSPM2 = 1;
  SSPM3 = 1;
  
  SSPEN = 1;

  TRISC3, TRISC4 = 1;

  TRISC6 = 0;
  TRISC7 = 1;

  CKP = 1;
  SMP = 0;
  CKE = 0;
  
  SSPADD = 255;
}

void writeToSlave(int adress, int code1){

  SEN = 1;
  while(SEN);

  ACKDT, SSPIF = 0;

  SSPBUF = adress;
  while(!SSPIF);
  SSPIF = 0;

  SSPBUF = code1;
  while(!SSPIF);
  SSPIF = 0;

  PEN = 1;
}

uchar getDataSlave(int adress, int command){
  
  SEN = 1;
  while(SEN);

  ACKDT, SSPIF = 0;

  SSPBUF = adress;
  while(!SSPIF);
  SSPIF = 0;

  SSPBUF = command;
  while(!SSPIF);
  SSPIF = 0;

  RCEN = 1;
  while(!BF);

  int data = SSPBUF;

  ACKEN = 1;
  while(ACKEN);

  PEN = 1;
  while(PEN);
  
  return data;
}
	    
void interrupt timers(){
}

int main(){

  PCFG0, PCFG1, PCFG2, PCFG3 = 1;

  i2configMaster();
  writeToSlave(SLAVE1, 123);
  
  while(1);
}
