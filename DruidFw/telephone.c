// telephone.c
#include "telephone.h"
#include "render.h"
#include "text_edit.h"
#include "ml_text_edit.h"
#include "kbd2.h"
#include "gsm.h"
//#include "fonts_nimbus_12_22.h"

// ===== TEL MessageBuffer data ===========
MessageBufferHandle_t tel_msg_buf_handle;
StaticStreamBuffer_t tel_msg_buf_struct;
static uint8_t tel_msg_buffer[ 100 ];
static void handle_kbd(char key);
void module_init(void);
// ========================================

// ======== UI ============================
static char te1_buf[11];
static TextEdit te1;

#define MTE_LINE_LEN 15
char line1[MTE_LINE_LEN];
char line2[MTE_LINE_LEN];
char line3[MTE_LINE_LEN];
char line4[MTE_LINE_LEN];
char line5[MTE_LINE_LEN];
char line6[MTE_LINE_LEN];
char line7[MTE_LINE_LEN];
MlineTextEdit mte;
// ========================================

volatile bool inited;
static void ui_init(void);
static void ui_update(void);
void tel_init(void);
void vTelTask(void* pvParameters);


void tel_init(void) {
  inited = false;
  tel_msg_buf_handle = xMessageBufferCreateStatic(sizeof(tel_msg_buffer),
						  tel_msg_buffer,
						  &tel_msg_buf_struct);
  ui_init();
}

char buffer[50];

void vTelTask(void* pvParameters) {
  (void)(pvParameters);

  tel_init();

  for(;;) {
    size_t rx_bytes = xMessageBufferReceive(tel_msg_buf_handle, buffer, 50, portMAX_DELAY);
    if (rx_bytes < 2) continue;

    switch(buffer[0]) {
    case MSG_HEADER_GSM:
      mlTextEdit_pushstr(&mte, buffer + 1, rx_bytes - 1);
      send_log_str(buffer + 1, rx_bytes - 1);
      ui_update();
      break;

    case MSG_HEADER_KBD: {
      char ch;
      if (true == kbd_key_to_char( buffer[1], &ch )) {
	textEdit_pushc(&te1, ch);
	ui_update();
      } else {
	handle_kbd(buffer[1]);
      }
    } // case MSG_HEADER_KBD
    case MSG_HEADER_TM:
      ui_update();
      if (inited == false) {
	//module_init();
	inited = true;
      }
      break;
    } // switch
  }
}

void module_init(void) {
  raw_logc("config usart");
  gsm_configure_usart();

  raw_logc("en HF");
  gsm_enable_hands_free();

  raw_logc("gain");
  gsm_change_side_tone_gain_lvl();

  send_log_str(buffer + 1, rx_bytes - 1);
  raw_logc("gsm init compl");
}

static void ui_init(void) {
  textEdit_init(&te1, te1_buf, 11);

  mlTextEdit_init(&mte, 7, MTE_LINE_LEN, line1, line2, line3, line4, line5, line6, line7);
}

static void ui_update(void) {
  displayRenderText(1, 172, "call:+", 6, &display);
  textEdit_render(&te1, 57, 172, &display);

  mlTextEdit_render(&mte, 7, 3, &display);

  /*const uint8_t tmp[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xf5, 0xff, 0xf5, 0xff, 0xed, 0xff, 0xee, 0xff, 0xee, 0xff, 0xde, 0x7f, 0xc0, 0x7f, 0xdf, 0xbf, 0xbf, 0x1f, 0xe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};*/

/*  {
    DispBuf pic;
    pic.buf_cols = 2; // byte
    pic.buf_rows = 22; // bits
    uint8_t buffer[44];
    pic.buffer = (byte*)buffer;

    for (byte j = 0; j < 44; j++) {
      pic.buffer[j] = pgm_read_byte_far( ch_32 + j );
    }


    displayRenderSubBuffer(30, 140, &pic, &display);
  }
  */
  displayFlush();
}

static void handle_kbd(char key) {
  switch(key) {
  case 24: // responce
    send_cstr("ATA\n\r");
    break;

  case 29: // call
    send_cstr("ATD+");
    send_str(te1.buffer, te1.data_len);
    send_cstr(";\r\n");
    break;

  case 27: // network status
    _log("get sig quality");
    gsm_get_signal_quality();
    break;

  default:
    break;

  } // switch

}
