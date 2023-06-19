#include "Arduino.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include "wifiFunctions.h"
#include <SPIFFS.h>

AsyncWebServer server(80);

void wifiFunc::setIPConfig(const IPAddress& ip, const IPAddress& gateway, const IPAddress& subnet){
  this-> ip = ip;
  this->gateway = gateway;
  this ->subnet = subnet;
}

void wifiFunc::begin(const char* ssid, const char* password, const char* htmlPath, const char* cssPath){
  
  if(!WiFi.softAPConfig(ip, gateway, subnet)){
    Serial.println("STA failed to configure");
  }
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print(F("To upload, go to:"));
  Serial.print(WiFi.softAPIP());
  Serial.println(F("/update\n"));
  
  /*
  String mensaje = "<p>To upload new software, please go to: " + ip.toString() + "/update</p>";
  server.on("/", HTTP_GET, [mensaje](AsyncWebServerRequest * request) {
    request->send(200, "text/html", mensaje);
  });
  */
  if(!SPIFFS.begin()){
    Serial.println("Error al montar SPIFFS");
    String mensaje = "<p>To upload new software, please go to: " + ip.toString() + "/update</p>";
    server.on("/", HTTP_GET, [mensaje](AsyncWebServerRequest * request) {
    request->send(200, "text/html", mensaje);
  });

  }
  else{
    server.on("/", HTTP_GET, [htmlPath](AsyncWebServerRequest *request){
    request->send(SPIFFS, htmlPath, "text/html");
  });
  server.serveStatic("/", SPIFFS, cssPath);

  }
    
  server.begin();
 

}

void wifiFunc::OverTheAirUpdate()
{
  AsyncElegantOTA.begin(&server);    // Start ElegantOTA
  
}