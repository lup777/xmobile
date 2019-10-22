// sander_mbr.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define _log printf

#pragma pack(push,1)
typedef struct Partition {
  u8 is_active; // 00h
  u8 start_chs[3]; // head, sector and cylinder 01h..03h
  u8 part_type; // 04h
  u8 end_chs[3]; // end head, sector, cylinder 05h ..07h
  u32 abs_start_sector; // 08h..0Bh (LBA)
  u32 sectors_in_part; // 0Ch..0Fh (num of sectors in part LBA)
} Partition;

struct Mbr {
  u8 code[139];        // 0000..008A
  u8 err_msgs[80];     // 008B..00DA
  u8 padding[227];     // 00DB..01BD    zeros (or NT drive serial number)
  union {
    u8 part_table[64];   // 01BE..01FD
    struct {
      struct Partition p1;
      struct Partition p2;
      struct Partition p3;
      struct Partition p4;
    };
  };
  u16 mbr_signature; // 01FE..01FF    0xAA55h [55, AA]
} Mbr;
#pragma pack(pop)

u8 buffer[sizeof(Mbr)];

u8 get_start_head(Partition* p) {
  return p->start_chs[0];
}

u16 get_start_cylinder(Partition* p) {
  return ((((u16)p->start_chs[1]) && 0x0003) << 8) | (u16)(p->start_chs[2]);
}

u8 get_start_sector(Partition* p) {
  return (p->start_chs[1] >> 2) && 0x3F;
}

u8 get_end_head(Partition* p) {
  return p->end_chs[0];
}

u16 get_end_cylinder(Partition* p) {
  return ((((u16)p->end_chs[1]) && 0x0003) << 8) | (u16)(p->start_chs[2]);
}

u8 get_end_sector(Partition* p) {
  return (p->end_chs[1] >> 2) && 0x3F;
}

int main(void) {
  FILE* fi;
  fi = fopen("sdb.img", "r");

  if (fi == NULL) {
    printf("open failed");
    return 1;
  }

  printf("sizeof MBR 0x%04lX\n", sizeof(Mbr));

  u16 i = 0;
  while (!feof(fi) && i < sizeof(Mbr)) {
    buffer[i++] = fgetc(fi);
    //printf("0x%02X\n", buffer[i-1]);
  }

  struct Mbr* pmbr = (struct Mbr*)buffer;

  _log("MBR signature: 0x%04X\n", pmbr->mbr_signature);
  _log("PART1 is_active: 0x%02X\n", pmbr->p1.is_active);
  _log("PART1 start_head 0x%02X\n", get_start_head(&(pmbr->p1)));
  _log("PART1 start_sector 0x%02X\n", get_start_sector(&(pmbr->p1)));
  _log("PART1 start_cylinder 0x%04X\n", get_start_cylinder(&(pmbr->p1)));
  _log("PART1 part_type 0x%02X\n", pmbr->p1.part_type);
  _log("PART1 end_head 0x%02X\n", get_end_head(&(pmbr->p1)));
  _log("PART1 end_sector 0x%02X\n", get_start_sector(&(pmbr->p1)));
  _log("PART1 end_cylinder 0x%04X\n", get_start_cylinder(&(pmbr->p1)));
  _log("PART1 start_abs_sector 0x%02X%02X%02X%02X\n",
       *((u8*)(&pmbr->p1.abs_start_sector) + 3),
       *((u8*)(&pmbr->p1.abs_start_sector) + 2),
       *((u8*)(&pmbr->p1.abs_start_sector) + 1),
       *((u8*)(&pmbr->p1.abs_start_sector)));
  _log("PART4 sectors_in_part 0x%02X%02X%02X%02X\n\n",
       *((u8*)(&pmbr->p1.sectors_in_part)+3),
       *((u8*)(&pmbr->p1.sectors_in_part)+2),
       *((u8*)(&pmbr->p1.sectors_in_part)+1),
       *((u8*)(&pmbr->p1.sectors_in_part)));

  fclose(fi);
  return 0;
}

// https://thestarman.pcministry.com/asm/mbr/PartTables.htm
