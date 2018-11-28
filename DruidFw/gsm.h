// gsm.h

#pragma once

#include "global.h"

#define CMD_SET_NUMBERIC_RESPONCE_FORMAT "ATV0"
#define CMD_DISABLE_ECHO "ATE0"
#define CMD_SET_ERROR_LEVEL_1 "AT+CMEE=1"
#define CMD_ENABLE_AON "AT+CLIP=1"

void GSM_Init(void);
