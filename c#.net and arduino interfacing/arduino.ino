#include <Wire.h>
#include <ArduinoJson.h>

char data;
void setup() {
  Serial.begin(9600); //initialize serial COM at 9600 baudrate
  pinMode(LED_BUILTIN, OUTPUT); //make the LED pin (13) as output
  
}

void loop() { 

  data = Serial.read();
if (data == 'N')
digitalWrite (LED_BUILTIN, HIGH);

else if (data == 'F')
digitalWrite (LED_BUILTIN, LOW);
}
