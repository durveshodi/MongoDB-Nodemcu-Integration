



#ifndef _MONGODB_H_
#define _MONGODB_H_

#include <Arduino.h>
#include <Arduino_JSON.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

class MongoDB{
public:

//char action;


String insertOne(String dataSource  , String database , String collection, String insertOne );
String findOne(String dataSource  , String database , String collection, String findOne );
String updateOne(String dataSource  , String database , String collection, String findOne , String updateOne );
String deleteOne(String dataSource  , String database , String collection, String deleteOne );

String findMany(String dataSource  , String database , String collection, String findMany ); 
String insertMany(String dataSource  , String database , String collection, String insertMany );
String updateMany(String dataSource  , String database , String collection, String updateMany );
String deleteMany(String dataSource  , String database , String collection, String deleteMany );

void Client(String url ,String api);
void Cluster(String name);
String  Request(String url , String payload);

JSONVar finds(String dataSource  , String database , String collection, String findMany );
};



#endif
