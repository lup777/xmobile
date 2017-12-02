#include <SPI.h>

enum {CHIP_SELECT = 8};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello world");

  SPI.transfer(0);
  
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("hey  hey hey!! :)");
  delay(2000);
}
