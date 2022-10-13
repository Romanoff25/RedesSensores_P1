#ifndef i2C_h
#define i2C_h


//LIBRARIES
#include <Arduino.h>
#include <Wire.h>


int16_t ReadReg(int adress, int reg)
{
  Wire.beginTransmission (adress);
  Wire.write(reg);
  int eWire = Wire.endTransmission(false);
  Wire.requestFrom(adress, 2);
  int data1=Wire.read();
  int data2=Wire.read();
  return ((data1<<8)+data2);
}

void WriteReg(int adress, int reg, int nByte, int data[])
{
  Wire.beginTransmission (adress);
  Wire.write(reg);
  for (size_t i = 0; i < nByte; i++)
  {
    Wire.write(data[i]);       //////REVISARaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa 
  }
  int eWire = Wire.endTransmission(false);
}


#endif  // i2C_h