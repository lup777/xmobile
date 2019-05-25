// render.h
#pragma once

#include "global.h"

#include <math.h>

#define DISPLAY_BUFFER_COLS_BYTE 25
#define DISPLAY_BUFFER_ROWS_BITS 200
#define DISPLAY_BUFFER_SIZE (DISPLAY_BUFFER_ROWS_BITS * DISPLAY_BUFFER_COLS_BYTE)


typedef struct struct_zone {
  short x_; // coordinates
  short y_; // coordinates
  short ex_; // coordinates
  short ey_; // coordinates
  bool clean;
} Zone;

typedef struct struct_display_buffer {
    uint8_t* buffer;
    short buf_rows;
    short buf_cols;
    size_t buf_size;
    Zone zone;
} DispBuf;

extern DispBuf display;

void displayInit(byte* display_buffer, byte* display_spi_buf);
void displayFlush(void);
void displayRenderDot(short x, short y, DispBuf* display_);
void displayRenderLine(short x, short y, short ex, short ey,
		       DispBuf* display_);
void displayRenderCircle(short x, short y, short r, DispBuf* display_);
void displayRenderRectangle(short x, short y, short x1, short y1,
			    DispBuf* display_);
void displayRenderSubBuffer(short tar_x, short tar_y,
			    DispBuf* sub_disp_, DispBuf* display_);
void displayRenderText(short x, short y,
		       char* text, size_t len,
		       DispBuf* display_);
void zoneUpdate(short x, short y, DispBuf* display_);
void zoneClear(void);
word zoneX(void);
word zoneY(void);
word zoneEx(void);
word zoneEy(void);
