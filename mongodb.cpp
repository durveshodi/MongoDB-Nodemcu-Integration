#include "mongodb.h"

String _url, _api , _cluster;

void MongoDB::Client(String url, String api) {
  _url = url + "/action/";
  _api = api;

  Serial.print("[Client] URL: ");
  Serial.println(url);
  Serial.print("[Client] API: ");
  Serial.println(api);
}

void MongoDB::Cluster(String cluster) {
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;
  String _Response;

  Serial.println("[Cluster] Checking ...");
  if (https.begin(*client, _url + cluster + "find")) {
    https.addHeader("Content-Type", "application/json"); 
    https.addHeader("api-key", _api);

    int httpCode =  https.POST( String("{\"collection\":\"test\",\"database\":\"test\",\"dataSource\":\"") + cluster + String("\",\"filter\": \"\"}") );
      

    if (httpCode > 0) {
      Serial.println("[Cluster] Available");
      _cluster = cluster;
    } else {
      Serial.println("[Cluster] Not available. Check cluster name");
      while( true){
        delay(1000);
        }
    }

    https.end();
  } else {
    Serial.println("[Cluster] Unable to connect. Check entered URL");
  }
}

String MongoDB::Request(String action, String payload) {
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;
  String _Response;
  Serial.println("[MongoDB] Sending \"" + action + "\" Request...");
  if (https.begin(*client, _url + action)) {  // HTTPS
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Authorization", _api);
    int httpCode = https.POST(payload);

    if (httpCode > 0) {
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode == 201) {
        if (action == "findOne") {
          Serial.printf("[MongoDB] Successfully sent\n");
          JSONVar data = JSON.parse(https.getString());
          _Response = JSON.stringify(data["document"]);
        } else if (action == "find") {
          JSONVar data = JSON.parse(https.getString());
          _Response = JSON.stringify(data["documents"]);
        } else {
          _Response = https.getString();
        }
        Serial.print("[MongoDB] Payload: ");
        Serial.println(_Response);
      } else {
        Serial.println("[MongoDB] Sending failed. Check JSON format.");
        Serial.print("[MongoDB] HTTP Response Code: ");
        Serial.println(httpCode);
      }
    }
    https.end();
  } else {
    Serial.printf("[MongoDB] Unable to connect. Check entered URL\n");
  }
  return _Response;
}

String MongoDB::findOne(String database, String collection, String filter) {
  String payload = filter ;
  String endpoint = "{\"collection\":\"" + collection + "\",\"database\":\""  + database + "\",\"dataSource\":\""  + _cluster + "\",\"filter\":" + payload + '}';
  return MongoDB::Request("findOne", endpoint);
  
}

String MongoDB::insertOne(String database, String collection, String document) {
  String payload = document;
  String endpoint = "{\"collection\":\"" + collection + "\",\"database\":\""  + database + "\",\"dataSource\":\""  + _cluster + "\",\"document\":" + payload + '}';
  return MongoDB::Request("insertOne", endpoint);
}

String MongoDB::updateOne(String database, String collection, String filter, String updates) {
  String payload[2] = {filter , updates} ;
  String endpoint = "{\"collection\":\"" + collection + "\",\"database\":\"" + database + "\",\"dataSource\":\"" + _cluster + "\",\"filter\":" + payload[0] + ",\"update\":{\"$set\":" + payload[1] + "}}";
  return MongoDB::Request("updateOne" , endpoint);
}

String MongoDB::deleteOne(String database, String collection, String filter) {
  String payload = filter;
  String endpoint = "{\"collection\":\"" + collection + "\",\"database\":\""  + database + "\",\"dataSource\":\""  + _cluster + "\",\"filter\":" + payload + '}';
  return MongoDB::Request("deleteOne" , endpoint);
}

String MongoDB::findMany(String database, String collection, String filter) {
  String payload = filter;
  String endpoint = "{\"collection\":\"" + collection + "\",\"database\":\""  + database + "\",\"dataSource\":\""  + _cluster + "\",\"filter\":" + payload + '}';
  return MongoDB::Request("find",endpoint);
}

String MongoDB::insertMany(String database, String collection, String documents) {
  String payload = documents;
  String endpoint = "{\"collection\":\"" + collection + "\",\"database\":\""  + database + "\",\"dataSource\":\""  + _cluster + "\",\"documents\":" + payload + '}';
  return MongoDB::Request("insertMany" , endpoint);
}

String MongoDB::updateMany(String database, String collection, String filter, String updates) {
  String payload[2] = {filter , updates} ;
  String endpoint = "{\"collection\":\"" + collection + "\",\"database\":\"" + database + "\",\"dataSource\":\"" + _cluster + "\",\"filter\":" + payload[0] + ",\"update\":{\"$set\":" + payload[1] + "}}";
  return MongoDB::Request("updateMany" , endpoint);
}

String MongoDB::deleteMany(String database, String collection, String filter) {
  String payload = filter;
  String endpoint = "{\"collection\":\"" + collection + "\",\"database\":\""  + database + "\",\"dataSource\":\""  + _cluster + "\",\"filter\":" + payload + '}';
  return MongoDB::Request("deleteMany" , endpoint);
}
