// render.h
#pragma once

#include "global.h"

#include <math.h>

void displayInit(void);
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
