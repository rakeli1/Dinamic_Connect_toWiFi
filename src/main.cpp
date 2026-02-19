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
JsonDocument doc;




String response;

struct WeatherPoint
{
   String timeData;
   float temp;
   float humidity;
   float pressure;
};

constexpr int MAX_POINTS = 40;
WeatherPoint forecastPoints[MAX_POINTS];
int pointsCount = 0;




void setup() 
{
  Serial.begin(9600);
  delay(3000);
  Serial.println("=====SETUP START=====");
  //clientsec.setCACert(root_ca);

  
  
  WiFi.mode(WIFI_STA);
  WiFi.setAutoReconnect(true);
  WiFi.begin(ssid, password);
 delay(500);
  Serial.print("Connecting to WiFi");
  while(WiFi.status()!= WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  delay(3000);
  
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
  http.useHTTP10(true);                       // раскомментировать при запросе в банк
  http.addHeader("User-Agent", "ESP32");      //  раскомментировать при запросе в банк       
  http.addHeader("Accept", "application/json"); // раскомментировать при запросе в банк      
  http.addHeader("Connection", "close");       //  раскомментировать при запросе в банк      
  http.setTimeout(5000);                       // раскоментировать при запросе в банк
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);//раскомментировать при запросе в банк!
  
  
  int httpCode = http.GET();
 

  if(httpCode > 0)
  {
    DeserializationError error = deserializeJson(doc, http.getStream());
    Serial.println(httpCode);
    if(!error)
    {
      //Serial.println("JSON REQUEST");
      serializeJson(doc, response);
      
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

  Serial.println(response);
}



void loop() 
{ 
  JsonArray arr = doc["list"];
  
  for(JsonObject p : arr)
  {
     if(pointsCount >= MAX_POINTS) break;

     //forecastPoints[pointsCount].timeData = p["dt_txt"];
     //forecastPoints[pointsCount].temp     = p["main"]["temp"];
     //forecastPoints[pointsCount].humidity = p["main"]["humidity"];
     //forecastPoints[pointsCount].pressure = p["main"]["pressure"];
     //pointsCount++;
  }
     for(int i = 0; i < pointsCount; i++)
     {
       //Serial.print("Time: "); Serial.println(forecastPoints[i].timeData);
       //Serial.print("Temp: "); Serial.println(forecastPoints[i].temp);
       //Serial.print("Humidity: "); Serial.println(forecastPoints[i].humidity);
       //Serial.print("Pressure: "); Serial.println(forecastPoints[i].pressure);
     }
  
    
}
  
    
  
  

   
    
   


