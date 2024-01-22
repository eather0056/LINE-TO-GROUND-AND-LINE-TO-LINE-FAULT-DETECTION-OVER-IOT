#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#include "ThingSpeak.h"

//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);

 unsigned long ch_no = 1692711;
    const char * write_api = "7YUU7RQW0GK0WNGJ";
    const char * read_api = "WXLQC9B84HBIW10K";
    String apiKey = "7YUU7RQW0GK0WNGJ"; 
       char auth[] = "mwa0000026133514";
       
       char ssid[] = "Iffat";
       char pass[] = "abcdefyou";
       
const char* server = "api.thingspeak.com";

    unsigned long startMillis;
    unsigned long currentMillis;
    const unsigned long period = 10000;

    WiFiClient client;
    
float breaker;
    int b = D3;
    int P;
    
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  nodemcu.begin(9600);
  
  while (!Serial) continue;
  WiFi.begin(ssid, pass);
          while (WiFi.status() != WL_CONNECTED)
          {
            delay(500);
            Serial.print(".");
//            lcd.clear();
//            lcd.print("............");
            delay(2000);
          }
              Serial.println("WiFi connected");
              Serial.println(WiFi.localIP());
//              lcd.clear();
//              lcd.setCursor(0,0);
//              lcd.print("WiFi connected");
//              lcd.setCursor(2,1);
//              lcd.print(WiFi.localIP());
              delay(2000);
              ThingSpeak.begin(client);
              startMillis = millis();

              pinMode(b,OUTPUT);
}


void loop() {
  
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");
  Serial.print("Recieved Phase:  ");
  String phase = data["Phase_"];
  Serial.println(phase);
  Serial.print("Recieved Zone:  ");
  float Zone = data["Zone_"];
  Serial.println(Zone);
    Serial.print("Recieved distence:  ");
  float distence = data["Distence"];
  Serial.println(distence);
  Serial.println("-----------------------------------------");


  if(phase == "'A'") {P=1;}
  if(phase == "'B'") {P=2;}
  if(phase == "'C'") {P=3;}
  if(phase == "'AB'") {P=4;}
  if(phase == "'BC'") {P=5;}
  if(phase == "'CA'") {P=6;}
  if(phase == "'ABC'") {P=7;}
  
breaker = ThingSpeak.readIntField(ch_no,8,read_api);
delay(1000);
ThingSpeak.writeField(ch_no,4,P,write_api);
delay(16000);
ThingSpeak.writeField(ch_no,5,distence,write_api);
delay(17000);
ThingSpeak.writeField(ch_no,6,Zone,write_api);


if (breaker == 1){
  digitalWrite(b,LOW);}
 else if (breaker == 0)
  {digitalWrite(b,HIGH);}

  

}
