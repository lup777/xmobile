// addr_book.c
#include <string.h>

#include "ext2.h"
#include "menu.h"
#include "text_edit.h"
#include "task_mgr.h"

#include "addr_book.h"

#define ADDRESS_BOOK_MSG_BUFFER_LEN 50
#define MENU_LINES_NUM 7
#define MENU_LINE_LEN 16
#define TITLE_BUF_LEN 14

void addrBook_init(void);
void ui_init(void);
void ui_update(void);
void handle_kbd(char key);
void call(void);
void enter_callback(i8 entry_num);

String get_text_callback(u8 max_len, i8 entry_num);
//void menu_update(void);
//void menu_up(void);
//void menu_down(void);
//static void menu_show(void);

MessageBufferHandle_t addr_book_msg_buf_handle = NULL;
static StaticStreamBuffer_t msg_buf_struct;
static uint8_t msg_buffer[ ADDRESS_BOOK_MSG_BUFFER_LEN ];
static char buffer[ADDRESS_BOOK_MSG_BUFFER_LEN];
size_t rx_bytes;
static File ab_file;
bool ab_opened = false;

// === UI ====
static char te1_buf[TITLE_BUF_LEN];
static TextEdit te1;

MENU(MENU_LINES_NUM, MENU_LINE_LEN, ab_menu, enter_callback);
// ===========

Entry book[] = {
  INIT_ENTRY("mother", "+79213258134", "-"),
  INIT_ENTRY("futher", "+79213258134", "+79213258144"),
  INIT_ENTRY("markovka", "+79213258154", "+79213258164"),
  INIT_ENTRY("mother1", "+79213258124", "-"),
  INIT_ENTRY("futher1", "+79213258134", "+79213258144"),
  INIT_ENTRY("markovka1", "+79213258154", "+79213258164"),
  INIT_ENTRY("lup", "+79213258124", "+79213258164")
};
#define ADDR_BOOK_LEN (sizeof(book) / sizeof(Entry))

void enter_callback(i8 entry_num) {
  _log("menu enter (%d)>>>", entry_num);
  static char buf[PHONE_LEN + 1];

  buf[0] = MSG_HEADER_CALL;
  u8 len = u8min(PHONE_LEN, book[entry_num].data.phone1.len);

  memcpy(buf + 1, book[entry_num].data.phone1.str, len);

  _log("AB call %d (size = %d)", entry_num, len);
  xMessageBufferSend(tm_msg_buf_handle, buf,
                     len + 1,
                     portMAX_DELAY);
}

String get_text_callback(u8 max_len, i8 entry_num) {
  static Entry e;

  if (ab_opened) {
    ab_file.internal_seek_address = entry_num * sizeof(Entry);

    if (sizeof(Entry) == read_file2(&ab_file, (char*)(&e), sizeof(Entry))) {
      return (String){
        .str = e.data.name.str,
        .len = e.data.name.len
      };
    }
  } else {
    Entry* entry = book + entry_num;

    u8 len = u8min(entry->data.name.len, max_len);

    if (entry_num < (i8)ADDR_BOOK_LEN && entry_num > 0)
      return (String){
        .str = entry->data.name.str,
        .len = len
      };
  }

  return (String){"--------", 8};
}

//MenuAB menu = INIT_MENU(book);

void addrBook_init(void) {
  raw_logc("addrBook_init? >>>");

  static bool inited = false;

  if (inited)
    return;

  raw_logc("addrBook_init >>>");

  menu_init(&ab_menu, get_text_callback);

  addr_book_msg_buf_handle = xMessageBufferCreateStatic(
      sizeof(msg_buffer),
      msg_buffer,
      &msg_buf_struct);
  ui_init();

  ab_opened = open_cpath("/address_book.ab", &ab_file);

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
  textEdit_init(&te1, te1_buf, TITLE_BUF_LEN, nimbus_bold_16);
  textEdit_clear(&te1);
  textEdit_setcstr(&te1, "-ADDRESS BOOK-");
}

void ui_update(void) {
  raw_logc("addr book ui update");

  textEdit_render(&te1, 2, 3, &display);

  if (active_task != enum_task_addr_book)
    return;

  menu_render(&ab_menu, 3, 35);

  displayFlush();
}

void handle_kbd(char key) {
  switch(key) {
  case 17: // key up
    menu_prev(&ab_menu);
    break;

  case 26: // key down
    menu_next(&ab_menu);
    break;

  case 9: // enter
    menu_enter(&ab_menu);
    return;
  }
}
