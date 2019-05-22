// task_mgr.c

static void ui_init(void);
static void ui_update(void);

static MlineTextEdit mte;

void vTaskMgr(void* pvParameters) {
  (void)(pvParameters);

  char buffer[TASK_MGR_BUFFER_SIZE];

  displayInit();
  EPD_ShowFullScreenImage(ucDisplayFullLupImage, 200, 200);

  GSM_Init();

  ui_init();

  active_task = task_mgr;

  CHECK(msg_buf_handle);
  for (;;) {
    size_t msg_size = xMessageBufferReceive(msg_buf_handle, buffer,
                                            TASK_MGR_BUFFER_SIZE,
                                            portMAX_DELAY);
    if (msg_size > 0) {
      // received message from KBD, GSM or ...
      switch(active_task) {
        case enum_task_mgr:
          handle_msg(buffer, msg_size);
          break;

        case enum_task_tel:
          xMessageBufferSend(tel_msgbuf_handle, buffer, msg_size, portMAX_DELAY);
          break;
      }
    }
  }
}

void handle_msg(buffer, msg_size) {
  switch(buffer[0]) {
  case MSG_HEADER_KBD:
    handle_kbd_msg(buffer + 1, msg_size - 1);
    break;

  case MSG_HEADER_GSM:
    break;
  }
}

static void handle_kbd_msg(buffer + 1, msg_size - 1) {
  char ch;
  if (true == kbd_key_to_char( key, &ch )) {
    // got though menu, and change checkboxes
  }
  ui_update();
}

static void ui_update(void) {
  mlTextEdit_render(&mte, 10, 10, &display);
}

static void ui_init(void) {

  mlTextEdit_init(&mte, 25, 2); // result will be checked internally

  // CheckBox1
  // CheckBox2
  mlTextEdit_pushcstr(&mte, "task manager");
  mlTextEdit_pushcstr(&mte, "telephone");
}
