// ext2.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "ext2.h"
#include "ext2.proto.h"

#ifndef SANDER
#  include "global.h"
#  include "sd.h"
#  include "usart.h"
#endif

#define MBR_SECTOR 0
#define PART_START_BLOCK (part_start_addr / block_size)
#define SUPER_BLOCK_NUM (PART_START_BLOCK + 1)
#define GROUP_DESCR_TABLE_BLOCK (SUPER_BLOCK_NUM + 1)
#define ROOT_INODE 2
#define ROOT_GROUP 0

static u32 part_start_addr = 0;
static u16 block_size = 1024;
static u32 blocks_per_group = 0;
static u32 inodes_per_group = 0;
//static u32 inode_table_block = 0;
static u8 buffer[1024]; // block size
static ext2_inode iroot;

#ifdef SANDER
FILE* fi;

#define _log printf
#define CHECK {}
#endif

void show_hex(u8* buffer_, long int display_offset, u32 start, u32 num) {
  for (u32 i = start; i < start + num; i+=16 ) {
    _log ("%08lX: %02X %02X %02X %02X  %02X %02X %02X %02X  %02X %02X %02X %02X  %02X %02X %02X %02X \n",
          display_offset + i,
          buffer_[i + 0], buffer_[i + 1], buffer_[i + 2], buffer_[i + 3],
          buffer_[i + 4], buffer_[i + 5], buffer_[i + 6], buffer_[i + 7],
          buffer_[i + 8], buffer_[i + 9], buffer_[i + 10], buffer_[i + 11],
          buffer_[i + 12], buffer_[i + 13], buffer_[i + 14], buffer_[i + 15]);
  }
}

bool read_sector(u32 sector_num) {
#ifndef SANDER
  if (sd_read_block_512b(buffer, sector_num * SECTOR_SIZE))
#else
  if (read_image(&fi, buffer, sector_num * SECTOR_SIZE, SECTOR_SIZE))
#endif
    return true;

  _log("read_sector: failed 0x%04x%04x",
       (u16)sector_num, (u16)(sector_num >> 16));
  return false;
}

bool read_block(u32 block_num) { // block num related to partition start
  /*if (read_image(block_num * block_size, block_size))
    return true;*/
  uint8_t steps = block_size / SECTOR_SIZE;
  u32 addr = block_num * block_size;

  for (u8 i = 0; i < steps; i++, addr += SECTOR_SIZE) {
#ifndef SANDER
    if (!sd_read_block_512b(buffer, addr))
#else
    if (!read_image(&fi, buffer + (i * SECTOR_SIZE), addr, SECTOR_SIZE))
#endif
    {
      _log("read_block: failed 0x%04X%04X", (u16)block_num,
           (u16)(block_num >> 16));
      return false;
    }

  } // for
  show_hex(buffer, addr - 512, 0, 512);
  return true;
}

void parse_mbr(void) {
  Mbr* mbr = (Mbr*)buffer;

  part_start_addr = mbr->p1.abs_start_sector * SECTOR_SIZE;
}

void parse_super_block(void) {
  static ext2_super_block* sb = (ext2_super_block*)buffer;

  if (sb->s_magic != 0xef53) {
    _log("ERROR: wrong Super Block signature\n");
    //show_hex(buffer, 0x0,0, 512);
  }


  block_size = 1024 << sb->s_log_block_size;
  blocks_per_group = sb->s_blocks_per_group;
  inodes_per_group = sb->s_inodes_per_group;

  _log("----------------- super block info ----------------------\n");
  _log("blk size: %d | blocks_per_group %d | inodes_per_group %d\n",
       block_size, blocks_per_group, inodes_per_group);
  _log("---------------------------------------------------------\n");
}

/*void parse_grp_descr_table(void) {
  ext2_group_desc_table* gt = (ext2_group_desc_table*)buffer;
  _log("----------------- grp descr table info ----------------------\n");
  inode_table_block = gt->bg_inode_table;
  _log("inode table block = %d\n", inode_table_block);
  _log("-------------------------------------------------------------\n");
  }*/

