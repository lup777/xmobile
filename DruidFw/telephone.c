// telephone.c
#include "telephone.h"
#include "render.h"
#include "text_edit.h"
#include "ml_text_edit.h"
#include "kbd2.h"
#include "gsm.h"

// ===== TEL MessageBuffer data ===========
MessageBufferHandle_t tel_msg_buf_handle;
StaticStreamBuffer_t tel_msg_buf_struct;
static uint8_t tel_msg_buffer[ 100 ];
static void handle_kbd(char key);
// ========================================

// ======== UI ============================
static char te1_buf[20];
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

static void ui_init(void);
static void ui_update(void);
void tel_init(void);
void vTelTask(void* pvParameters);


void tel_init(void) {
  tel_msg_buf_handle = xMessageBufferCreateStatic(sizeof(tel_msg_buffer),
						  tel_msg_buffer,
						  &tel_msg_buf_struct);
  ui_init();
}

void vTelTask(void* pvParameters) {
  (void)(pvParameters);

  tel_init();

  static char buffer[50];

  for(;;) {
    size_t rx_bytes = xMessageBufferReceive(tel_msg_buf_handle, buffer, 50, portMAX_DELAY);
    if (rx_bytes < 2) continue;

    switch(buffer[0]) {
    case MSG_HEADER_GSM:
      mlTextEdit_pushstr(&mte, buffer + 1, rx_bytes - 1);
      ui_update();
      break;

    case MSG_HEADER_KBD: {
      char ch;
      if (true == kbd_key_to_char( buffer[1], &ch )) {
	textEdit_pushc(&te1, ch);
      } else {
	handle_kbd(buffer[1]);
      }
      ui_update();
    } // case MSG_HEADER_KBD
    } // switch
  }
}

static void ui_init(void) {
  textEdit_init(&te1, te1_buf, 20);
  
  mlTextEdit_init(&mte, 7, MTE_LINE_LEN, line1, line2, line3, line4, line5, line6, line7);
}

static void ui_update(void) {
  displayRenderText(2, 173, "call: +", 7, &display);
  textEdit_render(&te1, 55, 170, &display);
  
  mlTextEdit_render(&mte, 3, 3, &display);

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

  default:
    break;

  } // switch
  
}
