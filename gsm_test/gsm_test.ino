#include <SoftwareSerial.h>

SoftwareSerial gsm(8,9); //aRDUINO RX (sim800 tx), aRDUINO TX (sim800 RX)

void setup() {
  // put your setup code here, to run once:
  delay(5000);
  Serial.begin(9600);
  Serial.println("hello!");  
  
  gsm.begin(9600);
  gsm.println("AT");
  
  while(!gsm.available()) {}
  Serial.write(gsm.read());
  delay(300);

  gsm.println("ATD+79213258124");
  
  /*
  gsm.println("AT+CMGF=1");
  while(!gsm.available()) {}
  Serial.write(gsm.read());
  delay(300);
  
  gsm.println("AT+CMGS=\"+79213258134\"");

  while(!gsm.available()) {}
  Serial.write(gsm.read());
  delay(300);

  gsm.println("Prinimat' sms poka ne ymeem :)");

  delay(300);
  gsm.print((char)26);*/
}

void loop() {
  if(gsm.available())
    Serial.write(gsm.read());
    
  if(Serial.available())
    gsm.write(Serial.read());
  // put your main code here, to run repeatedly:

}
