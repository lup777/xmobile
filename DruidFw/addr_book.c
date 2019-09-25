// addr_book.c
#include "addr_book.h"
#include "text_edit.h"

#define ADDRESS_BOOK_MSG_BUFFER_LEN 50

void addrBook_init(void);
void ui_init(void);
void ui_update(void);

MessageBufferHandle_t addr_book_msg_buf_handle;
static StaticStreamBuffer_t msg_buf_struct;
static uint8_t msg_buffer[ ADDRESS_BOOK_MSG_BUFFER_LEN ];
static char buffer[ADDRESS_BOOK_MSG_BUFFER_LEN];
size_t rx_bytes;

// === UI ====
static char te1_buf[12];
static TextEdit te1;
// ===========

void addrBook_init(void) {
  _log("addrBook_init >>>");
  addr_book_msg_buf_handle = xMessageBufferCreateStatic(
      sizeof(msg_buffer),
      msg_buffer,
      &msg_buf_struct);
  ui_init();
}

void addrBook_task(void* pvParameters) {
  _log("addrBook_task >>>");
  (void)(pvParameters);

  addrBook_init();

  for(;;) {
    rx_bytes = xMessageBufferReceive(
        addr_book_msg_buf_handle, buffer,
	ADDRESS_BOOK_MSG_BUFFER_LEN,
	portMAX_DELAY);
    _log("addr book msg");
    if (rx_bytes < 1) continue;

    switch(buffer[0]) {
    case MSG_HEADER_TM:
      ui_update();
      break;

    case MSG_HEADER_KBD:
      _log("addt book key");
      ui_update();
      break;
    }
  }
}

void ui_init(void) {
  textEdit_init(&te1, te1_buf, 12, nimbus_bold_16);

  textEdit_setcstr(&te1, "address book");
}

void ui_update(void) {
  _log("addr book ui update");
  if (active_task != enum_task_addr_book)
    return;

  textEdit_render(&te1, 22, 20, &display);  

  displayFlush();
}
