// kbd2.c

/* KBD I2C - TWIC
 SCL - PC1
 SDA - PC0
*/
#include <avr/io.h>
#include <avr/interrupt.h>

#include "global.h"
#include "usart.h"

#include "kbd2.h"
#include "task_mgr.h"

#define  MAX7370_ADDR 0x38

#define WRITE_FLAG 0
#define READ_FLAG 1

#define Takt_TWI 400000
#define TWI_BAUD(F_SYS, F_TWI) ((F_SYS / (2 * F_TWI)) - 5)
#define TWI_BAUDRATE TWI_BAUD(configCPU_CLOCK_HZ, Takt_TWI)

//void send_address(uint8_t rw);
//void start_tx(void);
//void start_rx(void);
void kbd_send_data(uint8_t addr, uint8_t* data, size_t len);
uint8_t kbd_read_byte(uint8_t addr);

void twi_init(void);
void max7370_init(void);

#define TWI_MASTER_WRITE 0
#define TWI_MASTER_READ  1

#define MAX7370_REG_FIFO          0x00
#define MAX7370_REG_CONFIG        0x01
#define MAX7370_REG_DEBOUNCE      0x02
#define MAX7370_REG_INTERRUPT     0x03
#define MAX7370_REG_SLEEP         0x06
#define MAX7370_REG_ARR_SIZE      0x30
#define MAX7370_REG_LED_ENABLE    0x31
#define MAX7370_REG_CONST_CURRENT 0x43
#define MAX7370_REG_PWM           0x45
#define MAX7370_REG_LED_CONF_C4   0x54
#define MAX7370_REG_LED_CONF_C5   0x55
#define MAX7370_REG_LED_CONF_C6   0x56
#define MAX7370_REG_LED_CONF_C7   0x57

// MAX7370_REG_CONFIG
#define MAX7370_CFG_ENABLE_KEY_RELEASE   (1 << 3)
#define MAX7370_CFG_INTERRUPT_UNTIL_READ (1 << 5)
#define MAX7370_CFG_WAKEUP               (1 << 7)

// MAX7370_REG_SLEEP
#define MAX7370_AUTOSLEEP_DISABLE 0

// col - 4
// row - 5
// int - PA0

void kbd_init(void) {
  raw_logc("kbd init");
  twi_init();
  max7370_init();


  PORTA.DIRCLR = PIN0_bm;
  PORTA.OUTCLR = PIN0_bm;

  PORTA.PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
  PORTA.INTCTRL = (PORT_INT1LVL_OFF_gc | PORT_INT0LVL_LO_gc);
  PORTA_INT0MASK = 0x01;
  raw_logc("kbd init complete");
}

void twi_init(void) {
  raw_logc("twi init");
  TWIC_MASTER_BAUD = TWI_BAUDRATE;

  TWIC_MASTER_CTRLA
    = TWI_MASTER_ENABLE_bm
    | TWI_MASTER_INTLVL_OFF_gc;
  //| TWI_MASTER_RIEN_bm;

  TWIC_MASTER_CTRLB = 0;
  TWIC_MASTER_CTRLC = 0;
  TWIC_MASTER_STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;
}

void max7370_init(void) {
  raw_logc("max7370 init");

  raw_logc("write config reg");
  // disable sleep, enable key release, clear int on first read
  kbd_send_reg_byte(MAX7370_REG_CONFIG,
		    MAX7370_CFG_INTERRUPT_UNTIL_READ
		    | MAX7370_CFG_WAKEUP);

  raw_logc("write debounce reg");
  // debounce time 16ms
  kbd_send_reg_byte(MAX7370_REG_DEBOUNCE, 0x77);

  raw_logc("write interrupt reg");
  // nINT asserts every debounce cycles
  kbd_send_reg_byte(MAX7370_REG_INTERRUPT, 0x01);

  raw_logc("write autosleep reg");
  // disable Autosleep
  kbd_send_reg_byte(MAX7370_REG_SLEEP, MAX7370_AUTOSLEEP_DISABLE);

  raw_logc("write arr size reg");
  // kb arr size
  kbd_send_reg_byte(MAX7370_REG_ARR_SIZE, 0x64);


  //kbd_send_reg_byte(MAX7370_REG_CONST_CURRENT, 0xC0);

  //kbd_send_reg_byte(MAX7370_REG_PWM, 0x0F);

  //kbd_send_reg_byte(MAX7370_REG_LED_CONF_C4, 0 | (1 << 5));
  //kbd_send_reg_byte(MAX7370_REG_LED_CONF_C5, 0 | (1 << 5));
  //kbd_send_reg_byte(MAX7370_REG_LED_CONF_C6, 0 | (1 << 5));
  //kbd_send_reg_byte(MAX7370_REG_LED_CONF_C7, 0 | (1 << 5));
  //kbd_send_reg_byte(MAX7370_REG_LED_ENABLE, 0x07);
}

