//LIBRARIES
#include <Arduino.h>  //Integra FreeRtos en si

//DEFINES
#define PIN_LED 5


//TAREAS

  //"Hola mundo"
void Tarea1( void * parameter ){
  while(1){
    Serial.println("Hola mundo");
    delay(1000);
  }
  vTaskDelete( NULL );
}

  //Led Blink
void Tarea2( void * parameter){
  while(1){
    digitalWrite(PIN_LED, HIGH);
    delay(200);
    digitalWrite(PIN_LED, LOW);
    delay(200);
  }
  vTaskDelete( NULL );
}


//SETUP
void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  xTaskCreate(Tarea1,"Tarea1",1000,NULL,1,NULL);
  xTaskCreate(Tarea2,"Tarea2",1000,NULL,1,NULL);

}


//MAIN LOOP
void loop() {

}


