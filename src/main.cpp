//LIBRARIES
#include <Arduino.h>
#define PIN_ADC 2

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


//EVENT-TIMER
void IRAM_ATTR onTimer() {
portENTER_CRITICAL(&timerMux);
int data = analogRead(PIN_ADC);
Serial.print(data);
Serial.println("ADC_Value: " + String(data*3.4/4095.0)+"V");
portEXIT_CRITICAL(&timerMux);
}



//INICIALIZATION
void setup() {
  //Serial
  Serial.begin(9600);

  //IOs
  pinMode(PIN_ADC, OUTPUT);

  //Timer
  timer = timerBegin(0, 80, true);             //Clock preescaler
  timerAttachInterrupt(timer, &onTimer, true);  //Define Event
  timerAlarmWrite(timer, 3000000, true);        //N_of_Ticks
  timerAlarmEnable(timer);
  
}

void loop() {
sleep(1000);
}