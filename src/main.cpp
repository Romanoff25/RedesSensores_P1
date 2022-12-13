//LIBRERIES
#include <WiFi.h>
#include "time.h"
#include "ArduinoJson.h"
#include "ESP32Time.h"
#include <ESP32_FTPClient.h>

//GATEWAY DATA
const char* ssid       = "RSense";
const char* password   = "";

//CLIENT
WiFiClient client;
IPAddress IP_Server (192,168,0,193);

//NTP DATA
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

//RTC
ESP32Time rtc(0);

//FTP
char ftp_server[] = "155.210.150.77";
char ftp_user[]   = "rsense";
char ftp_pass[]   = "rsense";

ESP32_FTPClient ftp (ftp_server,ftp_user,ftp_pass, 5000, 2);



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
  Serial.print("Local:");  Serial.println(WiFi.localIP());
  Serial.print("Public:"); Serial.println(WiFi.gatewayIP());
  Serial.print("Subnet:"); Serial.println(WiFi.subnetMask());

  //Actualizar Hora
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
}


//PRINT TIME LOOP
void loop(){  
 
//FTP
  ftp.OpenConnection();
  ftp.ChangeWorkDir("/rsense/765647");
  ftp.InitFile("Type A");

    //New_File + Time
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  String file_name= String(timeinfo.tm_year%100) + "_" + String(timeinfo.tm_mday) + "_"+String(timeinfo.tm_hour) +":" + String(timeinfo.tm_min)+":"+ String(timeinfo.tm_sec) + ".json" ;
  ftp.NewFile(file_name.c_str());

    //JSON
  const int capacity = JSON_ARRAY_SIZE(4) + 15*JSON_OBJECT_SIZE(3);
  StaticJsonDocument<capacity> doc;

  doc[0]["bn"] = "d1";
  doc[0]["u"]   = rtc.getEpoch();
  doc[0]["t"]   = "V";
  doc[0]["v"]   = random();

  for(int i=1 ; i<10 ; i++){
    doc[i]["u"]   = "Cel";
    doc[i]["t"]   = rtc.getEpoch();
    doc[i]["v"]   = random();
  }

  String output = doc.as<String>();
  char buf[output.length()];
  output.toCharArray(buf,output.length());

    //Write JSON
  ftp.Write(buf);
  ftp.CloseFile();
  ftp.CloseConnection();

//Wait 10s
delay(10000);

}