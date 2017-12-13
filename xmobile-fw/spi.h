//spi.h
#ifndef __SPI_H__
#define __SPI_H__
#include "global.h"

extern void vSpiSendTask(void* pvParameters);
extern void vSpiSendStream(const unsigned char* msg, size_t len);
extern void vSpiSendStreamByte(unsigned char byte);

#endif
