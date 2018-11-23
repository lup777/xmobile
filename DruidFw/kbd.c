                               // kbd.c

#include <stdio.h>

#include "FreeRTOS.h"

#include "global.h"
#include "kbd.h"

/*void _sleep(uint16_t time_ms) {
  //TickType_t xDelay = time / portTICK_PERIOD_MS;
  vTaskDelay((TickType_t)(time_ms / portTICK_PERIOD_MS));
  }*/

volatile uint16_t g_key_map;

#define KEY_1 (0x0001)
#define KEY_2 (1 << 1)
#define KEY_3 (1 << 2)
#define KEY_4 (1 << 3)
#define KEY_5 (1 << 4)
#define KEY_6 (1 << 5)
#define KEY_7 (1 << 6)
#define KEY_8 (1 << 7)
#define KEY_9 (1 << 8)
#define KEY_10 (1 << 9)
#define KEY_11 (1 << 10)
#define KEY_12 (1 << 11)
#define KEY_13 (1 << 12)
#define KEY_14 (1 << 13)
#define KEY_15 (1 << 14)
#define KEY_16 (1 << 15)

void KBD_Init(void) {
  // KBD OUT
  // PD 5 6 7

  // KBD IN
  // PC 0 1 2
  PORTD.DIRSET = PIN5_bm | PIN6_bm | PIN7_bm;
  //PORTD.OUTCLR = PIN5_bm | PIN6_bm | PIN7_bm;

  // slew rate
  //PORTD.PIN5CTRL |= PORT_SRLEN_bm;
  //PORTD.PIN6CTRL |= PORT_SRLEN_bm;
  //PORTD.PIN7CTRL |= PORT_SRLEN_bm;


  PORTC.DIRCLR = PIN0_bm | PIN1_bm | PIN2_bm;
  PORTC.PIN0CTRL |= PORT_OPC_PULLDOWN_gc;// | PORT_ISC_FALLING_gc; // | PORT_INVEN_bm;
  PORTC.PIN1CTRL |= PORT_OPC_PULLDOWN_gc;// | PORT_ISC_FALLING_gc; // | PORT_INVEN_bm;
  PORTC.PIN2CTRL |= PORT_OPC_PULLDOWN_gc;// | PORT_ISC_FALLING_gc; // | PORT_INVEN_bm;
}

//ISR(PORTC_INT0_vect) {}

Key KBD_Check(void) { // only 1 key at one time
  uint8_t i = (uint8_t)keyNo;
  uint16_t map = KBD_Read();

  if (map == 0 && g_key_map != 0) { // some key was released
    for (i = 0; i < 16; i++) {
      if (g_key_map & (uint16_t)(1 << i)) {
        break; // [i] key released
      }
    }
    g_key_map = 0; // clear last key map
  } else if (map != 0) {
    g_key_map = map;
  }

  char buf[] = "K:___";
  _u8tos(i, buf + 2, 3, 10);
  _log(buf);
  return (Key)i;
}

uint16_t KBD_Read(void) {
  uint16_t key_map = 0;
  uint8_t tmp = 0;

  PORTD.DIRCLR = PIN5_bm | PIN6_bm | PIN7_bm;
  PORTD.DIRSET = PIN5_bm;
  PORTD.OUTSET = PIN5_bm;

  _sleep(40);

  tmp = PORTC.IN;
  if ((tmp & PIN0_bm) != 0) {
    key_map |= KEY_1;
    _clog("key 1");
  }
  if ((tmp & PIN1_bm) != 0) {
    key_map |= KEY_2;
    _clog("key 2");
  }
  if ((tmp & PIN2_bm) != 0) {
    key_map |= KEY_3;
    _clog("key 3");
  }

  PORTD.OUTCLR = PIN5_bm;

  PORTD.DIRCLR = PIN5_bm | PIN6_bm | PIN7_bm;
  PORTD.DIRSET = PIN6_bm;
  PORTD.OUTSET = PIN6_bm;
  _sleep(40);

  tmp = PORTC.IN;
  if (tmp & PIN0_bm) {
    key_map |= KEY_4;
    _clog("key 4");
  }
  if (tmp & PIN1_bm) {
    key_map |= KEY_5;
    _clog("key 5");
  }
  if (tmp & PIN2_bm) {
    key_map |= KEY_6;
    _clog("key 6");
  }

  PORTD.OUTCLR = PIN6_bm;

  PORTD.DIRCLR = PIN5_bm | PIN6_bm | PIN7_bm;
  PORTD.DIRSET = PIN7_bm;
  PORTD.OUTSET = PIN7_bm;
  _sleep(40);

  tmp = PORTC.IN;
  if (tmp & PIN0_bm) {
    key_map |= KEY_7;
    _clog("key 7");
  }
  if (tmp & PIN1_bm) {
    key_map |= KEY_8;
    _clog("key 8");
  }
  if (tmp & PIN2_bm) {
    key_map |= KEY_9;
    _clog("key 9");
  }

  PORTD.OUTCLR = PIN7_bm;
  PORTD.DIRCLR = PIN5_bm | PIN6_bm | PIN7_bm;

  return key_map;
}
