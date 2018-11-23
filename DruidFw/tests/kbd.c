// kbd.c
#include <stdint.h>
#include <stdio.h>
typedef enum EnumKey {
  key0, key1, key2, key3, key4, key5, key6, key7, key8, key9, key10, key11,
  key12, key13, key14, key15, keyNo
} Key;

#define MAX 13
uint16_t test_data[] = {
  0, (1 << 1), 0, (1 << 4), (1 << 4), (1 << 4), (1 << 5), 0,
  (1 << 5), 0, (1 << 9), (1 << 8), 0
};

uint16_t g_key_map = 0;

uint16_t KBD_Read() {
  static int i = 0;

  return test_data[i++];
}

Key KBD_Check(void) { // only 1 key at one time
  uint8_t i = (uint8_t)keyNo;
  uint16_t map = KBD_Read();

  printf("map = %02X, g_key_map = %02X", map, g_key_map);
  if (map == 0 && g_key_map != 0) { // some key was released
    printf(" - ");
    for (i = 0; i < 16; i++) {
      if (g_key_map & (uint16_t)(1 << i)) {
        printf("[%d]", i);
        break; // [i] key released
      }
    }
    g_key_map = 0; // clear last key map
  } else if (map != 0) {
    g_key_map = map;
  }

  return (Key)i;
}

int main(void) {
  int i = 0;
  printf("keyNo = %d\n", keyNo);
  for (i = 0; i < sizeof(test_data) / sizeof(uint16_t); i++) {
    printf("    KBD_Check -> %d\n", KBD_Check());
  }
  return 0;
}
