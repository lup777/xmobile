#include <SoftwareSerial.h>


SoftwareSerial uno(2,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  uno.begin(57600);
  Serial.print("Hello!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(uno.available())
  {
    Serial.write(uno.read());
  }
}
