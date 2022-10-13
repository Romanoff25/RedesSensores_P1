#ifndef GY_9250_h
#define GY_9250_h

//LIBRARIES
#include <Arduino.h>
#include <i2C.h>

//DEFINES
    //REGs
#define Ax_Reg   0x3B
#define Ay_Reg   0x3D
#define Az_Reg   0x3F
#define Temp_Reg 0x41
#define Gx_Reg   0x43
#define Gy_Reg   0x45
#define Gz_Reg   0x47


#define rAxOffset 0x77
#define rAyOffset 0x7A
#define rAzOffset 0x7D
#define rGxOffset 0x13
#define rGyOffset 0x15
#define rGzOffset 0x17


    //COSISaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
#define conf_Accel_scale 2    // g      per bit
#define conf_Gyro_scale  250  // º/sec  per bit
#define ADC_res 65536 //16bits


//////////////////CONSTRUCTOR////////////////////////////////////////////////////////////////////////////
  //MPU9250::MPU9250() {
  //}


//////////////////CONFIGURACION////////////////////////////////////////////////////////////////////////////

  
class MPU9250{
    int adress {0x68};



  private:



  public:
    float ReadAccel(int axis)
    {
      int reg;
      switch (axis){
      case 0: reg=Ax_Reg; break;
      case 1: reg=Ay_Reg; break;
      case 2: reg=Az_Reg; break;
      default: Serial.println("Error -> Axis not available");break;
      }
      int16_t raw=ReadReg(adress,reg);
      return(raw*2.0*conf_Accel_scale/ADC_res);
    }

    float ReadGyro(int axis)
    {
      int reg;
      switch (axis){
      case 0: reg=Gx_Reg;break;
      case 1: reg=Gy_Reg;break;  
      case 2: reg=Gz_Reg;break;
      default: Serial.println("Error -> Axis not available");break;
      }
      int16_t raw=ReadReg(adress,reg);
      return(raw*2.0*conf_Gyro_scale/ADC_res);
    }
    
    float ReadTemp()
      {
        int16_t raw=ReadReg(adress,Temp_Reg);
        return(raw/333.87 + 21.0);
      }

};




#endif  // GY_9250_h