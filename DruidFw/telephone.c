// telephone.c
#include "telephone.h"
#include "render.h"
#include "text_edit.h"
#include "ml_text_edit.h"
#include "kbd2.h"
#include "gsm.h"
#include <string.h>
//#include "fonts_nimbus_12_22.h"

#define TEL_MSG_BUFFER_LEN 50

void configure_usart(void);
void get_signal_quality(void);

bool is_cmd_rdy(void);
bool is_cmd_ok(void);
bool is_cmd_error(void);

// ===== TEL MessageBuffer data ===========
MessageBufferHandle_t tel_msg_buf_handle = NULL;
StaticStreamBuffer_t tel_msg_buf_struct;
static uint8_t tel_msg_buffer[ TEL_MSG_BUFFER_LEN ];
static void handle_kbd(char key);
void module_init(void);
void handle_state_machine(void);
void answer_call(void);
void send_cfg(void);
bool cmp(char* s1, const char* s2, size_t len);
bool is_contain(const char* pat);
void menu_render(void);
// ========================================

// ======== UI ============================
static char te_call_buf[12];
static char label_call_buf[5];
static TextEdit te_call;
static TextEdit label_call;

static char label_at_buf[2];
static TextEdit label_at;

static char label_disable_hf_buf[10];
static TextEdit label_disable_hf;

static char label_mic_gain_lvl_buf[16];
static TextEdit label_mic_gain_lvl;

static char label_get_imei_buf[8];
static TextEdit label_get_imei;

static char label_responce_format_buf[18];
static TextEdit label_responce_format;

#define MTE_LINE_LEN 20
char line1[MTE_LINE_LEN];
char line2[MTE_LINE_LEN];
char line3[MTE_LINE_LEN];
char line4[MTE_LINE_LEN];
char line5[MTE_LINE_LEN];
char line6[MTE_LINE_LEN];
char line7[MTE_LINE_LEN];
char line8[MTE_LINE_LEN];
char line9[MTE_LINE_LEN];
char line10[MTE_LINE_LEN];
char line11[MTE_LINE_LEN];
MlineTextEdit mte;
// ========================================

typedef enum {
  menu_call,
  menu_first = menu_call,
  menu_at,
  menu_set_mic_gain_lvl,
  menu_get_imei,
  menu_set_responce_format,
  menu_hf_disable,
  menu_last = menu_hf_disable
} MenuState;

typedef enum {
  state_cfg_usart,
  state_wait_rdy,
  state_set_params,
  state_ready,
} State;

static State state;
static MenuState menu_state;
static void ui_init(void);
static void ui_update(void);
void tel_init(void);
void vTelTask(void* pvParameters);


void tel_init(void) {
  raw_logc("tel_init? >>>");
  
  static bool inited = false;

  if (inited)
    return;

  raw_logc("tel_init. >>>");
  
  state = state_wait_rdy;
  tel_msg_buf_handle = xMessageBufferCreateStatic(
			   sizeof(tel_msg_buffer),
			   tel_msg_buffer,
			   &tel_msg_buf_struct);
  ui_init();
  inited = true;
}

static char buffer[TEL_MSG_BUFFER_LEN];
size_t rx_bytes;

void vTelTask(void* pvParameters) {
  (void)(pvParameters);

  tel_init();

  for(;;) {
    rx_bytes = xMessageBufferReceive(
		   tel_msg_buf_handle, buffer, 
		   TEL_MSG_BUFFER_LEN, portMAX_DELAY);
    raw_logc("TEL...");
    if (rx_bytes < 1) continue;

    switch(buffer[0]) {
    case MSG_HEADER_GSM:
      mlTextEdit_pushstr(&mte, buffer + 1, rx_bytes - 1);
      send_log_str(buffer + 1, rx_bytes - 1);
      //handle_state_machine();
      //ui_update();
      break;

    case MSG_HEADER_KBD: {
      char ch;
      if (true == kbd_key_to_char( buffer[1], &ch )) {
	textEdit_pushc(&te_call, ch);
	ui_update();
      } else {
	handle_kbd(buffer[1]);
      }
      break;
    } // case MSG_HEADER_KBD
      
    case MSG_HEADER_TM:
      ui_update();
      break;

    case MSG_HEADER_CALL:
      _log("call: %s", &buffer[1]);
      break;
    } // switch
  }
}

static void ui_init(void) {
  // call
  textEdit_init(&te_call, te_call_buf, 11, nimbus_bold_16);
  textEdit_maximize(&te_call);

  textEdit_init(&label_call, label_call_buf, 5, nimbus_bold_16);
  textEdit_setcstr(&label_call, "call:");

    // disable HF
  textEdit_init(&label_at, label_at_buf, 2, nimbus_bold_16);
  textEdit_setcstr(&label_at, "at");

  // disable HF
  textEdit_init(&label_disable_hf, label_disable_hf_buf, 10, nimbus_bold_16);
  textEdit_setcstr(&label_disable_hf, "disable HF");

  // set mic gain lvl
  textEdit_init(&label_mic_gain_lvl, label_mic_gain_lvl_buf, 16, nimbus_bold_16);
  textEdit_setcstr(&label_mic_gain_lvl, "set MIC gain lvl");

  // get IMEI
  textEdit_init(&label_get_imei, label_get_imei_buf, 8, nimbus_bold_16);
  textEdit_setcstr(&label_get_imei, "get IMEI");

  // reponce format
  textEdit_init(&label_responce_format, label_responce_format_buf, 18, nimbus_bold_16);
  textEdit_setcstr(&label_responce_format, "set respoce format");
  

  //textEdit_setcstr(&te1, "79213258124");
  mlTextEdit_init(&mte, 11, MTE_LINE_LEN, line1, line2, line3, line4, 
                  line5, line6, line7, line8, line9, line10, line11,
		  nimbus_mono_10);
  menu_state = menu_first;
}

