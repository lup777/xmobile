//gsm.h
#ifndef __GSM_H__
#define __GSM_H__

#include "global.h"

extern void vGsmSendTextModeSms(char* phoneNumber, char* text);
//extern void vGsmSendPduModeSms(char* phoneNumber, char* text);
extern void vGsmUart1Init(uint32_t speed);
  
extern void vGsmSendString(char* str);
extern void vGsmModuleInit(void);
  
#endif
