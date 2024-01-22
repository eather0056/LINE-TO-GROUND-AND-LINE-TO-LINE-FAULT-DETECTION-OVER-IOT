#include "ThingSpeak.h"
#include <NewPing.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>



//D6 = Rx & D5 = Tx
SoftwareSerial nodemcu(D6, D5);

    unsigned long ch_no = 1692711;
    const char * write_api = "7YUU7RQW0GK0WNGJ";
    const char * read_api = "WXLQC9B84HBIW10K";
    String apiKey = "7YUU7RQW0GK0WNGJ"; 
             
       char auth[] = "mwa0000026133514";
       char ssid[] = "Eather_D";
       char pass[] = "12345678";
const char* server = "api.thingspeak.com";

    unsigned long startMillis;
    unsigned long currentMillis;
    const unsigned long period = 10000;

    WiFiClient client;


 float CB;
 
void setup() {
 
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

              pinMode(D4,OUTPUT);
}



void loop() {
  
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
//    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");
  float phase = data["Phase_"];
  Serial.println(phase);
  float Zone = data["Zone_"];
  Serial.println(Zone);
   float distence = data["Distence"];
int CB = ThingSpeak.readIntField(ch_no,read_api);

if (CB==1)
{digitalWrite(D2,HIGH);}
else if(CB==0)
{digitalWrite(D2,LOW);}


ThingSpeak.writeField(ch_no,7,phase,write_api);
ThingSpeak.writeField(ch_no,7,zone,write_api);
ThingSpeak.writeField(ch_no,7,distance,write_api);
}
