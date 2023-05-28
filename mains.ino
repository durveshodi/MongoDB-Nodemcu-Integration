#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "mongodb.h"

ESP8266WiFiMulti WiFiMulti;
MongoDB MongoDB;

String url = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
String api = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
      


void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("WIFI 2", "odedara21");
  Serial.println("WiFi Connecting");
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  MongoDB.Client(url ,api);
  MongoDB.Cluster("AtlasCluster");
  
}

void loop() {

  Serial.println(" MongoDB.findOne("AtlasCluster" , "sample_guides" ,"Client","{\"age\":\"22\"}");");
  delay(2000);
  
  Serial.println("MongoDB.updateOne("AtlasCluster" , "sample_guides" ,"planets2","{\"age\":\"22\"}","{\"name\":\"DURVESH\",\"age\":\"40\"}");");
  delay(2000);
                                                                                   
  Serial.println(MongoDB.inserOne("AtlasCluster" , "mongo_test" ,"planets2","{\"name\":\"Durvesh\"}) );
  delay(2000);

  Serial.println("MongoDB.deleteOne("AtlasCluster" , "sample_guides" ,"planets2", "{\"name\":\"bhargav\"}");");
  delay(20000);
      
   Serial.println(MongoDB.findMany("AtlasCluster" , "sample_guides" ,"planets2","{\"name\":\"bhargav\"}"));
   delay(10000);
}
