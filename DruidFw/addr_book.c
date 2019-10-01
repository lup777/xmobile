// addr_book.c
#include "addr_book.h"
#include "text_edit.h"
#include "task_mgr.h"
#include <string.h>

#define ADDRESS_BOOK_MSG_BUFFER_LEN 50

void addrBook_init(void);
void ui_init(void);
void ui_update(void);
void handle_kbd(char key);
void call(void);
void menu_update(void);
void menu_up(void);
void menu_down(void);
void menu_show(void);

MessageBufferHandle_t addr_book_msg_buf_handle = NULL;
static StaticStreamBuffer_t msg_buf_struct;
static uint8_t msg_buffer[ ADDRESS_BOOK_MSG_BUFFER_LEN ];
static char buffer[ADDRESS_BOOK_MSG_BUFFER_LEN];
size_t rx_bytes;

// === UI ====
static char te1_buf[12];
static TextEdit te1;

static char tes_buf[LINE_BUF_LEN * MENU_SIZE];
static TextEdit tes[MENU_SIZE];
// ===========

Entry book[] = {
  INIT_ENTRY("mother", "+79213258124", "-"),
  INIT_ENTRY("futher", "+79213258134", "+79213258144"),
  INIT_ENTRY("markovka", "+79213258154", "+79213258164"),
  INIT_ENTRY("mother1", "+79213258124", "-"),
  INIT_ENTRY("futher1", "+79213258134", "+79213258144"),
  INIT_ENTRY("markovka1", "+79213258154", "+79213258164"),
  INIT_ENTRY("markovka2", "+79213258154", "+79213258164")
};
#define ADDR_BOOK_LEN (sizeof(book) / sizeof(Entry))

Menu menu = INIT_MENU(book);

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
  for (i = 0; i < MENU_SIZE; i++) {
    char* buff = tes_buf + (LINE_BUF_LEN * i);
    textEdit_init(tes + i, buff, LINE_BUF_LEN, nimbus_mono_10);
  }

  textEdit_select(tes + (MENU_SIZE >> 1));

  for (i = 0; i < MENU_SIZE; i++) {
    textEdit_maximize(tes + i);
  }
}

void ui_update(void) {
  raw_logc("addr book ui update");
  if (active_task != enum_task_addr_book)
    return;

  textEdit_render(&te1, 22, 3, &display);

  /*for (i = 0; i < LINES; i++, y += 25) {
    textEdit_render(tes + i, 22, y, &display);
  }*/

  menu_show();

  displayFlush();
}

void menu_update(void) {
  for(uint8_t i = 0; i < MENU_SIZE; i++) {
    if (menu.book_index + i < (int8_t)ADDR_BOOK_LEN
	&& menu.book_index + i >= 0)
      menu.entries[i] = &(book[menu.book_index + i].data);
    else
      menu.entries[i] = NULL;
  }
}

void menu_show(void) {
  uint8_t y = 40;

  menu_update();
  for(uint8_t i = 0; i < MENU_SIZE; i++, y += 25) {
    if (menu.entries[i] != NULL) {
      textEdit_setstr(tes + i, menu.entries[i]->name.str, menu.entries[i]->name.len);
      textEdit_render(tes + i, 3, y, &display);
    } else {
    }
  }
}

void handle_kbd(char key) {
  switch(key) {
  case 17: // key up
    if (menu.book_index > 0 - (MENU_SIZE >> 1))
      menu.book_index --;
    break;

  case 26: // key down
    if (menu.book_index <
	(int8_t)(ADDR_BOOK_LEN - (MENU_SIZE >> 1) - 1))
      menu.book_index ++;
    break;

  case 9: // enter
    call();
    return;
  }
  _log("menu.book_index = %d", menu.book_index);
/*
#error AAAAAAAAAAAAAAAAa
  for (uint8_t i = 0; i < MENU_SIZE; i++) {
    if (i == menu_index)
      textEdit_select(tes + i);
    else
      textEdit_deselect(tes + i);
  }*/
}

void call(void) {
  static char buf[LINE_BUF_LEN];
  uint8_t size;
  buf[0] = MSG_HEADER_CALL;

  uint8_t entry_index = menu.book_index + (MENU_SIZE >> 1);

  size = book[entry_index].data.phone1.len;
  memcpy(buf + 1, book[entry_index].data.phone1.str, size);

  _log("AB call %d", entry_index);

  xMessageBufferSend(tm_msg_buf_handle, buf,
		     size + 1,
		     portMAX_DELAY);
}

void menu_up() {
  menu.book_index ++;
}

void menu_down() {
  if (menu.book_index > 0)
    menu.book_index --;
}
