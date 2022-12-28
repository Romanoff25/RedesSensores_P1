/*Program to use GATT service on ESP32 to send Battery Level
 * ESP32 works as server - Mobile as client
 * Program by: B.Aswinth Raj
 * Dated on: 13-10-2018
 * Website: www.circuitdigest.com
 */
#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h> //Library to use BLE as server
#include <BLE2902.h>

bool _BLEClientConnected = false;
BLECharacteristic CountCharacteristic(BLEUUID("2A19"), BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor CountDescriptor(BLEUUID("2901"));

class MyServerCallbacks : public BLEServerCallbacks {

    void onConnect(BLEServer* pServer) {
      _BLEClientConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      _BLEClientConnected = false;
    }
};

void InitBLE() {
  BLEDevice::init("GATT Counter");
  // Create the BLE Server
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  // Create the BLE Service
  BLEService *pCounter = pServer->createService(BLEUUID("180F"));
  pCounter->addCharacteristic(&CountCharacteristic);
  CountDescriptor.setValue("Percentage 0 - 100");
  CountCharacteristic.addDescriptor(&CountDescriptor);
  CountCharacteristic.addDescriptor(new BLE2902());
  pServer->getAdvertising()->addServiceUUID(BLEUUID("180F"));
  pCounter->start();
  // Start advertising
  pServer->getAdvertising()->start();

}

void setup() {
  Serial.begin(115200);
  Serial.println("Counter - GATT");
  InitBLE();
}

uint8_t counter = 0;
void loop() {
  CountCharacteristic.setValue(&counter,1);
  CountCharacteristic.notify();
  delay(1000);
  counter++;
  Serial.println(int(counter));

}

