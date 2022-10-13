//LIBRARIES
#include <Arduino.h>
#include <GY_9250.h>

//DEFINES
#define MPU_Adress 0x68


MPU9250 IMU1;
float buffer[3][10];

void setup()
{
  Serial.begin (9600);  
  Wire.begin (21, 22);   // sda= GPIO_21 /scl= GPIO_22
}


void loop()
{

  //FILL
  for (size_t i = 0; i < 10; i++)
  {
    for (size_t j = 0; j < 3; j++)
    {
      buffer[j][i]= IMU1.ReadAccel(j);
    }
    delay(100);
  }

  //PRINT
  for (size_t i = 0; i < 3; i++)
  {
      Serial.println();
      Serial.print("Axis-"+ String(i) +" data  --> ");
    for (size_t j = 0; j < 10; j++)
    {
      Serial.print(String(buffer[i][j]));
      Serial.print("\t, ");
    }

  }
Serial.println();
      


}




