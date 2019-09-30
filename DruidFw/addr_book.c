// addr_book.c
#include "addr_book.h"
#include "text_edit.h"
#include "task_mgr.h"
#include <string.h>

#define ADDRESS_BOOK_MSG_BUFFER_LEN 50
#define LINES 5
#define LINE_BUF_LEN 12
const char futher_phone[] = "+79213258124";
const char mother_phone[] = "+79213258134";
const char markovka_phone[] = "+79213258144";

void addrBook_init(void);
void ui_init(void);
void ui_update(void);
void handle_kbd(char key);
void call(void);

MessageBufferHandle_t addr_book_msg_buf_handle = NULL;
static StaticStreamBuffer_t msg_buf_struct;
static uint8_t msg_buffer[ ADDRESS_BOOK_MSG_BUFFER_LEN ];
static char buffer[ADDRESS_BOOK_MSG_BUFFER_LEN];
size_t rx_bytes;

// === UI ====
static char te1_buf[12];
static TextEdit te1;

static char tes_buf[LINE_BUF_LEN * LINES];
static TextEdit tes[LINES];
// ===========

static uint8_t menu_index;

void addrBook_init(void) {
  raw_logc("addrBook_init? >>>");

  static bool inited = false;

  if (inited)
    return;

  raw_logc("addrBook_init >>>");

  addr_book_msg_buf_handle = xMessageBufferCreateStatic(
      sizeof(msg_buffer),
      msg_buffer,
      &msg_buf_struct);
  ui_init();
  inited = true;
  menu_index = 0;
}

void addrBook_task(void* pvParameters) {
  raw_logc("addrBook_task >>>");
  (void)(pvParameters);

  addrBook_init();

  for(;;) {
    rx_bytes = xMessageBufferReceive(
        addr_book_msg_buf_handle, buffer,
	ADDRESS_BOOK_MSG_BUFFER_LEN,
	portMAX_DELAY);
    raw_logc("addr book msg");
    if (rx_bytes < 1) continue;

    switch(buffer[0]) {
    case MSG_HEADER_TM:
      ui_update();
      break;

    case MSG_HEADER_KBD:
      raw_logc("add book key");
      handle_kbd(buffer[1]);
      ui_update();
      break;
    }
  }
}

void ui_init(void) {
  textEdit_init(&te1, te1_buf, 12, nimbus_bold_16);
  textEdit_setcstr(&te1, "ADDRESS BOOK");
    
  uint8_t i;
  for (i = 0; i < LINES; i++) {
    char* buff = tes_buf + (LINE_BUF_LEN * i);
    textEdit_init(tes + i, buff, LINE_BUF_LEN, nimbus_mono_10);
  }

  textEdit_setcstr(tes + 0, "futher");
  textEdit_setcstr(tes + 1, "mother");
  textEdit_setcstr(tes + 2, "Markovka");

  textEdit_select(tes + 1);

  for (i = 0; i < LINES; i++) {
    textEdit_maximize(tes + i);
  }
}

void ui_update(void) {
  raw_logc("addr book ui update");
  if (active_task != enum_task_addr_book)
    return;

  textEdit_render(&te1, 22, 3, &display);

  uint8_t i;
  uint8_t y = 40;
  
  for (i = 0; i < LINES; i++, y += 25) {
    textEdit_render(tes + i, 22, y, &display);
  }
  
  displayFlush();
}

void handle_kbd(char key) {
  switch(key) {
  case 17: // key up
    if (menu_index > 0)
      menu_index--;
    break;
    
  case 26: // key down
    if (menu_index < LINES - 1)
      menu_index ++;
    break; 

  case 9: // enter
    call();
    return;
  }
  
  for (uint8_t i = 0; i < LINES; i++) {
    if (i == menu_index)
      textEdit_select(tes + i);
    else
      textEdit_deselect(tes + i);
  }
}

void call(void) {
  static char buf[15];
  uint8_t size;
  _log("AB call %d", menu_index);
  buf[0] = MSG_HEADER_CALL;

  switch(menu_index) {
  case 0:
    size = sizeof(futher_phone);
    memcpy(buf + 1, futher_phone, size);
    break;
  case 1:
    size = sizeof(mother_phone);
    memcpy(buf + 1, mother_phone, size);
    break;
  case 2:
    size = sizeof(markovka_phone);
    memcpy(buf + 1, markovka_phone, size);
    break;
    
  default:
    size = sizeof(markovka_phone);
    memcpy(buf + 1, markovka_phone, size);
    break;
  }

  xMessageBufferSend(tm_msg_buf_handle, buf,
		     size + 1,
		     portMAX_DELAY);
}