void kbd_send_reg_byte(uint8_t addr, uint8_t data) {
  kbd_send_data(addr, &data, 1);
}

void kbd_send_data(uint8_t addr, uint8_t* data, size_t len) {
  // bus to idle state
  TWIC_MASTER_STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;

  // write address, direction bit and start condition
  TWIC_MASTER_ADDR = (MAX7370_ADDR << 1) + TWI_MASTER_WRITE;

  // waite for write complete
  while( !(TWIC_MASTER_STATUS & TWI_MASTER_WIF_bm) );

  // write data byte
  TWIC_MASTER_DATA = addr;


  size_t i = 0;
  for(; i < len; i ++) {
    // waite for write complete
    while( !(TWIC_MASTER_STATUS & TWI_MASTER_WIF_bm) );

    // write data byte
    TWIC_MASTER_DATA = data[i];
  }

  // waite for write complete
  while( !(TWIC_MASTER_STATUS & TWI_MASTER_WIF_bm) );

  // write stop condition cmd
  TWIC_MASTER_CTRLC = TWI_MASTER_CMD_STOP_gc;
}

uint8_t kbd_read_byte(uint8_t addr) {
  // bus to idle state
  TWIC_MASTER_STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;

  // write address, direction bit and start condition
  TWIC_MASTER_ADDR = (MAX7370_ADDR << 1) + TWI_MASTER_WRITE;

  // waite for write complete
  while( !(TWIC_MASTER_STATUS & TWI_MASTER_WIF_bm) );

  // write ack for receive action
  //TWIC_MASTER_CTRLC = TWI_MASTER_CMD_RECVTRANS_gc;

  // address of data to read
  TWIC_MASTER_DATA = addr;

  // waite for write complete
  while( !(TWIC_MASTER_STATUS & TWI_MASTER_WIF_bm) );

  // write stop cmd
  //TWIC_MASTER_CTRLC = TWI_MASTER_CMD_STOP_gc;

  // write start cond cmd and slave address with direction bit
  TWIC_MASTER_ADDR = (MAX7370_ADDR << 1) + TWI_MASTER_READ;

  while( !(TWIC_MASTER_STATUS & TWI_MASTER_RIF_bm) );

  uint8_t data = TWIC_MASTER_DATA;

  TWIC_MASTER_CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;

  return data;
}

ISR(PORTA_INT0_vect) {
  BaseType_t need_yeld = pdFALSE;
  static byte buffer[2];
  buffer[1] = kbd_read_byte(MAX7370_REG_FIFO);

  //_log("PORTA INT (%d)", key);
  buffer[0] = MSG_HEADER_KBD;

  xMessageBufferSendFromISR(tm_msg_buf_handle,
			    buffer,
			    2,
			    &need_yeld);
  if (need_yeld == pdTRUE)
    taskYIELD();
}

bool kbd_key_to_char(byte key, char* ch) {
  if (ch == NULL)
    return false;

  switch(key) {
  case 13: *ch = '1'; return true;
  case 18: *ch = '2'; return true;
  case 25: *ch = '3'; return true;
  case  1: *ch = '4'; return true;
  case  5: *ch = '5'; return true;
  case  3: *ch = '6'; return true;
  case 21: *ch = '7'; return true;
  case 11: *ch = '8'; return true;
  case  0: *ch = '9'; return true;
  case  8: *ch = '*'; return true;
  case  10: *ch = '0'; return true;
  case  16: *ch = '#'; return true;
  }
  return false;
}
