                               // kbd.c

#include "global.h"
#include "kbd.h"

#include <avr/io.h>

#include "FreeRTOS.h"

/*void _sleep(uint16_t time_ms) {
  //TickType_t xDelay = time / portTICK_PERIOD_MS;
  vTaskDelay((TickType_t)(time_ms / portTICK_PERIOD_MS));
  }*/

void KBD_Init(void) {
  // KBD IN
  // PD 5 6 7

  // KBD OUT
  // PC 0 1 2
  PORTD.DIRSET = PIN5_bm | PIN6_bm | PIN7_bm;
  PORTD.OUTCLR = PIN5_bm | PIN6_bm | PIN7_bm;

  PORTC.DIRCLR = PIN0_bm | PIN1_bm | PIN2_bm;
  PORTC.PIN0CTRL = PORT_OPC_PULLDOWN_gc;
  PORTC.PIN1CTRL = PORT_OPC_PULLDOWN_gc;
  PORTC.PIN2CTRL = PORT_OPC_PULLDOWN_gc;
}

Key KBD_Check(void) {
  uint8_t counter = 0;
  Key new = KBD_Read();
  static Key old = keyNo;

  if (new == old)
    counter ++;
  else {
    counter = 0;
    old = new;
  }

  if (counter > 5) {
    counter = 0;
    return new;
  }
  return keyNo;
}

Key KBD_Read(void) {
  PORTD.OUTSET = PIN5_bm;
  _sleep(10);
  uint8_t pc0 = PORTC.IN & PIN0_bm;
  uint8_t pc1 = PORTC.IN & PIN1_bm;
  uint8_t pc2 = PORTC.IN & PIN2_bm;
  PORTD.OUTCLR = PIN5_bm;
  _sleep(10);

  if (pc0 != 0)
    return key1;
  if (pc1 != 0)
    return key2;
  if (pc2 != 0)
    return key3;

  PORTD.OUTSET = PIN6_bm;
  _sleep(10);
  pc0 = PORTC.IN & PIN0_bm;
  pc1 = PORTC.IN & PIN1_bm;
  pc2 = PORTC.IN & PIN2_bm;
  PORTD.OUTCLR = PIN6_bm;
  _sleep(10);

  if (pc0 != 0)
    return key4;
  if (pc1 != 0)
    return key5;
  if (pc2 != 0)
    return key6;

  PORTD.OUTSET = PIN7_bm;
  _sleep(10);
  pc0 = PORTC.IN & PIN0_bm;
  pc1 = PORTC.IN & PIN1_bm;
  pc2 = PORTC.IN & PIN2_bm;
  PORTD.OUTCLR = PIN7_bm;
  _sleep(10);

  if (pc0 != 0)
    return key7;
  if (pc1 != 0)
    return key8;
  if (pc2 != 0)
    return key9;

  return keyNo;
}
