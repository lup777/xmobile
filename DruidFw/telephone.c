// telephone.c
#include "telephone.h"
#include "render.h"
#include "text_edit.h"
#include "ml_text_edit.h"
#include "kbd2.h"
#include "gsm.h"
//#include "fonts_nimbus_12_22.h"

#define TEL_MSG_BUFFER_LEN 50

// ===== TEL MessageBuffer data ===========
MessageBufferHandle_t tel_msg_buf_handle;
StaticStreamBuffer_t tel_msg_buf_struct;
static uint8_t tel_msg_buffer[ 100 ];
static void handle_kbd(char key);
void module_init(void);
void handle_state_machine(void);
void answer_call(void);
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

typedef enum {
  state_cfg_usart,
  state_wait_rdy,
  state_enable_hf,
  state_enable_hf_ok,
  state_enable_hf_failed,
  state_set_tone_gain_lvl,
  state_ready,
} State;

static State state;
static void ui_init(void);
static void ui_update(void);
void tel_init(void);
void vTelTask(void* pvParameters);


void tel_init(void) {
  state = state_cfg_usart;
  tel_msg_buf_handle = xMessageBufferCreateStatic(sizeof(tel_msg_buffer),
						  tel_msg_buffer,
						  &tel_msg_buf_struct);
  ui_init();
  handle_state_machine();
}

char buffer[TEL_MSG_BUFFER_LEN];
size_t rx_bytes;

void vTelTask(void* pvParameters) {
  (void)(pvParameters);

  tel_init();

  for(;;) {
    rx_bytes = xMessageBufferReceive(tel_msg_buf_handle, buffer, 
                                            TEL_MSG_BUFFER_LEN, portMAX_DELAY);
    if (rx_bytes < 2) continue;

    switch(buffer[0]) {
    case MSG_HEADER_GSM:
      mlTextEdit_pushstr(&mte, buffer + 1, rx_bytes - 1);
      send_log_str(buffer + 1, rx_bytes - 1);
      handle_state_machine();
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
      break;
    } // switch
  }
}

static void ui_init(void) {
  textEdit_init(&te1, te1_buf, 11);

  mlTextEdit_init(&mte, 7, MTE_LINE_LEN, line1, line2, line3, line4, line5, line6, line7);
}

static void ui_update(void) {
  displayRenderText(1, 172, "call:+", 6, &display);
  textEdit_render(&te1, 57, 172, &display);

  mlTextEdit_render(&mte, 7, 3, &display);

  displayFlush();
}

static void handle_kbd(char key) {
  switch(key) {
  case 24: // responce
    gsm_send_cstr("ATA");
    break;

  case 29: // call
    gsm_send_cstr_ne("ATD+");
    gsm_send_str_ne(te1.buffer, te1.data_len);
    gsm_send_cstr(";");
    break;

  case 27: // network status
    _log("get sig quality");
    get_signal_quality();
    break;

  default:
    break;

  } // switch

}

void handle_state_machine() {
  switch (state) {
    case state_cfg_usart: 
      configure_usart();
      state = state_wait_rdy;
      _log("state_wait_rdy");
      break;

    case state_wait_rdy:
      if (is_cmd_rdy()) {
        state = state_enable_hf;
        enable_hands_free();
        _log("state_enable_hf");
      }
      break;
    case state_enable_hf:
      if (is_cmd_ok()) {
        _log("ok");
        _log("set tone gain lvl");
        change_side_tone_gain_lvl();
        state = state_set_tone_gain_lvl;
      } else if (is_cmd_error()) {
        _log("failed");
        state = state_ready;
      }
      break;

    case state_set_tone_gain_lvl:
      if (is_cmd_ok()) {
        _log("ok");
        _log("state_ready");
        change_side_tone_gain_lvl();
      } else if (is_cmd_error()) {
        _log("failed");
      }
      _log("state_ready");
      state = state_ready;
      break;

    case state_ready:
      break;

    default:
    CHECK(0);
      break;
  }
}


bool is_cmd_rdy() {
  if (rx_bytes == 3)
    if (buffer[0] == 'R')
      if (buffer[1] == 'D')
        if (buffer[2] == 'Y')
          return true;
  return false;
}

bool is_cmd_ok() {
  if (rx_bytes == 2)
    if (buffer[0] == 'O')
      if (buffer[1] == 'K')
        return true;
  return false;
}

bool is_cmd_error() {
  if (rx_bytes == 5)
    if (buffer[0] == 'E')
      if (buffer[1] == 'R')
        if (buffer[2] == 'R')
          if (buffer[3] == 'O')
            if (buffer[4] == 'R')
              return true;
  return false;
}


inline void answer_call(void) {
  gsm_send_cstr("ATA");
}

inline void configure_usart(void) {
  gsm_send_cstr("AT");
}

inline void enable_hands_free(void) {
  gsm_send_cstr("AT+CHF=1,2");
}

inline void change_side_tone_gain_lvl(void) {
  gsm_send_cstr("AT+SIDET=2,16");
}

inline void get_signal_quality(void) {
  gsm_send_cstr("AT+CSQ");
}