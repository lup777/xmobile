// sander_mbr.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

typedef uint32_t __u32;
typedef uint16_t __u16;
typedef int32_t __s32;
typedef int16_t __s16;
typedef uint8_t __u8;

typedef struct ext2_super_block {
  __u32   s_inodes_count;        /*  Количество индексных дескрипторов в ФС */
  __u32   s_blocks_count;        /*  Количество блоков в ФС */
  __u32   s_r_blocks_count;      /*  Количество зарезервированых блоков */
  __u32   s_free_blocks_count;   /*  Количество свободных блоков */
  __u32   s_free_inodes_count;   /*  Количество свободных индексных дескрипторов */
  __u32   s_first_data_block;    /*  Номер данного блока */
  __u32   s_log_block_size;      /*  log2(размер блока)-10 */
  __s32   s_log_frag_size;       /*  log2(размер фрагмента)-10 */
  __u32   s_blocks_per_group;    /*  #  Кол-во блоков в группе */
  __u32   s_frags_per_group;     /*  #  Кол-во фрагментов в группе */
  __u32   s_inodes_per_group;    /*  #  Кол-во индексных дескрипторов в группе */
  __u32   s_mtime;               /*  Время последнего монтирования в POSIX времени */
  __u32   s_wtime;               /*  Время последней записи в POSIX времени */
  __u16   s_mnt_count;
  __s16   s_max_mnt_count;
  __u16   s_errors;              /*  Код ошибки(см.ниже) */
  __u16   s_pad;
  __u32   s_lastcheck;           /*  POSIX время последней проверки */
  __u32   s_checkinterval;       /*  POSIX время между принудительными проверками */
  __u32   s_creator_os;          /*  ID ОС (см. ниже)  */
  __u32   s_rev_level;           /*  Версия */
  __u16   s_def_resuid;          /*  UserID, могущий использовать зар. блоки */
  __u16   s_def_resgid;          /*  GroupID, могущий использовать зар. блоки */
  __u32   s_reserved[235];       /*  Зарезервировано */
} ext2_super_block;

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

typedef struct Mbr {
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

void show_mbr_info(Partition* p);
bool img_read(FILE* fi,long int addr, size_t size, u8* buffer);
void show_super_block_info(ext2_super_block* sb);

//u8 buffer[sizeof(Mbr)];

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
  fi = fopen("/home/alexander/tmp/image.img", "r");

  if (fi == NULL) {
    printf("open failed");
    return 1;
  }

  printf("sizeof MBR 0x%04lX\n", sizeof(Mbr));

  static Mbr mbr;
  img_read(fi, 0x0, sizeof(Mbr), (u8*)(&mbr));

  _log("MBR signature: 0x%04X\n", mbr.mbr_signature);

  _log(" \n PART 1: ");
  show_mbr_info(&(mbr.p1));

  static ext2_super_block sb;

  u16 sector_size = 512;
  u32 super_block_addr = (mbr.p1.abs_start_sector * sector_size) + 0x400;
  img_read(fi, super_block_addr, sizeof(ext2_super_block), (u8*)(&sb));

  show_super_block_info(&sb);

  fclose(fi);
  return 0;
}

bool img_read(FILE* fi,long int addr, size_t size, u8* buffer) {
  int result = fseek(fi, addr, SEEK_SET);
  int i = 0;

  if (result != 0) {
    _log("seek failed");
  }

  while (!feof(fi) && i < size) {
    buffer[i++] = fgetc(fi);
    //printf("0x%02X\n", buffer[i-1]);
  }
  return true;
}

void show_super_block_info(ext2_super_block* sb) {
  printf("s_inodes_count = %d\n", sb->s_inodes_count);
  printf("s_blocks_count = %d\n", sb->s_blocks_count);
  printf("s_free_blocks_count = %d\n", sb->s_free_blocks_count);
  printf("s_first_data_block = %d\n", sb->s_first_data_block);
  printf("s_rev_level = %d\n", sb->s_rev_level);

}

void show_mbr_info(Partition* p) {
  _log("PART is_active: 0x%02X\n", p->is_active);
  _log("PART start_head 0x%02X\n", get_start_head(p));
  _log("PART start_sector 0x%02X\n", get_start_sector(p));
  _log("PART start_cylinder 0x%04X\n", get_start_cylinder(p));
  _log("PART part_type 0x%02X\n", p->part_type);
  _log("PART end_head 0x%02X\n", get_end_head(p));
  _log("PART end_sector 0x%02X\n", get_start_sector(p));
  _log("PART end_cylinder 0x%04X\n", get_start_cylinder(p));
  _log("PART start_abs_sector 0x%02X%02X%02X%02X\n",
       *((u8*)(&p->abs_start_sector) + 3),
       *((u8*)(&p->abs_start_sector) + 2),
       *((u8*)(&p->abs_start_sector) + 1),
       *((u8*)(&p->abs_start_sector)));
  _log("PART sectors_in_part 0x%02X%02X%02X%02X\n\n",
       *((u8*)(&p->sectors_in_part)+3),
       *((u8*)(&p->sectors_in_part)+2),
       *((u8*)(&p->sectors_in_part)+1),
       *((u8*)(&p->sectors_in_part)));

}

// C - 0x100
// H - 0x20
// S - 0x01

// TH - 0xBE
// TS - 0x01

// (C * TH * TS) + (H * TS) + (S - 1) = LBA
// (100 * BE * 1) + (20 * 1) + (1 - 1) = BE00 + 20 = BE20 LBA

// https://thestarman.pcministry.com/asm/mbr/PartTables.htm
