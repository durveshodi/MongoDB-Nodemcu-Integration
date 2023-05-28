#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "mongodb.h"

ESP8266WiFiMulti WiFiMulti;
MongoDB MongoDB;

String url = "https://data.mongodb-api.com/app/data-okora/endpoint/data/v1";
String api = "nlXJI6iJVPHMJDRCA1WrcTX2kEWx1wVZxtv2nkw9Sk76NSzKbdnv1TDCQchPWOzA";
      


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
  /*
  MongoDB.insertOne("AtlasCluster" , "sample_guides" ,"planets2", payload);
  Serial.println("");
  delay(2000);

  MongoDB.findOne("AtlasCluster" , "sample_guides" ,"planets2","{\"age\":\"22\"}");
  Serial.println("");
  delay(2000);

  MongoDB.updateOne("AtlasCluster" , "sample_guides" ,"planets2","{\"age\":\"22\"}","{\"name\":\"bhargav\",\"age\":\"40\"}");
  Serial.println("");
  delay(2000);
*/
  MongoDB.findMany("AtlasCluster" , "sample_guides" ,"planets2","{\"name\":\"bhargav\"}");
  Serial.println(MongoDB.insertMany("AtlasCluster" , "mongo_test" ,"planets2","{{\"name\":\"bhargav\"},{\"name\":\"Durvesh\"}}") );
  delay(2000);
/*/
  MongoDB.deleteOne("AtlasCluster" , "sample_guides" ,"planets2", "{\"name\":\"bhargav\"}");
  Serial.println("");
  delay(10000);
*/
}
