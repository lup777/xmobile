// addr_book.c
#include "addr_book.h"
#include "text_edit.h"

#define ADDRESS_BOOK_MSG_BUFFER_LEN 50

void addrBook_init(void);
void ui_init(void);
void ui_update(void);

MessageBufferHandle_t addr_book_msg_buf_handle = NULL;
static StaticStreamBuffer_t msg_buf_struct;
static uint8_t msg_buffer[ ADDRESS_BOOK_MSG_BUFFER_LEN ];
static char buffer[ADDRESS_BOOK_MSG_BUFFER_LEN];
size_t rx_bytes;

// === UI ====
static char te1_buf[12];
static TextEdit te1;

static char te2_buf[12];
static TextEdit te2;

static char te3_buf[12];
static TextEdit te3;

static char te4_buf[12];
static TextEdit te4;
// ===========

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
      ui_update();
      break;
    }
  }
}

void ui_init(void) {
  textEdit_init(&te1, te1_buf, 12, nimbus_bold_16);
  textEdit_init(&te2, te2_buf, 12, nimbus_mono_10);
  textEdit_init(&te3, te3_buf, 12, nimbus_mono_10);
  textEdit_init(&te4, te4_buf, 12, nimbus_mono_10);

  textEdit_setcstr(&te1, "address book");
  textEdit_setcstr(&te2, "futher");
  textEdit_setcstr(&te3, "mother");
  textEdit_setcstr(&te4, "Markovka");

  textEdit_select(&te3);

  textEdit_maximize(&te1);
  textEdit_maximize(&te2);
  textEdit_maximize(&te3);
  textEdit_maximize(&te4);
}

void ui_update(void) {
  raw_logc("addr book ui update");
  if (active_task != enum_task_addr_book)
    return;

  textEdit_render(&te1, 22, 10, &display);
  textEdit_render(&te2, 22, 50, &display);
  textEdit_render(&te3, 22, 70, &display);
  textEdit_render(&te4, 22, 90, &display);

  displayFlush();
}
