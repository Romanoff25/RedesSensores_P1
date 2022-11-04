//LIBRERIES
#include <WiFi.h>
#include "time.h"


//GATEWAY DATA
const char* ssid       = "RSense";
const char* password   = "";

//const char* ssid       = "Vendo_Opel_Corsa";
//const char* password   = "adangorron";

//SERVER
//WiFiServer server(65432);

//CLIENT
WiFiClient client;
IPAddress IP_Server (192,168,0,193);

//NTP DATA
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

//IP DATA
IPAddress IP_local;
IPAddress IP_public;
IPAddress IP_SubnetMask;


//
String hostName = "www.google.com";




void setup()
{
  Serial.begin(115200);

  //Numero de redes disponibles
  Serial.println(WiFi.scanNetworks());

  //Connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //Save local IP
  IP_local = WiFi.localIP();
  IP_public = WiFi.gatewayIP();
  IP_SubnetMask = WiFi.subnetMask();

  Serial.print("Local:");  Serial.println(IP_local);
  Serial.print("Public:"); Serial.println(IP_public);
  Serial.print("Subnet:"); Serial.println(IP_SubnetMask);

  //Actualizar Hora
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
    
}


//PRINT TIME LOOP
void loop(){  

  //>>>>>>>>CLIENT<<<<<<<<<<
  client.connect(IP_Server, 65432);

  bool fSend = 0;
  String sServerRecived;

  while(client.connected()){

    //READ
    if(client.available()){
      while(client.available()){
        sServerRecived= sServerRecived+char(client.read());
      }
    }

    //COMMAND -> "start"
    if(sServerRecived =="start"){
      fSend=1;
    }

    //COMMAND -> "stop"
    if(sServerRecived =="stop"){
      fSend=0;
    }
    
    //PRINT TIME
    if(fSend){
      struct tm timeinfo;
      getLocalTime(&timeinfo);
        //Data Format
      char cData [16];
      cData[0] = char(timeinfo.tm_hour/10 + 0x30);
      cData[1] = char(timeinfo.tm_hour%10 + 0x30);
      cData[2] = char(0x3a);
      cData[3] = char(timeinfo.tm_min/10 + 0x30);
      cData[4] = char(timeinfo.tm_min%10 + 0x30);
      cData[5] = char(0x3a);
      cData[6] = char(timeinfo.tm_sec/10 + 0x30);
      cData[7] = char(timeinfo.tm_sec%10 + 0x30);
        //Send data
      client.write(cData);
      client.write("\n");
        //Delay
      delay(1000);
    }

    //CLEAN READ
    sServerRecived="";
  }


}



