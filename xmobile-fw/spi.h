//spi.h
#ifndef __SPI_H__
#define __SPI_H__
#include "global.h"

extern void vSpiSendTask(void* pvParameters);
extern void SpiSendStream(char* msg);

#endif
