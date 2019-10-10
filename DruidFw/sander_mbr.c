// sander_mbr.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "fs.h"


void show_mbr_info(Partition* p);
bool img_read(long int addr, size_t size, u8* buffer);
void show_super_block_info(ext2_super_block* sb);
bool read_mbr(u8* buffer);

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

static u8 buffer[1024];

static FILE* fi;

int main(void) {
  fi = fopen("image.img", "r");

  if (fi == NULL) {
    printf("open failed");
    return 1;
  }

  printf("sizeof MBR 0x%04lX\n", sizeof(Mbr));

  read_mbr(buffer);
  _log("MBR signature: 0x%04X\n", ((Mbr*)buffer)->mbr_signature);
  _log(" \n PART 1: ");
  show_mbr_info(&(((Mbr*)buffer)->p1));

  Mbr* mbr = (Mbr*)buffer;
    
  u32 part_start_addr = (mbr->p1.abs_start_sector + 1) * SECTOR_SIZE;
  _log("part_start_addr = %d", part_start_addr);
  
  u32 super_block_addr =
    ((mbr->p1.abs_start_sector + 2) * SECTOR_SIZE);
  _log("super block addr: 0x%04X\n", super_block_addr);

  img_read(super_block_addr, sizeof(ext2_super_block), buffer);

  static ext2_super_block* sb = (ext2_super_block*)buffer;
  show_super_block_info(sb);
  
  u32 block_groups_number = sb->s_blocks_count
    / sb->s_blocks_per_group;
  printf("block_groups_number = %d\n", block_groups_number);


  //which block group contains first non reserved inode
  u32 block_group = (FIRST_NON_RESERVERD_INOD - 1)
    / sb->s_inodes_per_group;
  printf("block_group = %d\n", block_group);

  printf("s_blocks_per_group = %d\n", sb->s_blocks_per_group);

  // inode index in block group
  u32 index = (FIRST_NON_RESERVERD_INOD - 1)
    % sb->s_inodes_per_group;
  printf("inode index = %d\n", index);

  // which block contains our inode
  u32 containing_block = (index * INODE_SIZE) /
    (1024 << sb->s_log_block_size);
  printf("containing_block = %d\n", containing_block);

  
  u32 inode_addr = part_start_addr
    + (containing_block * (1024 << sb->s_log_block_size))
    + ((index + 1) * INODE_SIZE);

  printf("inode_addr = 0x%08X\n", inode_addr);

  for (u8 i = 0; i < 16; i++) {
    if (img_read(inode_addr + (i * INODE_SIZE),
		 INODE_SIZE,
		 buffer)) {
      _log("INODE %d\n", i + index);
      
      for (u8 j = 0; j < INODE_SIZE / 8; j+=8) {
	_log("%02X %02X %02X %02X %02X %02X %02X %02X\n",
	     buffer[j+0], buffer[j+1], buffer[j+2], buffer[j+3],
	     buffer[j+4], buffer[j+5], buffer[j+6], buffer[j+7]);
      }
      ext2_inode* in = (ext2_inode*)buffer;
      printf("in->i_mode = 0x%02X\n", in->i_mode);
    }
  }

  // https://wiki.osdev.org/Ext2
  
  
  fclose(fi);
  return 0;
}

bool read_mbr(u8* buffer) {
  return img_read(0, 512, buffer);
}

bool img_read(long int addr, size_t size, u8* buffer) {
  int result = fseek(fi, addr, SEEK_SET);
  int i = 0;

  if (result != 0) {
    _log("seek failed");
  }

  while (!feof(fi) && i < size) {
    buffer[i++] = fgetc(fi);
    //printf("0x%02X\n", buffer[i-1]);
  }
}

void show_super_block_info(ext2_super_block* sb) {
  printf("s_inodes_count = %d\n", sb->s_inodes_count);
  printf("s_blocks_count = %d\n", sb->s_blocks_count);
  printf("s_free_blocks_count = %d\n", sb->s_free_blocks_count);
  printf("s_first_data_block = %d\n", sb->s_first_data_block);
  printf("s_rev_level = %d\n", sb->s_rev_level);
  printf("s_log_block_size = %d\n", 1024 << sb->s_log_block_size);
  printf("s_log_frag_size = %d\n", 1024 << sb->s_log_frag_size);
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
