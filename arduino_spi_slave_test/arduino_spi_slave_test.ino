#include <SoftwareSerial.h>
#include "pins_arduino.h"
#include <SPI.h>

char buf [100];
volatile byte pos;
volatile boolean process_it;
SoftwareSerial Serial1(2,3);

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  Serial1.begin(57600);
  Serial.write("hello!");

  // have to send on master in, *slave out*
  pinMode(12, OUTPUT); // MISO
  pinMode(10, INPUT);  // SS
  /*pinMode(11, INPUT);  // MOSI
  
  pinMode(13, INPUT);  // SCK*/

  // turn on SPI in slave mode
  SPCR |= (1 << SPE);

  // turn on interrupts
 SPCR |= (1 << SPIE);

 pos = 0;
 process_it = false;
}

// SPI interrupt routine
ISR (SPI_STC_vect)
{
  byte c = SPDR;
  Serial.print ("ISR received: ");
  Serial.write (c);
  Serial.println ("");
 
 // add to buffer if room
 if (pos < sizeof buf)
   {
   buf [pos++] = c;
   
   // example: newline means time to process buffer
   
   buf [pos++] = '\n';
   buf [pos++] = 0;
   process_it = true;
     
     // end of room available
  }
}
void loop() {
  if (Serial1.available())
    {
      Serial.write(Serial1.read());  
    }

  
  if ((SPSR & (1<<SPIF)) != 0)
  {
      unsigned char c = SPDR;
      Serial.println("ISR from main");
      Serial.println (c);
      pos = 0;
      process_it = false;
   }  // end of flag set
   
}
