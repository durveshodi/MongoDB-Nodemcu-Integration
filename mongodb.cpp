
#include "mongodb.h"



String  _url , _api;

void MongoDB::Client(String url ,String api){
 _url  = url +  String("/action/");
 _api = api;
 
  Serial.print("[Client] URL : ");
  Serial.println(url);
  Serial.print("[Client] API : ");
  Serial.println(api);
}

void MongoDB::Cluster(String cluster){
   
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    String _Response ; 

    Serial.println("[Cluster] Checking ...");
    if (https.begin(*client, _url + String("find"))) { 
      https.addHeader("Content-Type", "application/json"); 
      https.addHeader("api-key", _api);
      
      int httpCode = https.POST( String("{\"collection\":\"test\",\"database\":\"test\",\"dataSource\":\"") + cluster + String("\",\"filter\": \"\"}") );
      
      if (httpCode > 0) {
        Serial.println("[Cluster] Available ");
        }
      else {
        Serial.println("[Cluster] not Available check Cluster name" );
      }

      https.end();
    } else {
      Serial.println("[Cluster] Unable to connect check entered Url\n");
    }

}

String  MongoDB::Request(String action , String payload){

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    HTTPClient https;
    String _Response ; 
    Serial.println("[MongoDB] Sending \"" + action + "\" Request...");
    if (https.begin(*client, _url + action)) {  // HTTPS
      
      https.addHeader("Content-Type", "application/json"); 
      https.addHeader("api-key", _api);
      int httpCode = https.POST( payload);
      
      if (httpCode > 0) {
        Serial.printf("[MongoDB] Succesfull Sended\n");
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY || httpCode == 201) {
           
            if(action == ("findOne")){              
               JSONVar data = JSON.parse(https.getString());
               _Response = JSON.stringify(data["document"]);
            }else if(action == ("find") ){              
               JSONVar data = JSON.parse(https.getString());
               _Response = JSON.stringify(data["documents"]);
            }else{
               _Response = https.getString();
            }
           Serial.print("[MongoDB] Payload : ");
           Serial.println(_Response);
          //Serial.println(Response);
        }
       else {
        Serial.println("[MongoDB] Sending... failed, Check JSON formet.");
        Serial.print("[MongoDB] Http Response Code: ");
        Serial.println(httpCode);
      }
      }
      https.end();
    } else {
      Serial.printf("[MongoDB] Unable to connect check entered URL\n");
    }
  return _Response;
}

String MongoDB::findOne(String dataSource  , String database , String collection, String findOne ){
  String _json =  String("{\"collection\":\"") + collection + String("\",\"database\":\"")  + database + String("\",\"dataSource\":\"")  + dataSource + String("\",\"filter\":") + findOne + String('}');
 return MongoDB::Request( "findOne",  _json);
}

String MongoDB::insertOne(String dataSource  , String database , String collection, String insertOne ){
  String _json =  String("{\"collection\":\"") + collection + String("\",\"database\":\"")  + database + String("\",\"dataSource\":\"")  + dataSource + String("\",\"document\":") + insertOne + String('}');
  return MongoDB::Request( "insertOne",  _json);
}

String MongoDB::updateOne(String dataSource  , String database , String collection, String findOne , String updateOne ){
  String _json =  String("{\"collection\":\"") + collection + String("\",\"database\":\"")  + database + String("\",\"dataSource\":\"")  + dataSource + String("\",\"filter\":") + findOne + String(",\"update\":{\"$set\":")  + updateOne + String("}}") ;
 return MongoDB::Request("updateOne",  _json);
}

String MongoDB::deleteOne(String dataSource  , String database , String collection, String deleteOne ){
  String _json =  String("{\"collection\":\"") + collection + String("\",\"database\":\"")  + database + String("\",\"dataSource\":\"")  + dataSource + String("\",\"filter\":") + deleteOne + String('}');
  return MongoDB::Request( "deleteOne",  _json);
}

String MongoDB::findMany(String dataSource  , String database , String collection, String findMany ){
  String _json =  String("{\"collection\":\"") + collection + String("\",\"database\":\"")  + database + String("\",\"dataSource\":\"")  + dataSource + String("\",\"filter\":") + findMany + String('}');
 return MongoDB::Request( "find",  _json);
}

String MongoDB::insertMany(String dataSource  , String database , String collection, String insertMany ){
  String _json =  String("{\"collection\":\"") + collection + String("\",\"database\":\"")  + database + String("\",\"dataSource\":\"")  + dataSource + String("\",\"filter\":") + insertMany + String('}');
 return MongoDB::Request( "insertMany",  _json);
}

String MongoDB::updateMany(String dataSource  , String database , String collection, String updateMany ){
  String _json =  String("{\"collection\":\"") + collection + String("\",\"database\":\"")  + database + String("\",\"dataSource\":\"")  + dataSource + String("\",\"filter\":") + updateMany + String('}');
 return MongoDB::Request( "updateMany",  _json);
}

String MongoDB::deleteMany(String dataSource  , String database , String collection, String deleteMany ){
  String _json =  String("{\"collection\":\"") + collection + String("\",\"database\":\"")  + database + String("\",\"dataSource\":\"")  + dataSource + String("\",\"filter\":") + deleteMany + String('}');
 return MongoDB::Request( "deleteMany",  _json);
}
