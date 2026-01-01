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

//WiFiClient client;
const char*root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"...содержимое сертификата bank.gov.ua..." \
"-----END CERTIFICATE-----\n";






String url = "https://api.openweathermap.org/data/2.5/forecast?lat=50.4333&lon=30.6167&appid=f2af430fc3518278afe78c607fbf2623&units=metric";
String urlBank = "https://bank.gov.ua/NBUStatService/v1/statdirectory/exchangenew?&jsonvalcode=EUR&date=20251111";
StaticJsonDocument<1024>doc;






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

  time_t now;
  while(time(nullptr) < 100000)
  {
    delay(500);
    Serial.print(".");

  }
 Serial.println("\nTime synced");
 WiFiClientSecure clientsec;
 clientsec.setInsecure();

  HTTPClient http;

  http.begin(clientsec, url);
  http.addHeader("User-Agent", "ESP32");
  http.addHeader("Accept", "application/json");

 // if(!clientsec.connect("bank.gov.ua", 443))
  //{
   // Serial.println("Connection failed");
   // return;
  //}
 // Serial.println("TLS connected");

  Serial.println("WiFi Connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  
  //http.begin(clientsec, url);
  int httpCode = http.GET();
 // String pyload = http.getString();// отладка для запроса в банк
  //Serial.println(pyload);          // отладка для запроса в банк

  if(httpCode ==200)
  {
    DeserializationError error = deserializeJson(doc, http.getStream());
    Serial.println(httpCode);
    if(!error)
    {
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
  
    //if(WiFi.status() == WL_CONNECTED)
    //{
      // Serial.println(WiFi.localIP());
    //}
    //delay(3000);
}
  
    
  
  

   
    
   


