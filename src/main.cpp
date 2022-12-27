
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial BT; // Objeto Bluetooth


void setup() {
  Serial.begin(115200); // Inicialización de la conexión en serie para la depuración
  BT.begin("ESP32_LED_Control"); // Nombre de su dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejarse");
}


void loop() {
  //RECIBIR
  if (BT.available()){// Comprueba si recibimos algo de Bluetooth
    Serial.print("Recibido: ");
    while (BT.available()){
      char incoming = BT.read(); // Lee lo que recibimos
      if(incoming == char(13)){
        Serial.println("");
      }else{
        Serial.print(incoming);
      }
    }
  }

  //ENVIAR
  if(Serial.available()){
    BT.println(Serial.read()); // Envía el mensaje de texto a través de BT Serial
  }

  //DELAY
  delay(20);
}




