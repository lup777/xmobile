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
#define BUFFER_SIZE 1024
#define NUM_PER_LINE 32
static u32 part_start_addr = 0;
static u16 block_size = 1024;
static u32 blocks_per_group = 0;
static u32 inodes_per_group = 0;
//static u32 inode_table_block = 0;
#ifdef SANDER
u8 buffer[BUFFER_SIZE]; // block size
#else
static u8 buffer[BUFFER_SIZE]; // block size
#endif
static ext2_inode iroot;

#ifdef SANDER
FILE* fi;

void raw_logc(const char* str) {
  printf("%s\n", str);
}
void sd_read_csd(u8* buffer) {(void)(buffer);}
#define _log printf
#define CHECK {}

#endif

void show_hex(u8* buffer_, long int display_offset, u32 start, u32 num) {
  _log("show_hex(buffer, 0x%08lX, 0x%08X, %d)\n", display_offset, start, num);

  for (u32 i = start; i < start + num
         && i + NUM_PER_LINE < BUFFER_SIZE; i+=NUM_PER_LINE ) {

    _log("%08lX:", display_offset + i);
    for (u8 j = 0; j < NUM_PER_LINE; j ++) {
      if (!(j % 4)) _log(" ");
      _log(" %02X", buffer_[i + j]);
    }
    _log("\n");
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
  //show_hex(buffer, addr - 512, 0, 512);
  return true;
}

void parse_mbr(void) {
  Mbr* mbr = (Mbr*)buffer;

  part_start_addr = mbr->p1.abs_start_sector * SECTOR_SIZE;
  _log("part_start_addr : 0x%08X\n", part_start_addr);
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

bool is_file(ext2_inode* pinode) {
  return (pinode->i_mode & 0x8000) != 0;
}

bool dir_entry_is_dir(ext2_dir_entry* entry) {
  return entry->enum_type == 2;
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
  //_log("read_inode >>> ");
  if (inodes_per_group == 0) {
    _log("inodes_per_group == 0 !! failed\n");
    return false;
  }
  u16 group = (inode_num - 1) / inodes_per_group;
  u16 inode = (inode_num - 1) - (group * inodes_per_group);

  //_log("| group: %d | ", group);
  //_log("inode: %4d | \n", inode);
  u32 inode_table_block = get_inode_table_block_for_group(group);

  u8 inodes_per_block = block_size / INODE_SIZE;
  u16 inode_table_block_offset = inode / inodes_per_block;
  inode -= (inode_table_block_offset * inodes_per_block);

  // read inode table
  u32 block = inode_table_block + PART_START_BLOCK +
                                  inode_table_block_offset;
  /*_log("               read_inode: inode table block %d | \n",
    block);*/

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

/* *** open_file2 ***
   open file by inode num
*/
bool open_file(u32 inode, File* file) {
  file->internal_seek_address = 0;
  
  return read_inode(&(file->inode), inode);
}

/*bool open_file(char* name, size_t name_len, File* file) {
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

//  _log("file content: (%d), size: %d bytes\n", file->inode.i_block[0], file->inode.i_size);
  //if (!read_block(file->inode.i_block[0] + PART_START_BLOCK))
  //  return false;

  file->block_point = 0;
  file->buffer_point = 0;
  file->internal_seek_address = 0;
  return true;
}*/

/*bool open_cpath(const char* path, File* file) {
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
*/
/* *** read_data_block_by_id ***
 * IN: 
 *     copy_len - how many bytes need to read
 *     block_id - block id from inode (related to partition start)
 *     block_offset - offset in data block
 * return:
 *         how many bytes has readed
*/
u16 read_data_block_by_id(u32 block_id, u16 block_offset, char* out, u32 copy_len) {
  if (block_offset > block_size) {// bad block offset
    _log("ERR: bad block offset");
    return 0;
  }

  copy_len = umin(copy_len, block_size);
  copy_len = umin(block_size - block_offset, copy_len);
    
  if (read_block(block_id + PART_START_BLOCK)) {
    //_log("read_data_block_by_id[%d]: read %d bytes\n", block_id, copy_len);
    memcpy(out, buffer + block_offset, copy_len);
    return copy_len;
  }
  return 0;
}

/* *** read_direct_data_blocks ***
 * IN:
 *     file - pointer to File struct
 *     data_block_serial_number - serial number of first data block to read 
 *      in range[0 .. 11]
 *     first_data_block_offset - start position in first data block
 *     out - out buffer
 *     out_len - how many byte need to read
 * return: 
 *         how many files was read
*/
u32 read_direct_data_blocks(File* file,
                            u32 data_block_serial_number,
                            u16 first_data_block_offset,
                            char* out,
                            u32 out_len) {
  u32 result_len = 0;
  for(; data_block_serial_number < DIRECT_BLOCK_POINTERS_NUM
        ;data_block_serial_number++) {
    u32 read_len = 0;

    u32 data_block_id = file->inode.i_block[data_block_serial_number];
    read_len = read_data_block_by_id(data_block_id,
                                     first_data_block_offset,
                                     out,
                                     out_len - result_len);
    if (read_len == 0)
      break;

    /*_log("read data block[%d] [%d .. %d] out_len = %d\n",
         data_block_serial_number,
         first_data_block_offset,
         block_size, out_len);*/

    first_data_block_offset = 0;
    out += read_len;
    result_len += read_len;
  }
  return result_len;
}

/* *** read_singly_indirect_data_blocks ***
 * IN: 
 *     file - pointer to File struct
 *     data_block_serial_number - serial number of first data block to read 
 *      in range[12 .. (255 + 12)]
 *     first_data_block_offset - start position in first data block
 *     out - out buffer
 *     out_len - how many byte need to read
 * return: 
 *         how many files was read
 *     
*/
u32 read_singly_indirect_data_blocks(File* file,
                                     u32 data_block_serial_number,
                                     u16 first_data_block_offset,
                                     char* out,
                                     u32 out_len) {
  // direct pointers: 0 - 11
  // single idirect pointer: 12
  //            [Inode Double Indirect Pointer (13)]
  /*                           |
         [PP             P              PP]       //  0 lvl (pointers to next lvl)
          |              |              |         
     [PP  P  PP]    [PP  P  PP]     [PP  PP PP]   //  1 lvl (pointers to data blocks)
      /   |   \      /   |   \       /   |   \
    [DD] [D] [DD]  [DD] [D]  [DD]  [DD] [D]  [DD] //  2 lvl (data blocks)
  */

  u32 ready_len = 0;
  // related to first singly indirect data block
  data_block_serial_number -= 12;

  //_log("SI: data_block_serial_number = 0x%08X (%d)\n",
  //     data_block_serial_number, data_block_serial_number);
  //_log("SI: first_data_block_offset = 0x%08X (%d)\n", first_data_block_offset,
  //     first_data_block_offset);
  
  for(; data_block_serial_number < 256; data_block_serial_number ++) {
    if ((out_len - ready_len) == 0)
      break; // nothing to read more
    
    u32 si_block_id = file->inode.i_block[SINGLE_INDERECT_BLOCK_ID];
    
    if (read_block(si_block_id + PART_START_BLOCK)) {
      // now i_block[12] with pointers to data blocks is in buffer
      u32 data_block_id = ((u32*)buffer)[data_block_serial_number];
      u32 read_len = read_data_block_by_id(data_block_id,
                                           first_data_block_offset,
                                           out,
                                           out_len - ready_len);
      if (read_len == 0)
        break;
      
      first_data_block_offset = 0;
      ready_len += read_len;
      out += read_len;
      
    } // if
  } // for
  
  return ready_len;
}

/* *** get_indirect_subblock_id ***
  [   A        B       T   ] [   _       _       _   ]
   [X Y Z]  [W E R] [U I O]   [_ _ _] [_ _ _] [_ _ _]
EXAMPLE: func(B, 2) -> E
IN: 
    block_id - ID of block with idirect poiters
    index - index of subblock to read
RET: 
    ID of sub block with given index
*/
u32 get_indirect_subblock_id(u32 block_id, u16 index) {
  if (read_block(block_id + PART_START_BLOCK)) {
    return ((u32*)buffer)[index];
  }
  return 0;
}

/* *** read_singly_indirect_data_blocks ***
 * IN: 
 *     file - pointer to File struct
 *     data_block_serial_number - serial number of first data block to read 
 *      in range[12 .. (255 + 12)]
 *     data_block_offset - start position in first data block
 *     out - out buffer
 *     out_len - how many byte need to read
 * return: 
 *         how many files was read
 *     
*/
u32 read_doubly_indirect_data_blocks(File* file,
                                     u32 data_block_serial_number,
                                     u16 data_block_offset,
                                     char* out,
                                     u32 out_len) {
  u32 ready_len = 0;
  // adjust data block serial number to the first data block on layer_0
  data_block_serial_number -= 12; // minus direct blocks
  data_block_serial_number -= 256; // minus singly indirect blocks
  //_log("DI: data_block_serial_number = 0x%08X (%d)\n",
  //     data_block_serial_number, data_block_serial_number);

  /*
    i_block[13][layer_0_point][layer_2_point][data_offset] -> byte
    i_block[13][layer_0_point][layer_2_point] -> 1024 bytes of data block    
   */

  u32 layer_0_index = data_block_serial_number / 256;
  u32 layer_1_index = data_block_serial_number % 256;

  //_log("DI: layer_0_index = 0x%08X (%d)\n", layer_0_index, layer_0_index);
  //_log("DI: layer_1_index = 0x%08X (%d)\n", layer_1_index, layer_1_index);

  u32 block_id = file->inode.i_block[DOUBLY_INDERECT_BLOCK_ID];

  for (; layer_0_index <= 255; layer_0_index++) {
    if ((out_len - ready_len) == 0) break; // nothing to read more
    u32 read_len = 0;
      
    u32 layer_0_block_id = get_indirect_subblock_id(block_id, layer_0_index);
    //_log("DI: layer_0_block_id = 0x%08X (%d)\n", layer_0_block_id, layer_0_block_id);

    for (; layer_1_index <= 255; layer_1_index++) {
     if ((out_len - ready_len) == 0) break; // nothing to read more
     u32 layer_1_block_id = get_indirect_subblock_id(layer_0_block_id, layer_1_index);
     //_log("DI: layer_1_block_id = 0x%08X (%d)\n", layer_1_block_id, layer_1_block_id);

      read_len = read_data_block_by_id(layer_1_block_id, data_block_offset,
                                       out, out_len - ready_len);
      data_block_offset = 0;
      out += read_len;
      
      if (read_len == 0)
        break;

      ready_len += read_len;
    }
    
    layer_1_index = 0;
    if (read_len == 0)
      break;
  }
  //show_hex(buffer, 0, 0, 32);
  return ready_len;
}

/* *** read_file3 ***
 * IN: 
 *     out - pointer to output buffer
 *     out_len - how many byte need to read
 * return:
 *         how many bytes was read
*/
u32 read_file3(File* file, char* out, u32 out_len) {
  u32 ready_len = 0;

  if (file->internal_seek_address >= file->inode.i_size) {
    _log("R3: nothing to read (%d >= %d)\n", file->internal_seek_address,
         file->inode.i_size);
    return 0;
  }
  out_len = umin(out_len, file->inode.i_size - file->internal_seek_address);
  //_log("R3: file->internal_seek_address = %d\n", file->internal_seek_address);



  for (u32 read_len = 0; ready_len < out_len; ) {
    read_len = 0;

    // how may data blocks left behind
    uint32_t data_block_serial_number = file->internal_seek_address / block_size;
    
    u32 data_block_offset = file->internal_seek_address % block_size;
    /*
    _log("R3: file->internal_seek_address = 0x%08X (%d)\n", file->internal_seek_address,
         file->internal_seek_address);
    _log("R3: data_block_serial_number = 0x%08X (%d)\n", data_block_serial_number,
         data_block_serial_number);
    _log("R3: data_block_offset = 0x%08X (%d)\n", data_block_offset, data_block_offset);
    */
    if (data_block_serial_number < 12 ) {
      //_log("R3: read direct blocks [%d .. 11]\n", data_block_serial_number);
      read_len = read_direct_data_blocks(file,
                                         data_block_serial_number,
                                         data_block_offset,
                                         out,
                                         out_len - ready_len);
      //_log("R3: read %d bytes from direct data blocks\n", read_len);
    } else if (data_block_serial_number < 12 + 256) {
      //_log("R3: read singly indirect blocks [%d .. %d]\n",
      //     data_block_serial_number, 12 + 255);
      
      read_len = read_singly_indirect_data_blocks(file,
                                                  data_block_serial_number,
                                                  data_block_offset,
                                                  out + ready_len,
                                                  out_len - ready_len);
      
    } else if (data_block_serial_number < (u32)(12 + 256 + 65536)) {
    //_log("R3: read doubly idirect blocks [%d .. %d]\n", data_block_serial_number,
    //       12 + 255 + (255 * 255));

      read_len = read_doubly_indirect_data_blocks(file,
                                                  data_block_serial_number,
                                                  data_block_offset,
                                                  out + ready_len,
                                                  out_len - ready_len);
    } else {
      // triply indirect blocks
      // NOT IMPLEMENTED
    }

    if (read_len == 0)
      break;
    file->internal_seek_address += read_len;

    ready_len += read_len;
  } // for

  return ready_len;
}

/* *** eum_dir_start ***
   IN: 
      handle - where store intermediate data for enumeratin
      inode - we will eum this enode (directory)
   RET:
      true - if success
*/
bool eum_dir_start(DirEnumHandle* handle, u32 inode) {
  static ext2_inode root;
  handle->i_block_index = 0;
  handle->i_entry_index_bytes = 0;
  handle->first_inode = inode;

  //_log("eum_dir_start: inode = %d\n", inode);
  if (inode < 2)
    return false;

  for(u8 i = 0; i < 12; i++)
    handle->i_block[i] = 0;
 
  return true;
}

/* *** eum_dir_next ***
   IN: 
      handle - where store intermediate data for enumeratin
      out - where to copy netx found dir entry struct
   RET:
      true - if success
*/
bool enum_dir_next(DirEnumHandle* handle, ext2_dir_entry* out) {
  //_log("enum_dir_next: handle->i_entry_index_bytes = %d\n", handle->i_entry_index_bytes);
  //_log("enum_dir_next: handle->i_block_index = %d\n", handle->i_block_index);
  if (handle->i_block[0] == 0) {
    // first call
    static ext2_inode root;
    if (read_inode(&root, handle->first_inode)) {
      for(u8 i = 0; i < 12; i++)
        handle->i_block[i] = root.i_block[i];
    }
  }

  
  if (handle->i_entry_index_bytes >= block_size) {
    handle->i_block_index ++;
    handle->i_entry_index_bytes = 0;
  }
  
  if (handle->i_block[handle->i_block_index] == 0)
    return false;
  
  if (handle->i_block_index > DIRECT_BLOCK_POINTERS_NUM) {
    _log("max of entries with direct pointers. Indirect pointers are not supported \n");
    return false;
  }
  //_log("enum_dir_next: block: %d", handle->i_block[handle->i_block_index]);
  if (read_block(handle->i_block[handle->i_block_index] + PART_START_BLOCK)) {
    ext2_dir_entry* dir_entry = (ext2_dir_entry*)(buffer + handle->i_entry_index_bytes);

    handle->i_entry_index_bytes += dir_entry->entry_size;

    memcpy(out, dir_entry, dir_entry->entry_size);
    _log("  entry: ");
    send_log_str(dir_entry->name, dir_entry->name_len); _log("\n");

    return true;
  } // if ( read_block
  _log("something failed during enum_dir_next\n");
  return false;
}

bool string_find_char(char* str, u8 len, char c, u8* index_out) {
  for (u8 i = 0; i < len; i ++) {
    if(str[i] == c) {
      *index_out = i;
      return true;
    }
  }
  return false;
}
 
bool enum_path_string_start(PathEnumHandle* handle, char* path, u8 path_len) {
  u8 point = 0;
  handle->offset = 0;
  handle->len = 0;
  handle->path = path;
  handle->path_len = path_len;

  _log(" start: path: ");
  send_log_str(handle->path + point, handle->path_len - point); _log("\n");


  if (handle->path[point] != '/') {
    _log("next: invalid path, should start from, or maybe end of path /\n");
    _log(" path: ");
    send_log_str(handle->path[point], handle->path_len - point); _log("\n");
    return false;
  }

  /*point ++; // go to next char after '/'

  u8 index;
  if (string_find_char(path + point,
                       handle->path_len - point, '/', &index)) {
    // it is next (not last) entry
    handle->offset = point;
    handle->len = index - 1;
  } else { // it is last entry
    handle->offset = point;
    handle->len = handle->path_len - point;
    }*/
  
  return true;
}

bool str_cmp(char* str1, char* str2, u8 len) {
  for (u8 i = 0; i < len; i++) {
    if (str1[i] != str2[i])
      return false;
  }
  return true;
}

bool enum_path_string_next(PathEnumHandle* handle) {
  /*_log("path next: offset: %d\n", handle->offset);
    _log("path next: len: %d\n", handle->len);*/
  u8 point = handle->offset + handle->len;

  if (point >= handle->path_len)
    return false;
    
  if (handle->path[point] != '/') {
    _log("next: invalid path, should start from /, or maybe end of path \\n");
    _log(" path: ");
    //send_log_str(handle->path[point], handle->path_len - point); _log("\n");
    return false;
  }

  point += 1; // go to next char after '/'

  u8 index;
  if (string_find_char(handle->path + point, handle->path_len - point,
                       '/', &index)) {
    // it is next (not last) entry
    handle->offset = point;
    handle->len = index;
  } else { // it is last entry
    handle->offset = point;
    handle->len = handle->path_len - point;
  }

  return true;
}

bool open_path(char* path, u8 path_len, File* file) {

  DirEnumHandle enum_handle;
  ext2_dir_entry entry;
  PathEnumHandle h;

  if (!eum_dir_start(&enum_handle, ROOT_INODE)) {
    _log("start_eum_dir failed\n"); return NULL;
  }

  if (!enum_path_string_start(&h, path, path_len)) {
    _log("failed to enum path string"); return NULL;
  }
    
  int i = 0;

  if (!enum_path_string_next(&h)) return NULL;
    
  while (enum_dir_next(&enum_handle, &entry)) {
    if (entry.name_len == h.len) {
      if (str_cmp(entry.name, path + h.offset, h.len)) {
        _log("- --> found entry from path: ");
        send_log_str(entry.name, entry.name_len); _log("\n");

        if (!dir_entry_is_dir(&entry))
          break; // it is a file
        
        if (eum_dir_start(&enum_handle, entry.inode)) {
          if (!enum_path_string_next(&h))
            break;
          continue;
        } else {
          _log("eum_dir_start failed\n");
          return NULL;
        }
      }
    }

    i++;
    if (i > 30)
      break;
  } // while

  if (!dir_entry_is_dir(&entry)) {
    return open_file(entry.inode, file);
  }
  
  return false;
}