u32 get_inode_table_block_for_group(u32 group) {
  //_log("get_inode_table_block_for_group (%d)>>>\n", group);
  if (group * sizeof(ext2_group_desc_table) > block_size) {
    _log("get_inode_table_block_for_group: invalid group\n");
    return 0;
  }
  // read group descriptor table
  read_block(GROUP_DESCR_TABLE_BLOCK);

  ext2_group_desc_table* gt = (ext2_group_desc_table*)buffer;

  gt += group;
  /*_log("get_inode_table_block_for_group: bg_block_bitmap = %d\n",
       gt->bg_block_bitmap);
  _log("get_inode_table_block_for_group: bg_inode_bitmap = %d\n",
       gt->bg_inode_bitmap);
  _log("get_inode_table_block_for_group: g_inode_table  = %d\n",
       gt->bg_inode_table);*/

  return gt->bg_inode_table;
}

bool is_dir(ext2_inode* pinode) {
  return (pinode->i_mode & 0x4000) != 0;
}

void show_inode(ext2_inode* inode) {
  _log("-------------- inode -------------\n");
  _log("i_mode 0x%04X | size 0x%08X | blocks %d\n",
       inode->i_mode, inode->i_size, inode->i_blocks);
  if (is_dir(inode))
    _log("directory\n");
  else
    _log("file\n");
  for (u8 i = 0; i < 15; i++) {
    _log("i_block[%d] = %d\n", i, inode->i_block[i]);
  }
  _log("----------------------------------\n");
}

bool read_inode(ext2_inode* pinode, u32 inode_num) {
  _log("read_inode >>> ");
  if (inodes_per_group == 0) {
    _log("inodes_per_group == 0 !! failed\n");
    return false;
  }
  u16 group = (inode_num - 1) / inodes_per_group;
  u16 inode = (inode_num - 1) - (group * inodes_per_group);

  _log("| group: %d | ", group);
  _log("inode: %4d | \n", inode);
  u32 inode_table_block = get_inode_table_block_for_group(group);

  u8 inodes_per_block = block_size / INODE_SIZE;
  u16 inode_table_block_offset = inode / inodes_per_block;
  inode -= (inode_table_block_offset * inodes_per_block);

  // read inode table
  u32 block = inode_table_block + PART_START_BLOCK +
                                  inode_table_block_offset;
  _log("               read_inode: inode table block %d | \n",
       block);

  if (true != read_block(block))
    return false;

  ext2_inode* source = (ext2_inode*)buffer;
  source += inode;

  memcpy(pinode, source, sizeof(ext2_inode));
  return true;
}

bool get_directory_entry(ext2_inode* pinode, u32 entry_num,
                         ext2_dir_entry* pentry_out) {
  //_log("get_directory_entry >>>\n");

#if 1
  static u8 local_buf[1024];
  ext2_dir_entry* pentry = (ext2_dir_entry*)local_buf;
  memcpy(local_buf, buffer, 1024);
#else
  ext2_dir_entry* pentry = (ext2_dir_entry*)buffer;
#endif

  for (u8 iblock_id = 0; iblock_id < 12; iblock_id++) { // direct block pointers
    if (pinode->i_block[iblock_id] == 0) {
      _log("error. inode i_block = 0; return");
      return false;
    }

    // why -2?
    if (!read_block(pinode->i_block[iblock_id] + PART_START_BLOCK))
      return false;

    u32 offset = 0;

    for (u32 i = 0; offset < block_size; i++, offset += pentry->entry_size) {
      pentry = (ext2_dir_entry*)(buffer + offset);
      //_log("entry: %s\n", pentry->name);
      if (i == entry_num) {
        //_log("found entry: %s\n", pentry->name);
        memcpy(pentry_out, pentry, sizeof(ext2_dir_entry));
        return true;
      }
    } // for offset
  } // for iblock_id
  return false;
}

