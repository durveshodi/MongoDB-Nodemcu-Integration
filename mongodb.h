



#ifndef _MONGODB_H_
#define _MONGODB_H_

#include <Arduino.h>
#include <Arduino_JSON.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

class MongoDB {
public:
  void Client(String url, String api);
  void Cluster(String cluster);
  String Request(String action, String payload);
  String findOne(String database, String collection, String findOne);
  String insertOne(String database, String collection, String insertOne);
  String updateOne(String database, String collection, String filter, String updates);
  String deleteOne(String database, String collection, String deleteOne);
  String findMany(String database, String collection, String findMany);
  String insertMany(String database, String collection, String insertMany);
  String updateMany(String database, String collection, String filter, String updates);
  String deleteMany(String database, String collection, String deleteMany);
};



#endif
