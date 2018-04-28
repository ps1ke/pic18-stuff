#include <stdio.h>
#include "piclcd.h"
#include "pici2c.h"
#include "picserial.h"

int main(){

  initI2CMaster(255);
  initLCD();
  stringLCD("LCD be working!!");
  initUSART()

  while(1){
	
    writeI2CMaster(0xA0);     //7 bit address + Write
    writeI2CMaster(0xAA);    //Write data
    stopI2CMaster();

    printf("USART");
	
    for( uint i = 0; i < 255; i++);
  }

  return 0;
}