u32 umin(u32 first, u32 second) {
  if(first < second)
    return first;
  return second;
}



bool get_inode_child_by_name(ext2_inode* parent, char* name,
                             u8 len, ext2_dir_entry* entry_out) {
  //_log("get_inode_child_by_name >>> ");
  //send_log_str(name, len);
  static ext2_dir_entry entry;
  u16 i = 0;

  while(get_directory_entry(parent, i++, &entry) == true) {
    //_log("entry: "); send_log_str(entry.name, entry.name_len); _log("\n");
    if (0 == memcmp(name, entry.name,
                    umin(entry.name_len, len))) {
      memcpy(entry_out, &entry, sizeof(ext2_dir_entry));
      /*_log(" -- found! | ");
      _log("entry name: | "); send_log_str(entry.name, entry.name_len);
      _log(" | entry inode: %d | ", entry.inode);
      _log("entry entry size: %d |\n", entry.entry_size);*/
      return true;
    }
  }
  _log("-- %s not found\n", name);
  return false;
}

bool get_inode_child_by_cname(ext2_inode* parent, const char* name,
                              ext2_dir_entry* entry_out) {
  return get_inode_child_by_name(parent, (char*)name, strlen(name), entry_out);
}

bool get_entry_child_by_name(ext2_dir_entry* in_out, char* name, u8 name_len) {
  _log("get_entry_child_by_name >>> ");
  send_log_str(name, name_len); _log("\n");
  static ext2_inode inode; // TODO: use buffer for this

  _log("### inode %d\n", in_out->inode);
  if(true != read_inode(&inode, in_out->inode)) {
    _log("get_entry_child_by_name: ");
    send_log_str(name, name_len);
    _log(" read_inode failed\n");
    return false;
  }

  //show_inode(&inode);

  if (true != is_dir(&inode)) {
    _log("it is not directory\n");
    return false;
  }
  return get_inode_child_by_name(&inode, name, name_len, in_out);
}

bool get_entry_child_by_cname(ext2_dir_entry* in_out, const char* name) {
  return get_entry_child_by_name(in_out, (char*)name, strlen(name));
}

inode_type get_inode_type(ext2_inode* e) {
  if (e->i_mode & idirectory) return idirectory;
  if (e->i_mode & ifile) return ifile;
  if (e->i_mode & isymbolic_link) return isymbolic_link;

  if (e->i_mode & ififo) return ififo;
  if (e->i_mode & icharacter_device) return icharacter_device;
  if (e->i_mode & iblock_device) return iblock_device;
  if (e->i_mode & iunix_socket) return iunix_socket;

  return iunkown;
}

entry_type get_entry_type(ext2_dir_entry* e) {
  if (e->enum_type <= esymbolic_link)
    return (entry_type)e->enum_type;

  return eunknown;
}

void show_dir_entry(ext2_dir_entry* e) {
  //_log("show_dir_entry >>>\n");
  static ext2_inode inode;  // TODO: use buffer for this
  read_inode(&inode, e->inode);

  _log("-------- dir entry ---------------\n");
  _log("name: ");
  send_log_str(e->name, e->name_len);
  _log(" | type: %s | mode: 0x%04X (0x%02X) | inode %d | size: %d\n",
       is_dir(&inode) ? "directory" : "file", inode.i_mode,  e->enum_type,
       e->inode, e->entry_size);
  _log("----------------------------------\n");
}

bool ext2_init(void) {
  raw_logc("ext2_init >>>");
#ifdef SANDER
  if (!open_image(&fi))
    return false;
#else
  if (!sd_init())
    return false;
#endif

  sd_read_csd(buffer);
  
  // read MBR
  raw_logc("read MBR");
  if (!read_sector(0))
    return false;
  show_hex(buffer, 0, 0, 512);
  parse_mbr();

  _log("read Super Block\n");
  // read Super Block
  if (!read_block(SUPER_BLOCK_NUM))
    return false;
  parse_super_block();

  // read root inode
  if (!read_inode(&iroot, ROOT_INODE)) // 2
      return false;
  //show_inode(&iroot);
  return true;
}

