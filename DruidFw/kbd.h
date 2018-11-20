// key.h

#ifndef __KEY_H__
#define __KEY_H__

typedef enum EnumKey {
  key1, key2, key3, key4, key5, key6, key7, key8, key9, key0, keyNo
} Key;

void KBD_Init(void);
Key KBD_Check(void);
Key KBD_Read(void);
#endif // __KEY_H__
