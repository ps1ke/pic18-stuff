#ifndef _PICI2C_H
#define _PICI2C_H

typedef unsigned int uint;
typedef unsigned char uchar;

void initI2CMaster(uint);
void waitI2CMaster();
void startI2CMaster();
void repeatI2CMaster();
void stopI2CMaster();
void writeI2CMaster(uchar);
uchar readI2CMaster(uchar);

void initI2CSlave(uchar);
uchar slaveRECEIVED();
void slaveSEND(uchar);
void interrupt slaveI2C();

#endif