bool open_file(char* name, size_t name_len, File* file) {
  // read file
  if (file->entry.inode != 0) {
    if (!get_entry_child_by_name(&file->entry, name, name_len))
      return false;
  } else {
    if (!get_inode_child_by_name(&iroot, name, name_len, &file->entry))
      return false;
  }

  if (get_entry_type(&file->entry) != efile) {
    show_dir_entry(&file->entry);
    _log("it is not regular file\n");
    return false;
  }

  if (!read_inode(&file->inode, file->entry.inode))
    return false;
  //show_inode(&i);

/*  _log("file content: (%d), size: %d bytes\n", file->inode.i_block[0], file->inode.i_size);
  if (!read_block(file->inode.i_block[0] + PART_START_BLOCK))
    return false;*/

  file->block_point = 0;
  file->buffer_point = 0;
  file->internal_seek_address = 0;
  return true;
}

bool open_cpath(const char* path, File* file) {
  _log("open_cfile: %s\n", path);
  size_t str_len = strlen(path);
  bool once_happend = false;

  if (path[0] != '/') {
    _log("path should start from //");
    return false;
  }

  memset(file, 0, sizeof(File));
  size_t start = 0; // position of first / char
  size_t end = start; // position of next / char

  for(; end < str_len; end++) {
    if (path[end] == '/') {
      if (end - start > 1) {// at leas 1 char /x/
        _log("entry: ");
        send_log_str((char*)(path + start + 1), end - start - 1); _log("\n");

        if (!once_happend) {
          if (!get_inode_child_by_name(&iroot, (char*)(path + start + 1),
                                       end - start - 1, &file->entry))
            return false;

          once_happend = true;
        } else {
          if (!get_entry_child_by_name(&file->entry, (char*)(path + start + 1),
                                       end - start - 1))
            return false;
        } // } else {
        start = end;
      } // if !once_happend
    } // end - start > 1
  } // for

  if (end - start > 1) {
    _log("last entry: ");
    send_log_str((char*)(path + start + 1), end - start);  _log("\n");

    if (!open_file((char*)(path + start + 1), end - start, file))
      return false;
  } else {
    _log("file not found\n");
    return false;
  }

  return true;
}

/* bool read_block_of_data_blocks(u32 root_block_id, char* out, u32 offset, u32 out_len)
 * Read data blocks pointed by root_block_id
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 * root_block_id - id of block contained data blocks ids
 * out           - output buffer
 * offset        - related offset (bytes) in data to read. Started from the beggining
 *                 of the first data block
 * out_len       - how many (bytes) needs to read
*/
u32 read_block_of_data_blocks(u32 root_block_id, char* out, u32 offset, u32 out_len) {
  u32 requested_len = out_len;
  u32 points_per_block = block_size / 4; // data blocks pointers in block
  u32 block_point = offset / block_size; // current data block position number in root_block
  u32 buffer_point = offset % block_size; // byte offset in buffer
  u32* p_root = (u32*)buffer;
  //_log("block_point %d | buffer_point %d | root_block_id %d\n", block_point, buffer_point,
  //     root_block_id);
  // got through all data blocks
  for (; block_point < points_per_block; block_point++, buffer_point = 0) {
    //_log("block_point %d\n", block_point);
    if (read_block( root_block_id + PART_START_BLOCK )) { // read root block
      // read data plock pointed by block_point
      if (read_block( p_root[block_point] + PART_START_BLOCK )) {
        u32 copy_len = umin(block_size - buffer_point, out_len); // how many data to read
        //_log("read ... copy_len %d\n", copy_len);
        memcpy(out, buffer + buffer_point, copy_len); // read data
        //send_log_str(out, copy_len); _log("\n");
        out += copy_len;
        buffer_point += copy_len;
        out_len -= copy_len; // data needed to read
        if (out_len != 0) { // if more data needed to read
          continue; // read a new data block
        } else { // nothing else to read
          _log("nothing else read\n");
          return requested_len - out_len;
        }
      } // if read data block
    } // if read root block
    _log("read block of data block error\n");
    return requested_len - out_len;
  } // for block_point
  return requested_len - out_len;
}

