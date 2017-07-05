//import real time clock libraries
//#include <Wire.h>
//#include "RTClib.h"

//define real time clock setup
//RTC_DS1307 rtc;
//const int clock_pwr = A3;
//const int clock_gnd = A2;

//define sensor pins 
const int sensorPin = A0;
const int relayPercent = 8;
const int relay1000PPM = 7;
const int relay100PPM = 6;
const int relay10000PPM = 5;

//create sensor variables
float oxygen = 0.0;
byte sensorRange = 1+48;
int sensorValue = 0;


void setup()
{
  Serial.begin(9600);                  
  analogReference(INTERNAL);
  /*
  pinMode(clock_gnd, OUTPUT);
  digitalWrite(clock_gnd, LOW);
  
  pinMode(clock_pwr, OUTPUT);
  digitalWrite(clock_pwr, HIGH);
  
  delay(10);
  
  Wire.begin();
  rtc.begin();
 
  rtc.adjust(DateTime(__DATE__, __TIME__));
  
  DateTime now = rtc.now();
  Serial.print("Setup\t");
  
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(' ');
  Serial.println();
*/
  digitalWrite(sensorPin, LOW);
  pinMode(sensorPin, INPUT); 

  
  pinMode(relayPercent, OUTPUT);
  digitalWrite(relayPercent, HIGH);
  

  pinMode(relay1000PPM, OUTPUT);
  digitalWrite(relay1000PPM, HIGH);

  pinMode(relay100PPM, OUTPUT);
  digitalWrite(relay100PPM, HIGH);
  
  pinMode(relay10000PPM, OUTPUT);
  digitalWrite(relay10000PPM, HIGH);
 
    
  delay(10000);  
}



void loop() {
 
delay(1000);
  
//DateTime now = DateTime(__DATE__, __TIME__);

sensorValue = analogRead(sensorPin);
  
switch (sensorRange-48) {
    case 1://0-25%
      //Serial.println("Relay: 1");
      digitalWrite(relay10000PPM, HIGH);
      digitalWrite(relay100PPM, HIGH);
      digitalWrite(relay1000PPM, HIGH);
      digitalWrite(relayPercent, HIGH);
    break;
    
    case 2:// 0-10,000 ppm
      digitalWrite(relayPercent, LOW);
      digitalWrite(relay1000PPM, HIGH);
      digitalWrite(relay100PPM, HIGH);
      digitalWrite(relay10000PPM, LOW);  
    break;    
    
    case 3://0-1000 ppm
      digitalWrite(relayPercent, LOW);
      digitalWrite(relay10000PPM, HIGH);
      digitalWrite(relay100PPM, HIGH);
      digitalWrite(relay1000PPM, LOW);  
    break;
    
    case 4://0-100 ppm
      digitalWrite(relayPercent, LOW);
      digitalWrite(relay10000PPM, HIGH);
      digitalWrite(relay1000PPM, HIGH);
      digitalWrite(relay100PPM, LOW);  
    break;
   
    default: 
    break;   
}
  
  
  
  

switch (sensorRange-48) {
    case 1:
      oxygen = sensorValue * (25.0/1023.0);
      Serial.print("Relay: ");
      Serial.print(sensorRange-48);
      Serial.print(", Analog: "); 
      Serial.print(sensorValue);
      Serial.print(", %Vol Oxygen: ");
      Serial.print(oxygen, 1);
    break;
    
    case 2:// 0-10,000 ppm
      oxygen = sensorValue * (10000.0 / 1023.0);
      Serial.print("Relay: ");
      Serial.print(sensorRange-48);
      Serial.print(", Analog: "); 
      Serial.print(sensorValue);
      Serial.print(", 0-10,000PPM O2: ");
      Serial.print(oxygen, 1);
    break;    
    
    case 3:
    //0-1000 ppm
      oxygen = sensorValue * (1000.0 / 1023.0);
      Serial.print("Relay: ");
      Serial.print(sensorRange-48);
      Serial.print(", Analog: "); 
      Serial.print(sensorValue);
      Serial.print(", 0-1000PPM O2: ");
      Serial.print(oxygen, 1);
    break;
    
    case 4://0-100 ppm
      oxygen = sensorValue * (100.0 / 1023.0);
      Serial.print("Relay: ");
      Serial.print(sensorRange-48);
      Serial.print(", Analog: "); 
      Serial.print(sensorValue);    
      Serial.print(", 0-100PPM O2: ");
      Serial.print(oxygen, 1);
    break;  
    
    default: 
      sensorRange = 1+48;
     
  }
  /*
  Serial.print(", Time: ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  */
  Serial.println();
}


void serialEvent(){
 if (Serial.available() > 0) {
                
                sensorRange = Serial.read();
 }
}
