//LIBRARIES
#include <Arduino.h>  //Integrates FreeRTOS
#include <GY_9250.h>

//DEFINES
#define MPU_Adress 0x68
#define PIN_LED 5
#define PIN_ADC 2
#define PIN_PWM 17
#define LedChannel 0
#define PWM_f 5000
#define PWM_res 12 //8,10,12,15



//OBJECTS
MPU9250 IMU1;
float buffer[3][10];
SemaphoreHandle_t mutex_UART = xSemaphoreCreateMutex();
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;



//TASKS
  //Buffer_2_UART (1s) (Task1)
void Tarea1( void * parameter){
  
  while(1){
    delay(800);
    //if(xSemaphoreTake(mutex_UART,0)==pdTRUE){
      digitalWrite(PIN_LED, LOW);
      Serial.println();
      for (size_t i = 0; i < 3; i++){
          Serial.println();
          Serial.print("Axis-"+ String(i) +" data  --> ");
        for (size_t j = 0; j < 10; j++)
        {
          Serial.print(String(buffer[i][j]));
          Serial.print("\t, ");
        }
        delay(200);
        digitalWrite(PIN_LED, HIGH);
      //}
      //xSemaphoreGive(mutex_UART);
    }
  }
  vTaskDelete( NULL );
}

  //MPU_2_Buffer (1ms) (MAIN LOOP)
void loop() {
  for (size_t i = 0; i < 10; i++){
    for (size_t j = 0; j < 3; j++)
    {
      buffer[j][i]= IMU1.ReadAccel(j);
    }
    delay(100);
  }
}



//SETUP
void setup() {
  //Serial
  Serial.begin(115200);

  //IOs
  pinMode(PIN_ADC, OUTPUT);
  pinMode(PIN_PWM, OUTPUT);

  //PWM
  ledcSetup(LedChannel, PWM_f, PWM_res);;
  ledcAttachPin(PIN_PWM, LedChannel);

  //IOs
  pinMode(PIN_LED, OUTPUT);
  Wire.begin (21, 22); // sda= GPIO_21 /scl= GPIO_22

  //FreeRTOS
  xTaskCreate(Tarea1,"Buffer_2_UART",1000,NULL,1,NULL);

}
