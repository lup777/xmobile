// menu.h

#pragma once

typedef unsigned char u8;
typedef signed short i8;

#ifndef SANDER
#  include "global.h"
#else
#  include "sander.h"
#  endif

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct String {
  char* str;
  size_t len;
} String;

typedef String (*GetTextFptr)(u8 max_len, i8);
typedef void (*EnterFptr)(i8 entry_num);

typedef String (*GetTextFptr)(u8 max_len, i8);
typedef void (*EnterFptr)(i8 entry_num);

typedef struct Menu {
  char *buffer;
  size_t buffer_len;
  GetTextFptr get_text;
  EnterFptr enter;
  u8 lines_num;
  u8 line_len;
  u8 selected;
  u8 start_line;
} Menu;

/*
 * __LINES_NUM__ nomber of lines
 * __LINES_LEN__ len of lines
 * __MENU_HANDLE__ menu handle name
 */
#define MENU(__LINES_NUM__, __LINES_LEN__, __MENU_HANDLE__, __ENTER_CALLBACK__) \
  static char menu_buffer[__LINES_NUM__ * __LINES_LEN__];               \
  static Menu __MENU_HANDLE__ = {                                       \
    .buffer = menu_buffer,                                              \
    .buffer_len = __LINES_NUM__ * __LINES_LEN__,                        \
    .lines_num = __LINES_NUM__,                                         \
    .line_len = __LINES_LEN__,                                          \
    .enter = __ENTER_CALLBACK__                                         \
};
/* TODO
 *  ADD UI elements in MENU macro
*/

void menu_init(Menu* pmenu, GetTextFptr get_text_fptr);
void menu_show(Menu* pmenu);
void menu_prev(Menu* pmenu);
void menu_next(Menu* pmenu);
void menu_enter(Menu* pmenu);
