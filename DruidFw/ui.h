//ui.h
#ifndef __UI_H__
#define __UI_H__

#include "kbd.h"
#include "pgm.h"

void vUITask(void* pvParameters);
void UI_SetKey(Key key);
Key UI_GetKey(void);


#endif // __UI_H__
