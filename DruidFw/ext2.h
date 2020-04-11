// ext2.h

#include "fs.h"
/* ext2_init
 * Read MBR and main ext2 params from SD card
*/
bool ext2_init(void);

/* open_cpath
 * Open full path (example: /xxx/yyy/fff)
 * Writes Inode and Directory Entry structures into File param
*/
bool open_cpath(const char* path, File* file);

/* read_file3
 * Read out_len bytes from file in current seek position
*/
u32 read_file3(File* file, char* out, u32 out_len);
