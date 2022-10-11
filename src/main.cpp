//LIBRARIES
#include <Arduino.h>
#define PIN_ADC 2
#define PIN_PWM 17
#define LedChannel 0
#define PWM_f 5000
#define PWM_res 12 //8,10,12,15

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


//EVENT-TIMER
void IRAM_ATTR onTimer() {
portENTER_CRITICAL(&timerMux);
int data = analogRead(PIN_ADC);
ledcWrite(LedChannel,1024);
Serial.println("ADC_Value: " + String(data*3.4/4095.0)+"V");
portEXIT_CRITICAL(&timerMux);
}



//INICIALIZATION
void setup() {
  //Serial
  Serial.begin(9600);

  //IOs
  pinMode(PIN_ADC, OUTPUT);
  pinMode(PIN_PWM, OUTPUT);

  //PWM
  ledcSetup(LedChannel, PWM_f, PWM_res);
  ledcAttachPin(PIN_PWM, LedChannel);

  //Timer
  timer = timerBegin(0, 80, true);             //Clock preescaler
  timerAttachInterrupt(timer, &onTimer, true);  //Define Event
  timerAlarmWrite(timer, 3000000, true);        //N_of_Ticks
  timerAlarmEnable(timer);
  
}

void loop() {
sleep(1000);
}