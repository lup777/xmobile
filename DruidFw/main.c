// main.c

#include "global.h"

#include <stdio.h>
#include <string.h>
#include "epd.h"
#include "pgm.h"
#include "kbd2.h"
//#include "telephone.h"
#include "gsm.h"
#include "menu.h"
#include "render.h"
#include "core_drv.h"

// local functions
static void vMainTask(void* pvParameters);
static void TestApp1(void* pvParameters);

void _sleep(uint16_t time_ms);
void check_endian(void);
// ~ local functions

// GLOBAL VARIABLES
Context context;

/*static App menu[MENU_SIZE] = {
  {TestApp1, NOT_EXISTS_ID,                   "telephone      "},
  {TestApp1, NOT_EXISTS_ID,                   "calendar       "},
  {TestApp1, NOT_EXISTS_ID,                   "reader         "},
  {TestApp1, NOT_EXISTS_ID,                   "snake          "},
  {TestApp1, NOT_EXISTS_ID,                   "music player   "}
  };*/

MessageBufferHandle_t kbd_rx_buf;
MessageBufferHandle_t gsm_rx_buf;
// ~GLOBAL VARIABLES~

int main(void) {
  kbd_rx_buf = xMessageBufferCreate( KBD_RX_BUFFER_SIZE );
  gsm_rx_buf = xMessageBufferCreate( 50 );

  {  // init modules (order is significant)
    clk_init();  // set sys clock to internal 32 MGz
    sram_init(); // configure external SRAM
    log_init();  // configure debug USART
    kbd_init();  // configure keyboard MAX7370 I2C
    int_init();  // enable ints and clear int flags
  }

  context.active_app_id = MENU_MAILBOX_ID;

  for (uint8_t i = 0; i < MAILBOX_SIZE; i++)
    context.mail[i] = NULL;

  xTaskCreate( vMainTask,
               "main_task",
               configMINIMAL_STACK_SIZE,
               NULL,
               1,
               NULL );

  xTaskCreate( TestApp1,
               "test task",
               configMINIMAL_STACK_SIZE,
               NULL,
               1,
               NULL );


  vTaskStartScheduler();

  return 0;
}

static void TestApp1(void* pvParameters) {
  (void)(pvParameters);
  _sleep(20000);
  _log("TestApp1");
  for(;;) {
    //gsm_get_signal_quality();
    _sleep(3000);
    //send_str("AT+CRSL=15\n\r", 12);
    _sleep(3000);
  }
}

static void vMainTask(void* pvParameters) {
  (void)(pvParameters);

  check_endian();

  displayInit();

  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);

  GSM_Init();
  _log("MAIN main task init completed");

  //APP_TelephoneStart();
  //APP_MenuStart(menu);

