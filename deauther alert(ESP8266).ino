#include <ESP8266WiFi.h>

// D5 PIN_14

// D6 PIN_12

const char* ap = "automation";
const char* pass = "roboticworld";
int wifistatus;
int connectstatus=0;

void setup() 
  {
    pinMode(5, OUTPUT); //green
    pinMode(4, OUTPUT); //red
    WiFi.begin(ap,pass);
  }

void loop() 
{
  
wifistatus=WiFi.status();
  if(wifistatus!=WL_CONNECTED)

  {
                        digitalWrite(4, HIGH);
                        delay(200);
                        digitalWrite(4, LOW);
                        delay(200); 
    }
    else
                            
{
                       do
                       {
                       
                        digitalWrite(5, HIGH); 
                        digitalWrite(4, LOW);
                       }
                       while(wifistatus==WL_CONNECTED);
}
}
                   

                       
      
