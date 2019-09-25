// telephone.h

#pragma once

#include "global.h"

extern MessageBufferHandle_t tel_msg_buf_handle;

void vTelTask(void* pvParameters);
void tel_init(void);
