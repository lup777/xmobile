//task_mgr.h

#pragma once

#include "global.h"

extern MessageBufferHandle_t tm_msg_buf_handle;
void vTaskMgr(void* pvParameters);
