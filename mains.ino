#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "mongodb.h"

// Update these values with your MongoDB connection details
const char* WIFI_SSID = "WIFI 2";
const char* WIFI_PASSWORD = "odedara21";
const char* MONGODB_API_URL = "https://data.mongodb-api.com/app/data-okora/endpoint/data/v1";
const char* MONGODB_API_KEY = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

ESP8266WiFiMulti WiFiMulti;
// Create an instance of the MongoDB class
MongoDB mongodb; 

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connecting to WiFi...");
    
  // Initialize the MongoDB client
  mongodb.Client(MONGODB_API_URL, MONGODB_API_KEY);
  
  

}

void loop() {  
  // Cluster
  mongodb.Cluster("AtlasCluster");
  // Test the MongoDB functions

  // FindOne
  String findOneResult = mongodb.findOne("sample_guides", "user", "{\"name\": \"John\"}");
  Serial.print("findOne Result: ");
  Serial.println(findOneResult);

  // InsertOne
  String insertOneResult = mongodb.insertOne("sample_guides", "user", "{\"name\": \"John\", \"age\": 30}");
  Serial.print("insertOne Result: ");
  Serial.println(insertOneResult);

  // UpdateOne
  String updateOneResult = mongodb.updateOne("sample_guides", "user", "{\"name\": \"John\"}", "{\"age\": 35}");
  Serial.print("updateOne Result: ");
  Serial.println(updateOneResult);

  // DeleteOne
  String deleteOneResult = mongodb.deleteOne("sample_guides", "user", "{\"name\": \"John\"}");
  Serial.print("deleteOne Result: ");
  Serial.println(deleteOneResult);

  // FindMany
  String findManyResult = mongodb.findMany("sample_guides", "user", "{\"age\": {\"$gt\": 25}}");
  Serial.print("findMany Result: ");
  Serial.println(findManyResult);

  // InsertMany
  String insertManyResult = mongodb.insertMany("sample_guides", "user", "[{\"name\": \"John\", \"age\": 30}, {\"name\": \"Jane\", \"age\": 28}]");
  Serial.print("insertMany Result: ");
  Serial.println(insertManyResult);

  // UpdateMany
  String updateManyResult = mongodb.updateMany("sample_guides", "user", "{\"age\": {\"$gt\": 25}}", "{\"age\": 30}");
  Serial.print("updateMany Result: ");
  Serial.println(updateManyResult);

  // DeleteMany
  String deleteManyResult = mongodb.deleteMany("sample_guides", "user", "{\"age\": {\"$gt\": 25}}");
  Serial.print("deleteMany Result: ");
  Serial.println(deleteManyResult);

  delay(5000);  // Wait for 5 seconds before running the tests again
}
