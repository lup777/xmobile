// kbd2.c

/* KBD I2C - TWIC
 SCL - PC1
 SDA - PC0
*/

#define  MAX7370_ADDR 0x38

#define WRITE_FLAG 0
#define READ_FLAG 1

#define Taktfreuqenz 32000000
#define Takt_TWI 400000
#define TWI_BAUD(F_SYS, F_TWI) ((F_SYS / (2 * F_TWI)) - 5)
#define TWI_BAUDRATE TWI_BAUD(Taktfrequenz, Takt_TWI)

void send_address(uint8_t rw);
void start_tx(void);
void start_rx(void);

void twi_init(void);
void max7370_init(void);


void kbd_init(void) {
  twi_init();
  max7370_init();
}

void twi_init(void) {
  TWIC_MASTER_BAUD = TWI_BAUDRATE;

  TWIC_MASTER_CTRLA
    = TWI_MASTER_ENABLE_bm
    | TWI_MASTER_INTLVL_OFF_gc;
  //| TWI_MASTER_RIEN_bm;

  TWIC_MASTER_CTRLB = 0;
  TWIC_MASTER_CTRLC = 0;
  TWIC_MASTER_STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;
}

#define MAX7370_REG_CONFIG        0x01
#define MAX7370_REG_DEBOUNCE      0x02
#define MAX7370_REG_INTERRUPT     0x03
#define MAX7370_REG_SLEEP         0x06
#define MAX7370_REG_ARR_SIZE      0x30

// MAX7370_REG_CONFIG
#define MAX7370_CFG_ENABLE_KEY_RELEASE   (1 << 3)
#define MAX7370_CFG_INTERRUPT_UNTIL_READ (1 << 5)
#define MAX7370_CFG_WAKEUP               (1 << 7)

// MAX7370_REG_SLEEP
#define MAX7370_AUTOSLEEP_DISABLE 0

void max7370_init(void) {
  // disable sleep, enable key release, clear int on first read
  max7370_write_reg(client, 
		    MAX7370_REG_CONFIG, MAX7370_CFG_KEY_NORELEASE | MAX7370_CFG_INTERRUPT | MAX7370_CFG_WAKEUP);

  // debounce time 16ms
  max7370_write_reg(client, MAX7370_REG_DEBOUNCE, 0x77);
  
  // nINT asserts every debounce cycles
  max7370_write_reg(client, MAX7370_REG_INTERRUPT, 0x01);
  
  // disable Autosleep
  max7370_write_reg(client, MAX7370_REG_SLEEP, MAX7370_AUTOSLEEP_DISABLE);
 
  // kb arr size
  max7370_write_reg(client, MAX7370_REG_ARR_SIZE, 0xFF); 
}

void kbd_send_data(uint8_t addr, uint8_t* data, size_t len) {
  // bus to idle state
  TWIC_MASTER_STATUS = TWI_MASTER_BUSSTATE_IDLE_gc;

  // write address, direction bit and start condition
  TWIC_MASTER_ADDR = (MAX7370_ADDR << 1) + TWI_MASTER_WRITE;

  // waite for write complete
  while( !(TWIC_MASTER_STATUS & TWI_MASTER_WIF_bm) );

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

  uint8_t data = TWIC_MASTER_RIF_bm;

  TWIC_MASTER_CTRLC = TWI_MASTER_ACKACT_bm | TWI_MASTER_CMD_STOP_gc;

  return data;
}