#define line_num 10
  struct LineDate {
    char line[25];
    byte len;
  } lines[line_num];

  struct TextField12 {
    char text[12];
    byte len;
    byte index;
  } phone_number;

  size_t i = 0;
  
  for (i = 0; i < line_num; i++) {
    lines[i].len = 0;
  }
  phone_number.len = 12;
  phone_number.index = 0;
  bool need_update_display = false;
  
  for(;;) {
    char key;
    
    char gsm_char[25];
    
    size_t kbd_rx_bytes = xMessageBufferReceive(kbd_rx_buf, &key, 1, 0);
    size_t gsm_rx_bytes = xMessageBufferReceive(gsm_rx_buf,
						gsm_char,
						25, 0);

    if (kbd_rx_bytes > 0) {
      //_log("KBD: 0x%02X", key);

      if (key == 0x02) { // loud connection
	send_cstr("AT+SNFS=1\n\r");
      }
      
      else if (key == 0x1B) { // get signal quality
	gsm_get_signal_quality();
      }
      
      else if (key == 0x1D) { // set ring volume
	send_cstr("AT+CRSL=15\n\r");
      }

      else if (key == 0x18) {//responce the call
	send_cstr("ATA\n\r");
      }

      else if (key == 17) { // call 
	send_cstr("ATD+");
	send_str(phone_number.text, phone_number.index);
	send_cstr(";\r\n");
      }

      else {
	_log("KBD: 0x%02X", key);

	switch(key) {
	case 13: phone_number.text[phone_number.index] = '1';
	  phone_number.index ++;
	  break;
	case 18: phone_number.text[phone_number.index] = '2';
	  phone_number.index ++;
	  break;
	case 25: phone_number.text[phone_number.index] = '3';
	  phone_number.index ++;
	  break;
	case  1: phone_number.text[phone_number.index] = '4';
	  phone_number.index ++;
	  break;
	case  5: phone_number.text[phone_number.index] = '5';
	  phone_number.index ++;
	  break;
	case  3: phone_number.text[phone_number.index] = '6';
	  phone_number.index ++;
	  break;
	case 21: phone_number.text[phone_number.index] = '7';
	  phone_number.index ++;
	  break;
	case 11: phone_number.text[phone_number.index] = '8';
	  phone_number.index ++;
	  break;
	case  0: phone_number.text[phone_number.index] = '9';
	  phone_number.index ++;
	  break;
	case  8: phone_number.text[phone_number.index] = '*';
	  phone_number.index ++;
	  break;
	case  10: phone_number.text[phone_number.index] = '0';
	  phone_number.index ++;
	  break;
	case  16: phone_number.text[phone_number.index] = '#';
	  phone_number.index ++;
	  break;	  
	}
	if (phone_number.index >= phone_number.len) {
	  phone_number.index = 0;
	}
	need_update_display = true;
      } 
    }

    if (gsm_rx_bytes > 0) {
      
      for (i = 1; i < line_num; i++) {
	memcpy(&(lines[i - 1]), &(lines[i]), 25);
	lines[i - 1].len = lines[i].len;
      }
      memcpy(lines[line_num - 1].line, gsm_char, gsm_rx_bytes);
      lines[line_num - 1].len = gsm_rx_bytes;
      
      //_log("GSM: %c  (0x%02X)", gsm_char, gsm_char);
      logcl("GSM: ");

      for(i = 0; i < gsm_rx_bytes; i++) {
	logc(gsm_char[i]);
      }
      logcl("\n\r");

      need_update_display = true;
    }


    // update display
    if (need_update_display) {
      need_update_display = false;
      displayRenderText(8, 10, "gsm:", 4, &display);
      for (i = 0; i < line_num; i++) {

	char* str = lines[i].line;
	byte len = lines[i].len;
	
	displayRenderText(8, 24 + (i * 14), str, len, &display);	
      }

      displayRenderText(3, 185, "call: +", 7, &display);
      displayRenderText(60, 185, phone_number.text, phone_number.index, &display);
      displayRenderRectangle(2, 180, 150, 197, &display);
      displayFlush();
    }
    // ~update display

    //APP_MenuMessagePump();
  }
  //APP_MenuStart(menu);
  //APP_MenuMessagePump();
}

void SendAppMsg(uint8_t msg_id, char* payload, uint8_t payload_len,
                uint8_t mailbox_id) {
  char buf[10];
  if (payload_len > 10 + 1) {
    _log("ERR SendAppMsg: too log msg");
    return;
  }

  if (context.mail[mailbox_id] == NULL) {
    _log("ERR SendAppMsg: mailbox id == NULL");
    return;
  }

  buf[0] = msg_id;
  if (payload)
    for (int i = 0; i < payload_len; i++)
      buf[i + 1] = payload[i]; // copy payload

  size_t xBytesSent;

  taskENTER_CRITICAL();
  //_log("send to %p", context.mail[mailbox_id]);
  xBytesSent = xMessageBufferSend(context.mail[mailbox_id], buf,
                                  (size_t)payload_len + 1, 0);
  taskEXIT_CRITICAL();

  if (xBytesSent != (size_t)payload_len + 1) {
    _log("ERR SendAppMsg");
  }
}

void _sleep(uint16_t time_ms) {
  vTaskDelay((TickType_t)(time_ms / portTICK_PERIOD_MS));
}

inline void check_endian(void) {
  union {
    uint16_t d;
    uint8_t a[2];
  } t;

  t.d = 1;
  if (t.a[0])
    _log("little endian");
  else
    _log("big endian");
}
