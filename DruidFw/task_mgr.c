// task_mgr.c
// revert-buffer-with-coding-system koi8-r-unix
#include "task_mgr.h"
#include "render.h"
#include "pgm.h"
#include "epd.h"
#include "gsm.h"
#include "text_edit.h"
#include "check_box.h"
#include "telephone.h"
#include "addr_book.h"
#include "sd.h"

static void ui_init(void);
static void ui_update(void);
static void handle_msg(char *buffer, size_t msg_size);
inline void menu_down(void);
inline void menu_up(void);
static void task_mgr_hook(char* buffer, size_t msg_size);
void menu_enter(void);

int8_t state;
byte menu_size;
// ===== TASK MANAGER MessageBuffer data ===========
MessageBufferHandle_t tm_msg_buf_handle;
StaticStreamBuffer_t msg_buf_struct;
static uint8_t msg_buffer[ 50 ];
// ========================================

// ===== DISPLAY DATA =====================
byte display_buffer[DISPLAY_BUFFER_SIZE];
//byte dispay_spi_buf[DISPLAY_BUFFER_ROWS_BITS];
// ========================================

// ======== UI ============================
static char te1_buf[12];
static TextEdit te1;

static char te2_buf[12];
static TextEdit te2;

static char te3_buf[12];
static TextEdit te3;

static CheckBox cb1;
static CheckBox cb2;
static CheckBox cb3;
// ========================================

enum enum_tasks active_task;

void vTaskMgr(void* pvParameters) {
  (void)(pvParameters);

  static char buffer[TASK_MGR_BUFFER_SIZE];

  tm_msg_buf_handle = xMessageBufferCreateStatic(
			  sizeof(msg_buffer),
			  msg_buffer,
			  &msg_buf_struct);

  displayInit(display_buffer);
  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);

  ui_init();

  GSM_Init();

  active_task = enum_task_mgr;
  state = 0;
  menu_size = 3;

  ui_update();
  
  tel_init();

  sd_init();   // init SD memory card
  static uint8_t buf[512];
  sd_read_csd(buf);
  
  sd_read_block_512b(buf, 0);

  addrBook_init();
  
  CHECK(tm_msg_buf_handle);
  for (;;) {
    _log("TM ...");
    size_t msg_size = xMessageBufferReceive(
			  tm_msg_buf_handle, buffer,
			  TASK_MGR_BUFFER_SIZE,
			  portMAX_DELAY);
    if (msg_size > 0) {
      // received message from KBD, GSM or ...
      task_mgr_hook(buffer, msg_size);

      switch(active_task) {
        case enum_task_mgr:
          handle_msg(buffer, msg_size);
          break;

        case enum_task_tel:	  
          xMessageBufferSend(
	      tel_msg_buf_handle, buffer, msg_size,
	      portMAX_DELAY);
          break;

        case enum_task_addr_book:
	  _log("TM: msg for addr book");

	  if (buffer[0] == MSG_HEADER_CALL)
	    handle_msg(buffer, msg_size);
	  else
	    xMessageBufferSend(
		addr_book_msg_buf_handle, buffer, msg_size,
		portMAX_DELAY);
	  break;

        case enum_task_clock:
	  break;

        default:
	  CHECK(0);
	  break;
      }
    }
  } // for(;;)
  //ui_init();
  //ui_update();
}

static void handle_msg(char *buffer, size_t msg_size) {
  switch(buffer[0]) {
  case MSG_HEADER_KBD: {
    if (buffer[1] == 17) {// key up
      menu_up();
      ui_update();
    }

    if (buffer[1] == 9)  // key enter
      menu_enter();

    if (buffer[1] == 26) {// key down
      menu_down();
      ui_update();
    }

    break;
  } // KBD

  case MSG_HEADER_GSM:
    xMessageBufferSend(tel_msg_buf_handle, buffer,
		       msg_size, portMAX_DELAY);
    break;

  case MSG_HEADER_CALL:
    _log("TM MSG_HEADER_CALL");
    active_task = enum_task_tel;
    byte header = MSG_HEADER_TM;
    xMessageBufferSend(tel_msg_buf_handle, &header,
		       1, portMAX_DELAY);

    xMessageBufferSend(tel_msg_buf_handle, buffer,
		       msg_size, portMAX_DELAY);
    
    break;

  } // switch
  
}

void menu_enter(void) {
  switch (state) {
  case 0:
    active_task = enum_task_mgr;
    break;

  case 1: {
    active_task = enum_task_tel;
    byte header = MSG_HEADER_TM;
    xMessageBufferSend(tel_msg_buf_handle, &header,
		       1, portMAX_DELAY);
    break;
  }

  case 2: {
    active_task = enum_task_addr_book;
    byte header = MSG_HEADER_TM;
    xMessageBufferSend(addr_book_msg_buf_handle, &header,
		       1, portMAX_DELAY);
    break;
  }

  default:
    CHECK(0);
    break;
  }
}

inline void menu_down(void) {
  state ++;

  if (state >= menu_size)
    state = 0;
}

inline void menu_up(void) {
  state --;

  if (state < 0)
    state = menu_size - 1;
}
/*static void handle_kbd_msg(buffer + 1, msg_size - 1) {
  char ch;
  if (true == kbd_key_to_char( key, &ch )) {
    // got though menu, and change checkboxes
  }
  ui_update();
  }*/

static void ui_update(void) {
  _log("task mgr  ui_update");
  textEdit_render(&te1, 18, 10, &display);
  textEdit_render(&te2, 18, 40, &display);
  textEdit_render(&te3, 18, 70, &display);

    checkBox_set_value(&cb1, false);
    checkBox_set_value(&cb2, false);
    checkBox_set_value(&cb3, false);
  
  if (state == 0)
    checkBox_set_value(&cb1, true);

  if (state == 1)
    checkBox_set_value(&cb2, true);

  if (state == 2)
    checkBox_set_value(&cb3, true);

  checkBox_render(&cb1, 2, 10, &display);
  checkBox_render(&cb2, 2, 40, &display);
  checkBox_render(&cb3, 2, 70, &display);

  displayFlush();
}

static void ui_init(void) {
  textEdit_init(&te1, te1_buf, 12, nimbus_bold_16);
  textEdit_init(&te2, te2_buf, 12, nimbus_bold_16);
  textEdit_init(&te3, te3_buf, 12, nimbus_bold_16);

  textEdit_maximize(&te1);
  textEdit_maximize(&te2);
  textEdit_maximize(&te3);
  
  //textEdit_setstr(&te1, "������", 6);
  //textEdit_setstr(&te2, "�������", 7);
  textEdit_setcstr(&te1, "tasks");
  textEdit_setcstr(&te2, "telephone");
  textEdit_setcstr(&te3, "address book");
  
  checkBox_set_value(&cb1, true);
}

static void task_mgr_hook(char* buffer, size_t msg_size) {
  (void)(msg_size);
  if (buffer[0] == MSG_HEADER_KBD)
    if (buffer[1] == 19) {
      active_task = enum_task_mgr;
      ui_update();
    }
}
