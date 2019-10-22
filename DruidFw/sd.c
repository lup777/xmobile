// sd.c

// PE1 - chip select
// PD5..7 - SPI
#include "sd.h"

#define F_CPU 32000000UL
#include <util/delay.h>

#define CS_ENABLE PORTE.OUTCLR = PIN1_bm
#define CS_DISABLE PORTE.OUTSET = PIN1_bm

#define R1_IDLE 0x01

#define SD_CMD_GO_IDLE_STATE 0 //CMD0 R1
#define SD_CMD_READ_SINGLE_BLOCK 17 // CMD17 R1
#define SD_CMD_READ_CSD 9 // CMD9 R1
#define SD_CMD_SEND_OP_COND 1 // CMD1 R1
#define SD_READ_SINGLE_BLOCK 17 // CMD 17

typedef uint8_t u8;
typedef uint32_t u32;
typedef uint16_t u16;

static void spid_init(void);
static bool sd_reset(void);
//static void wait_idle(void);
static uint8_t send_byte(uint8_t);
static uint8_t read_byte(void);
static u8 send_cmd_r1(u8 cmd, u32 param);
static u8 wait_byte(void);
void sd_read_buffer(u8* buffer, u16 size);

static void spid_init(void) {
  PORTD.DIRSET = PIN5_bm | PIN7_bm; // MOSI, SCK
  PORTD.DIRCLR = PIN6_bm; // MISO
  PORTE.DIRSET = PIN1_bm; //CS

  SPID.INTCTRL = SPI_INTLVL_OFF_gc;

  SPID.CTRL = SPI_MASTER_bm | SPI_ENABLE_bm
    /*| SPI_CLK2X_bm
    | SPI_PRESCALER0_bm // 250 KGz (for 32MGz)
    | SPI_PRESCALER1_bm // 250 KGz (for 32MGz)*/
    | SPI_MODE_0_gc;
}

static bool sd_reset(void) {
  u8 r = send_cmd_r1(SD_CMD_GO_IDLE_STATE, 0);

  if (r != R1_IDLE) {
    _log("SD reset failed 0x%02X", r);
    return false;
  }
  return true;
}

bool sd_init(void) {
  PORTD.DIRSET = PIN5_bm; // MOSI (DI)
  PORTD.OUTSET = PIN5_bm; // MOSI (DI)
  PORTE.DIRSET = PIN1_bm; //CS
  PORTE.OUTSET = PIN1_bm; //CS
  CS_DISABLE;

  spid_init();

  raw_logc("send CMD 0");
  // CMD 0
  for (u8 j = 0; j < 0xFF; j++) {
    CS_DISABLE;
    // 80 clock impulses
    for (u8 i = 0; i < 10; i++) {
      send_byte(0xFF);
    }
    CS_ENABLE;

    if (sd_reset() == true)
      break;
  }

  raw_logc("send CMD 8");
  // CMD 8
  if (send_cmd_r1(8, 0x01AA) == 0x01) {
    //Check for SDC ver.2+ card
    u8 data[4];
    for (u8 i = 0; i < 4; i++) {
      data[i] = wait_byte();
    }
    _log("resp: %02X %02X %02X %02X",
	 data[0], data[1], data[2], data[3]);

    raw_logc("send ACMD 41");
    // CMD 41
    for (u8 i = 0; i < 0x1; i++) {
      u8 r = 0xFF;
      if (0x01 == send_cmd_r1(55, 0x65)) { // CMD 55
	send_byte(0x40 + 41); // CMD 41
	send_byte(0x40); // data 1
	send_byte(0x00); // data 2
	send_byte(0x00); // data 3
	send_byte(0x00); // data 4

	send_byte(0x17); // crc
	send_byte(0xFF); // dummy

	CS_DISABLE;
	send_byte(0xFF); // dummy
	CS_ENABLE;

	r = send_byte(0xFF); // resp
	if (r == 0) {
	  _log("SD init OK (%d)", i);
	  break;
	} else {
	  _sleep(300);
	}
      } // for
    } // if CMD 55
  }
  CS_DISABLE;

  for (u8 i = 0; i < 50; i++) {

    u8 r = 0xFF;

    CS_ENABLE;
    r = send_cmd_r1(SD_CMD_SEND_OP_COND, 0);
    CS_DISABLE;
    if (r == 0) {
      _log("SD init success (%d)", i);
      return true;
    }
  }
  raw_logc("SD init failed");
  return false;
}

static uint8_t send_byte(uint8_t b) {
  SPID.DATA = b;
  //raw_logc("wait flag");
  while((SPID.STATUS & SPI_IF_bm) == 0);
  //raw_logc("sent");
  return SPID.DATA;
}

static u8 wait_byte(void) {
  u8 r = 0xFF;
  for(u8 i = 0; i < 0xFF && r == 0xFF; i++) {
    r = read_byte();
  }
  if (r == 0xFF)
    raw_logc("wait byte failed");
  return r;
}

static uint8_t read_byte(void) {
  SPID.DATA = 0xFF;
  while((SPID.STATUS & SPI_IF_bm) == 0);
  return SPID.DATA;
}

static u8 send_cmd_r1(u8 cmd, u32 param) {
  //wait_byte();
  send_byte(0xFF);
  send_byte(cmd | 0x40);
  send_byte((u8) (param >> 24));
  send_byte((u8) (param >> 16));
  send_byte((u8) (param >> 8));
  send_byte((u8) param);

  // CRC
  if (cmd == 8)
    send_byte(0x87);
  else if (cmd == 0)
    send_byte(0x95);
  else
    send_byte(0xFF);

  u8 r = wait_byte();

  //_log("SD CMD%02d resp 0x%02X", cmd, r);
  return r;
}
#define SINGLE_DATA_TOKEN 0xFE

void sd_read_csd(uint8_t* buffer) {
  raw_logc("sd_read_csd >>>");
  CS_ENABLE;
  u8 r = send_cmd_r1(SD_CMD_READ_CSD, 0);
  if (r != 0) {
    _log("read csd failed 0x%02X", r);
    return;
  }

  r = wait_byte();
  _log("waiting token 0x%02X", r);
  for (u8 i = 0; i < 16; i++) {
    buffer[i] = wait_byte();
    _log("SD CSD: 0x%02X", buffer[i]);
  }

  send_byte(0xFF);
  send_byte(0xFF);
  CS_DISABLE;
}

void sd_read_buffer(u8* buffer, u16 size) {
  for (u16 i = 0; i < size; i++) {
    buffer[i] = read_byte();
    //_log("read 0x%02X", buffer[i]);
  }
}

bool sd_read_block_512b(u8* buffer, u32 addr) {
  CS_ENABLE;
  //SD_CMD_READ_SINGLE_BLOCK
  if ( 0x00 == send_cmd_r1(SD_READ_SINGLE_BLOCK, addr)) {
    raw_logc("SD_READ_SINGLE_BLOCK success");

    for (u8 i = 0; i < 10; i++) {
      if (SINGLE_DATA_TOKEN == wait_byte()) {
        sd_read_buffer(buffer, 512);
        CS_DISABLE;
        return true;
      }
    }
  }
  CS_DISABLE;
  return false;
}


/*bool sd_write_block_512b() {
  //http://we.easyelectronics.ru/AVR/mmcsd-i-avr-chast-2-rabota-s-kartoy.html
  }*/
