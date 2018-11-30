// key.h
#pragma once

#include <avr/io.h>

typedef enum EnumKey {
  key0, key1, key2, key3, key4, key5, key6, key7, key8, key9, key10, key11,
  key12, key13, key14, key15, keyNo, keyClose
} Key;

void KBD_Init(void);
Key KBD_Check(void);
uint16_t KBD_Read(void);
Key KBD_WaiteKey(void);
