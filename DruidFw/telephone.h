// telephone.h

#pragma once

#include "global.h"

extern MessageBufferHandle_t tel_msg_buf_handle;

void vTelTask(void* pvParameters);


void configure_usart(void);
void enable_hands_free(void);
void change_side_tone_gain_lvl(void);
void get_signal_quality(void);

bool is_cmd_rdy(void);
bool is_cmd_ok(void);
bool is_cmd_error(void);