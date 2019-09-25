//addr_book.h

#pragma once

#include "global.h"

extern MessageBufferHandle_t addr_book_msg_buf_handle;

void addrBook_task(void* pvParameters);
void addrBook_init(void);

#define NAME_LEN 15
#define NUMBER_LEN 11

struct AB_record {
  char name[NAME_LEN];
  char soname[NAME_LEN];
  char patronymic[NAME_LEN];
  char number[NUMBER_LEN];
};