u32 read_file2(File* file, char* out, u32 out_len) {
  u32 requested_len = umin(out_len, file->inode.i_size); // data len needed to read
  out_len = requested_len;
  u32 buffer_point = file->internal_seek_address % block_size;
  u32 block_point = file->internal_seek_address / block_size;

  if (file->internal_seek_address >= file->inode.i_size)
    return 0;

  //_log("read_file  out_len %d | \n", out_len);
  _log("file->internal_seek_address = %d\n", file->internal_seek_address);

  for(;block_point < DIRECT_BLOCK_POINTERS_NUM; block_point++, buffer_point = 0) {
    /*_log("#### read_file: file->inode.i_block[%d] = %d\n",
         block_point, file->inode.i_block[block_point]);*/
    if (file->inode.i_block[file->block_point] == 0) // no data in this block
      break;

    if (read_block(file->inode.i_block[block_point] + PART_START_BLOCK)) {
      u32 copy_len = umin(out_len, block_size - buffer_point);
      //_log("read ...copy_len %d\n", copy_len);
      memcpy(out, buffer + buffer_point, copy_len);
      //send_log_str(out, copy_len); _log("\n");
      out += copy_len; // out buffer pointer
      out_len -= copy_len; // remain data to send
      buffer_point += copy_len;
      //_log("out_len = %d\n", out_len);
      if (out_len == 0) {// no more need to read
        //file->internal_seek_address += requested_len - out_len;
        break;
      }
    }
  } // for
  file->internal_seek_address += requested_len - out_len;
  _log("return %d\n", requested_len - out_len);
  //return requested_len - out_len;
  /* IN:
   * internal_seek_address
   *
   */
  if (out_len != 0) { // more data needed from singly inderect block
    //file->internal_seek_address += requested_len - out_len;
    u32 last_single_inderect_block_point = DIRECT_BLOCK_POINTERS_NUM + (block_size / 4);
    if (block_point >= SINGLE_INDERECT_BLOCK_ID // eq or gt then pointed by single inderect buffer
        && block_point < last_single_inderect_block_point) { // less then last ponted by single ..
      _log("file->internal_seek_address = %d\n", file->internal_seek_address);
      _log("next block to read %d(%d). pos: %d \n", file->inode.i_block[block_point], block_point,
           file->internal_seek_address - (DIRECT_BLOCK_POINTERS_NUM * block_size));

      u32 data_len = read_block_of_data_blocks(file->inode.i_block[SINGLE_INDERECT_BLOCK_ID], out,
                       // address related to start of singly inderect block
                       file->internal_seek_address - (DIRECT_BLOCK_POINTERS_NUM * block_size),
                                               out_len);
      _log("++++ singly inderect data read %d\n", data_len);
      file->internal_seek_address += data_len;
      out_len -= data_len;
    }
  }
  _log("file->internal_seek_address %d\n", file->internal_seek_address);
  // if we to read doule inderect block pointers
  if (out_len != 0) { // need more data
    _log("out_len = %d\n", out_len);
    u16 ptr_blk_size = block_size / 4;

    u32 first_doubly_inderect_point = (block_size / 4) * block_size
      + (DIRECT_BLOCK_POINTERS_NUM * block_size); // address of first byte addressed ...

    // amount of byte from the beginning of file til the end
    u32 last_doubly_inderect_point = first_doubly_inderect_point +
      ptr_blk_size * ptr_blk_size * block_size; // of doubly inderect block pointer


    _log("last_doubly_inderect_point %d\n", last_doubly_inderect_point);
    _log("first_doubly_inderect_point %d\n", first_doubly_inderect_point);

    // need to read from doubly inderrect block pointer
    if (file->internal_seek_address >= first_doubly_inderect_point &&
        file->internal_seek_address < last_doubly_inderect_point) {

      // Till now for simpicity we will think that addresses of doubly.... started from zero
      u32 point = file->internal_seek_address - first_doubly_inderect_point;
      _log("point %d\n", point);

      u32 blk_size_1lvl = block_size;
      u32 blk_size_2lvl = blk_size_1lvl * 255;

      // current block id on 2lvl
      u32 _2lvl_block_point = point / blk_size_2lvl; // amount of address block 3 lvl

      // current block id on 1lvl
      u32 _1lvl_buffer_point = (point % blk_size_2lvl) / blk_size_1lvl;

       // current position in data block
      u32 _0lvl_data_point = (point % blk_size_2lvl) % blk_size_1lvl;

      //_log("_3lvl_block_point %d\n", _3lvl_block_point); // deepest, contains data block pointers
      _log("_2lvl_block_point %d\n", _2lvl_block_point); // contains poiners to 2lvl
      _log("_1lvl_buffer_point %d\n", _1lvl_buffer_point); // data buffer num
      _log("_0lvl_data_point %d\n", _0lvl_data_point); // point in data buffer

      // read block with 3lvl pointers
      _log("pointer to 2 lvl %d\n", file->inode.i_block[DOUBLY_INDERECT_BLOCK_ID]);

      // now 3lvl blocks are in buffer

      // go thought 2lvl (syngly ptr block pointers)
      for (;_2lvl_block_point < ptr_blk_size; _2lvl_block_point++, _1lvl_buffer_point = 0) {
        read_block(file->inode.i_block[DOUBLY_INDERECT_BLOCK_ID] + PART_START_BLOCK);

        u32* pblockptr_id = ((u32*)buffer) + _2lvl_block_point;
        //_log("+ 2lvl block id 0x%08X\n", *pblockptr_id);

        if (*pblockptr_id == 0) {
          _log("pblockptr_id == 0\n");
          break;
        }

        // go though 1lvl (data ptr block pointers)
        for (; _1lvl_buffer_point < ptr_blk_size;
             _1lvl_buffer_point++, _0lvl_data_point = 0) {

          read_block(file->inode.i_block[DOUBLY_INDERECT_BLOCK_ID] + PART_START_BLOCK);
          read_block((*pblockptr_id) +  PART_START_BLOCK);

          u32* pblock_id = ((u32*)buffer) + _1lvl_buffer_point;
          //_log("+ 1lvl block id 0x%08X\n", *pblock_id);

          if (*pblock_id == 0)
            break;

          if (read_block((*pblock_id) + PART_START_BLOCK)) {
            // now we are on data buffer (on 0lvl)

            // copy data
            u16 copy_len = umin(block_size - _0lvl_data_point, out_len);
            /*_log("copy %d bytes from %d:%d:%d\n", copy_len,
                 _2lvl_block_point, _1lvl_buffer_point,
                 _0lvl_data_point);*/
            memcpy(out, buffer + _0lvl_data_point, copy_len);
            //send_log_str(out, copy_len); _log("\n");
            out += copy_len;
            _0lvl_data_point += copy_len;
            out_len -= copy_len;

            // no need to read more
            if (out_len == 0) {
              _log("no more data needed\n");
              _2lvl_block_point = ptr_blk_size;
              _1lvl_buffer_point = ptr_blk_size;
              _0lvl_data_point = block_size;
            }
          } // if read data block
        } // for go though 1 lvl
      } // for go through 2lvl
      file->internal_seek_address += requested_len - out_len;
    } // if need to read doubly inderect pointers
  } // if need more data (doubly inderect)

  // TODO handle triply inderect block pointers

  _log("return %d\n", requested_len - out_len);
  return requested_len - out_len; // successfully read data
}
