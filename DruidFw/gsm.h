// gsm.h

#pragma once

#include "global.h"

#define CMD_SET_NUMBERIC_RESPONCE_FORMAT "ATV0"
#define CMD_DISABLE_ECHO "ATE0"
#define CMD_SET_ERROR_LEVEL_1 "AT+CMEE=1"
#define CMD_ENABLE_AON "AT+CLIP=1"
#define CMD_CHECK_NET_STATUS "AT+CREG?"
#define CMD_GET_IMEI "AT+GSN"

extern MessageBufferHandle_t gsm_msg_buf_handle;

void GSM_Init(void);

void gsm_send_cstr(const char* data);
void gsm_send_str(char* data, size_t len);
void gsm_send_cstr_ne(const char* data);
void gsm_send_str_ne(char* data, size_t len);

void gsm_send_cmd_end(void);
bool gsm_status(void);


void GSM_CallCmd(const char* msg);
void SendGsm(const char* msg);
void SendGsmLen(const char* msg, uint8_t len);