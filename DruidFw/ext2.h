// ext2.h

#include "fs.h"


typedef struct {
  u16 i_entry_index_bytes;
  u8 i_block_index;
  u32 i_block[12];
  u32 first_inode;
} DirEnumHandle;

typedef struct {
  u8 offset;
  u8 len;
  char* path;
  u8 path_len
} PathEnumHandle;

/* ext2_init
 * Read MBR and main ext2 params from SD card
*/
bool ext2_init(void);

/* open_cpath
 * Open full path (example: /xxx/yyy/fff)
 * Writes Inode structure into File param
*/
bool open_path(char* path, u8 path_len, File* file);

/* read_file3
 * Read out_len bytes from file in current seek position
*/
u32 read_file3(File* file, char* out, u32 out_len);

/* *** eum_dir_start ***
   IN: 
      handle - where store intermediate data for enumeratin
      out - where to copy first found dir entry struct
      inode - we will eum this enode (directory)
   RET:
      true - if success
*/
bool eum_dir_start(DirEnumHandle* handle, u32 inode);

/* *** eum_dir_next ***
   IN: 
      handle - where store intermediate data for enumeratin
      out - where to copy netx found dir entry struct
   RET:
      true - if success
      
*/
bool enum_dir_next(DirEnumHandle* handle, ext2_dir_entry* out);