static void ui_update(void) {
  _log("tel ui update");
  if (active_task != enum_task_tel)
    return;

  mlTextEdit_render(&mte, 7, 3, &display);

  menu_render();
  
  displayFlush();
}

void menu_render(void) {
  switch(menu_state) {
    
  case menu_call:
    textEdit_render(&label_call, 1, 172, &display);
    textEdit_render(&te_call, 57, 172, &display);
    break;

  case menu_at:
    textEdit_render(&label_at, 1, 172, &display);
    break;

  case menu_hf_disable:
    textEdit_render(&label_disable_hf, 1, 172, &display);
    break;

  case menu_get_imei:
    textEdit_render(&label_get_imei, 1, 172, &display);
    break;
    
  case menu_set_mic_gain_lvl:
    textEdit_render(&label_mic_gain_lvl, 1, 172, &display);
    break;

  case menu_set_responce_format:
    textEdit_render(&label_responce_format, 1, 172, &display);
    break;

  default:
    break;
  }
}

static void handle_kbd(char key) {
  _log("tel h kbd");
  switch(key) {
  case 24: // responce
    gsm_send_cstr("ATA");
    break;

  case 9: // enter
    switch(menu_state) {
    case menu_call:
      gsm_send_cstr_ne("ATD");
      gsm_send_str_ne(te_call.buffer, te_call.data_len);
      gsm_send_cstr(";");
      mlTextEdit_pushcstr(&mte, "calling...");
      
      
      break;

    case menu_at:
      gsm_send_cstr("AT");
      mlTextEdit_pushcstr(&mte, "AT");
      break;

    case menu_hf_disable:
      gsm_send_cstr("AT+CHF=1,0");
      mlTextEdit_pushcstr(&mte, "AT+CHF=1,0");
      break;

    case menu_get_imei:
      gsm_send_cstr("AT+GSN");
      mlTextEdit_pushcstr(&mte, "AT+GSN");
      break;

    case menu_set_mic_gain_lvl:
      gsm_send_cstr("AT+CMIC=0,7");
      mlTextEdit_pushcstr(&mte, "AT+CMIC=0,7");
      break;

    case menu_set_responce_format:
      gsm_send_cstr("ATV1");
      mlTextEdit_pushcstr(&mte, "ATV1");
      break;

    default:
      CHECK(0);
      break;
    }
    ui_update();
    break; // case 9: // enter

  case 27: // network status
    //_log("get sig quality");
    //get_signal_quality();
    gsm_send_cstr("AT+IFC=0,0;+IPR=115200;ATV1&W");
    mlTextEdit_pushcstr(&mte, "cmd sent");
    ui_update();
    break;

  case 2: {
    //gsm_send_cstr("AT&FZE0+IPR=115200;&W");
    char c;
    if (menu_state == menu_call) {
      
      textEdit_pop(&te_call, &c);
    }
    ui_update();
    break;
  }

  case 26:
    if (menu_state > menu_first)
      menu_state --;
    ui_update();
    break;

  case 17:
    if (menu_state < menu_last)
      menu_state ++;
    ui_update();
    break;

  case 29:
    gsm_send_cstr("ATH");
    mlTextEdit_pushcstr(&mte, "ATH");
    ui_update();
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
      state = state_ready;
      break;

    case state_wait_rdy:
      _log("_wait rdy");
      if (is_contain("RDY") == true) {
	_log("send CFG");
        state = state_ready;
        send_cfg();
      }
      break;

    case state_ready:
      ui_update();
      _log("_ready");
      break;

    default:
    CHECK(0);
      break;
  }
}


bool cmp(char* s1, const char* s2, size_t len) {
  for (size_t i = 0; i < len; i++) {
    _log("%d != %d", s1[i], s2[i]);
    if (s1[i] != s2[i]) {
      return false;
    }
  }
  return true;
}

bool is_contain(const char* pat) {
  size_t i = 0;
  for (i = 0; strlen(pat) < rx_bytes - i; i++) {
    if (cmp(buffer + i, pat, strlen(pat)))
      return true;
  }
  return false;
}

bool is_cmd_ok() {
  if (rx_bytes >= 2)
    if (buffer[1] == 'O')
      if (buffer[2] == 'K')
        return true;
  return false;
}

bool is_cmd_error() {
  if (rx_bytes >= 5)
    if (buffer[1] == 'E')
      if (buffer[2] == 'R')
        if (buffer[3] == 'R')
          if (buffer[4] == 'O')
            if (buffer[5] == 'R')
              return true;
  return false;
}

void send_cfg(void) {
static const char cmd[] = "\
AT\
+CHF=0,0;\
+SIDET=0,16;\
+CRSL=100;\
+CLVL=100;\
+CMIC=0,15;\
+CMUT=0;\
&W";
  gsm_send_cstr(cmd);
}

inline void answer_call(void) {
  gsm_send_cstr("ATA");
}

inline void configure_usart(void) {
  while( gsm_status() == false );
  gsm_send_cstr("AT");
}

inline void get_signal_quality(void) {
  gsm_send_cstr("AT+CSQ");
}
