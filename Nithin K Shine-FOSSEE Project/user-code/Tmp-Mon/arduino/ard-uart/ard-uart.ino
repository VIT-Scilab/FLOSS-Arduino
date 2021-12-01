#include "SoftwareSerial.h"
 
SoftwareSerial wifi(2,3) ; // rx , tx 
 
void setup()
{
Serial.begin(9600); 
wifi.begin(9600); 
  
}
 
void loop()
 
{
  
  Serial.println(" I am sending message to Webserver using ESP32"); 
  wifi.println(" Message from Arduino   "); 
  delay(1000); 
}
