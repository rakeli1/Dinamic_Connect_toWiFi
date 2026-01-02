#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <FT6336U.h>
#include <Wire.h>
#include "Button.h"
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <time.h>


const char* ssid = "TP-Link_C810";
const char* password = "91891518";


String url = "https://api.openweathermap.org/data/2.5/forecast?lat=50.4333&lon=30.6167&appid=f2af430fc3518278afe78c607fbf2623&units=metric";
String urlBank = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchangenew?&jsonvalcode=EUR&date=20260101";
StaticJsonDocument<2048>doc;






void setup() 
{
  Serial.begin(9600);
  delay(5000);
  Serial.println("=====SETUP START=====");
  //clientsec.setCACert(root_ca);
  
  WiFi.begin(ssid, password);
 // WiFi.mode(WIFI_STA);
 delay(500);
  Serial.print("Connecting to WiFi");
  while(WiFi.status()!= WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");


  while(time(nullptr) < 100000)
  {
    delay(500);
    Serial.print(".");

  }
 Serial.println("\nTime synced");
 WiFiClientSecure clientsec;
 clientsec.setInsecure();

  

 

  Serial.println("WiFi Connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());



  HTTPClient http;

  http.begin(clientsec, urlBank); 

  http.setTimeout(5000);
  http.useHTTP10(true);                     
  http.addHeader("User-Agent", "ESP32");               
  http.addHeader("Accept", "application/json");        
  http.addHeader("Connection", "close");               

 
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);//раскомментировать при запросе в банк!
  
  
  int httpCode = http.GET();
 

  if(httpCode > 0)
  {
    DeserializationError error = deserializeJson(doc, http.getStream());
    Serial.println(httpCode);
    if(!error)
    {
      //Serial.println("JSON REQUEST");
      serializeJsonPretty(doc, Serial);
    }else
    {
      Serial.print("JSON parse error: ");
      Serial.println(error.c_str());
    }
  }else
  {
    Serial.print("HTTP request error: ");
    Serial.println(httpCode);
  }
  http.end();
}


void loop() 
{ 
  
    
}
  
    
  
  

   
    
   


