// task_mgr.c

#include "task_mgr.h"
#include "render.h"
#include "pgm.h"
#include "epd.h"
#include "gsm.h"
#include "text_edit.h"
#include "check_box.h"
#include "telephone.h"

static void ui_init(void);
static void ui_update(void);
static void handle_msg(char *buffer, size_t msg_size);
inline void menu_down(void);
inline void menu_up(void);
static void task_mgr_hook(char* buffer, size_t msg_size);

int8_t state;
byte menu_size;
// ===== TASK MANAGER MessageBuffer data ===========
MessageBufferHandle_t tm_msg_buf_handle;
StaticStreamBuffer_t msg_buf_struct;
static uint8_t msg_buffer[ 50 ];
// ========================================

// ===== DISPLAY DATA =====================
byte display_buffer[DISPLAY_BUFFER_SIZE];
byte dispay_spi_buf[DISPLAY_BUFFER_ROWS_BITS];
// ========================================

// ======== UI ============================
static char te1_buf[12];
static TextEdit te1;

static char te2_buf[12];
static TextEdit te2;

static CheckBox cb1;
static CheckBox cb2;
// ========================================

enum enum_tasks active_task;


void vTaskMgr(void* pvParameters) {
  (void)(pvParameters);

  static char buffer[TASK_MGR_BUFFER_SIZE];

  tm_msg_buf_handle = xMessageBufferCreateStatic(sizeof(msg_buffer),
						 msg_buffer,
						 &msg_buf_struct);
  displayInit(display_buffer, dispay_spi_buf);
  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);

  ui_init();

  GSM_Init();

  ui_update();

  active_task = enum_task_tel;//enum_task_mgr;
  state = 0;
  menu_size = 2;
  
  CHECK(tm_msg_buf_handle);
  for (;;) {
    size_t msg_size = xMessageBufferReceive(tm_msg_buf_handle, buffer,
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
          xMessageBufferSend(tel_msg_buf_handle, buffer, msg_size, portMAX_DELAY);
          break;

        case enum_task_clock:
	        break;

        default:
	      CHECK(0);
	      break;
      }
    }
  }
  ui_init();
  ui_update();
}

static void handle_msg(char *buffer, size_t msg_size) {
  switch(buffer[0]) {
  case MSG_HEADER_KBD: {
    if (buffer[1] == 17) // key up
      menu_up();

    if (buffer[1] == 9) { // key enter
      switch (state) {
      case 0:
        active_task = enum_task_mgr; break;
      case 1:
	active_task = enum_task_tel; break;
	buffer[0] = MSG_HEADER_TM;
	xMessageBufferSend(tel_msg_buf_handle, buffer, 1, portMAX_DELAY);
      default:
	CHECK(0);
	break;
      }
    }

    if (buffer[1] == 26) // key down
      menu_down();
    ui_update();
    //_log("KBD: 0x%02X", buffer[1]);

    break;
  } // KBD

  case MSG_HEADER_GSM:
    xMessageBufferSend(tel_msg_buf_handle, buffer, msg_size, portMAX_DELAY);
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
  textEdit_render(&te1, 18, 10, &display);
  textEdit_render(&te2, 18, 40, &display);

  if (state == 0) {
    checkBox_set_value(&cb1, true);
    checkBox_set_value(&cb2, false);
  }

  if (state == 1) {
    checkBox_set_value(&cb1, false);
    checkBox_set_value(&cb2, true);
  }
  
  checkBox_render(&cb1, 2, 10, &display);
  checkBox_render(&cb2, 2, 40, &display);
    
  displayFlush();
}

static void ui_init(void) {
  textEdit_init(&te1, te1_buf, 12);
  textEdit_init(&te2, te2_buf, 12);

  textEdit_setcstr(&te1, "task manager");
  textEdit_setcstr(&te2, "telephone");

  checkBox_set_value(&cb1, true);
}

static void task_mgr_hook(char* buffer, size_t msg_size) {
  (void)(msg_size);
  if (buffer[0] == MSG_HEADER_KBD)
    if (buffer[1] == 19)
      active_task = enum_task_mgr;
}
