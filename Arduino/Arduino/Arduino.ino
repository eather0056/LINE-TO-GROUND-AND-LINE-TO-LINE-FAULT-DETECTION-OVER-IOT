#include <Adafruit_GFX.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include<SoftwareSerial.h>
#include <ArduinoJson.h>

LiquidCrystal_I2C lcd(0x27,16,2); 
SoftwareSerial nodemcu(5, 6);

int ledPin1 = 1;
int ledPin2 = 2;
int ledPin3 = 3;
int ledPin4 = 4;
int ledPin5 = 0;
int ledPin6 = 10;
int ledPin7 = 7;
int ledPin8 = 8;
int ledPin9 = 11;
int ledPin10 = 12;
int ledPin11 = 13;
int ledPin12 = 9;
int matlabData;
int distance;

String Phase;
int Zone;

//float Phase;
//float Zone;
//float distance;
 
void setup() 
{

  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
  pinMode(ledPin5,OUTPUT);
  pinMode(ledPin6,OUTPUT);
  pinMode(ledPin7,OUTPUT);
  pinMode(ledPin8,OUTPUT);
  pinMode(ledPin9,OUTPUT);
  pinMode(ledPin10,OUTPUT);
  pinMode(ledPin11,OUTPUT);
  pinMode(ledPin12,OUTPUT);
  
   Wire.begin();
   nodemcu.begin(9600);
   Serial.begin(9600);
   
   lcd.begin();                 
   lcd.backlight();
   lcd.print(" Line Fault M. ");
   delay(1000);
   
}
 
void loop() 
{
   lcd.clear();
   
   if(Serial.available()>0) // if there is data to read
   {
    matlabData=Serial.read(); // read data

    switch (matlabData) {
    case 1:
      digitalWrite(ledPin1,HIGH);
      digitalWrite(ledPin4,HIGH);
      Phase = "'A'";
      break;
    case 2:
      digitalWrite(ledPin2,HIGH);
      digitalWrite(ledPin4,HIGH);
      Phase = "'B'";
    case 3:
     digitalWrite(ledPin3,HIGH);
     digitalWrite(ledPin4,HIGH);
     Phase = "'C'";
      break;
    case 4:
      digitalWrite(ledPin1,HIGH);
      digitalWrite(ledPin2,HIGH);
      digitalWrite(ledPin4,HIGH);
      Phase = "'AB'";
      break;
    case 5:
      digitalWrite(ledPin2,HIGH);
      digitalWrite(ledPin3,HIGH);
      digitalWrite(ledPin4,HIGH);
      Phase = "'BC'";
      break;
    case 6:
      digitalWrite(ledPin1,HIGH);
      digitalWrite(ledPin3,HIGH);
      digitalWrite(ledPin4,HIGH);
      Phase = "'CA'";
      break;
    case 7:
      digitalWrite(ledPin2,HIGH);
      digitalWrite(ledPin1,HIGH);
      digitalWrite(ledPin3,HIGH);
      digitalWrite(ledPin4,HIGH);
      Phase = "'ABC'";
      break;
    case 8:
      digitalWrite(ledPin8,HIGH);
      distance = 600;
      Zone = 1;
      break;
    case 9:
     digitalWrite(ledPin9,HIGH);
     distance = 1000;
     Zone = 2;
     break;
    case 10:
     digitalWrite(ledPin10,HIGH);
     distance = 500;
     Zone = 3;
     break;
    case 11:
     digitalWrite(ledPin11,HIGH);
     distance = 200;
     Zone = 4;
     break;
    case 12:
     digitalWrite(ledPin12,HIGH);
     distance = 700;
     Zone = 5;
     break;
    
}

     if (matlabData==1)
        digitalWrite(ledPin1,HIGH);
    else if(matlabData==2)
      digitalWrite(ledPin2,LOW); 
    if(matlabData==3)
      analogWrite(ledPin3,255); 
    else if(matlabData==4)
      analogWrite(ledPin3,0); 
      else if (matlabData==5)
        digitalWrite(ledPin6,HIGH); 
    else if(matlabData==7)
      digitalWrite(ledPin4,LOW); 
  
    else  if(matlabData==8)
      analogWrite(ledPin5,255); 
      
    else if(matlabData==10)
      analogWrite(ledPin5,0); 
      else if (matlabData==11)
        analogWrite(ledPin6,255); 
    else if(matlabData==12)
      analogWrite(ledPin6,0); 
    if(matlabData== 5)
      digitalWrite(ledPin7,HIGH); 
      
    else if(matlabData=14)
      digitalWrite(ledPin7,LOW); 

  }
  digitalWrite(ledPin6,HIGH);
//  Zone = 50;
//  Phase =30;
//  distance =100;
  
  lcd.setCursor(0, 0);
  lcd.print("Fault At: ");
  lcd.print(Phase);
  lcd.setCursor(0, 1);
  lcd.print("Zone: ");
  lcd.print(Zone);
  delay(1500);
  
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("Km");
  delay(1500);

//  /////////////////////////////Data Transfer////////////////////////////
    StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();



  //Assign collected data to JSON Object
  data["Phase_"] = Phase;
  data["Zone_"] = Zone;
  data["Distence"] = distance;

  //Send data to NodeMCU
  data.printTo(nodemcu);
  jsonBuffer.clear();

  delay(2000);
}
