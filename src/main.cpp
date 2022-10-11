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
  timer = timerBegin(0, 800, true);             //Clock preescaler (to 10kHz)
  timerAttachInterrupt(timer, &onTimer, true);  //Define Event

}



//COMMAND INPUT
void serialEvent() {
  while (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    int iBrackets = input.indexOf("(");


    //WITHOUT BRACKETS
    if(iBrackets==-1){
      ////////
        //ADC -> Devolver valor del ADC
        if (input.startsWith("ADC")){
          Serial.println("ADC_Value: " + String(analogRead(PIN_ADC)*3.4/4095.0)+"V");
        }

        //Not valid Command
        else{
          Serial.println("Not valid command");
        }
      ////////
    }


    //WITH BRAKETS
    else if(input.endsWith(")")){
      String header=input.substring(0,iBrackets);
      String content=input.substring(iBrackets+1,input.length()-1);

    ////////
      //ADC -> Devolver valor del ADC cada s segundos (0 = parar envio)
      if (header=="ADC"){
        int ClockTime = content.toInt();
        if(ClockTime){
          timerAlarmWrite(timer, ClockTime*100000, true);        //N_of_Ticks
          timerAlarmEnable(timer);
          Serial.println("ADC_timer: Enabled each " + String(ClockTime)+"s");
        }else{
          timerAlarmDisable(timer);
          Serial.println("ADC_timer: Disabled");
        }
      }

      //PWM -> PWM al valor de x*10%  (Valore no validos x=0)
      if (header=="PWM"){
        ledcWrite(LedChannel,(content.toInt()*4096.0/9.0));
        Serial.println("PWM_set_to: " + String(content.toInt()*100.0/9.0)+"%");
      }

      //Not valid Command
      else {
        ("Not valid command");
      }
    ////////

    }

    //NONE
    else{
      Serial.println("Not valid input");
    }



  }
}


void loop() {
sleep(1);
}



