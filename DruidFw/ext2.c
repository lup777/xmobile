// ext2.c

typedef uint32_t __u32
typedef uint16_t __u16
typedef int32_t __s32
typedef int16_t __s16
typedef uint8_t __u8

﻿struct ext2_super_block {
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
  ﻿__u16   s_errors;              /*  Код ошибки(см.ниже) */
  __u16   s_pad;
  __u32   s_lastcheck;           /*  POSIX время последней проверки */
  __u32   s_checkinterval;       /*  POSIX время между принудительными проверками */
  __u32   s_creator_os;          /*  ID ОС (см. ниже)  */
  __u32   s_rev_level;           /*  Версия */
  __u16   s_def_resuid;          /*  UserID, могущий использовать зар. блоки */
  __u16   s_def_resgid;          /*  GroupID, могущий использовать зар. блоки */
  __u32   s_reserved[235];       /*  Зарезервировано */
};

﻿struct ext2_group_desc
{
  __u32 bg_block_bitmap;        /*  Номер блока в битовой карте*/
  __u32 bg_inode_bitmap;        /*  Дескриптор блока в битовой карте */
  __u32 bg_inode_table;         /*  Номер блока в таблице дескрипторов */
  __u16 bg_free_blocks_count;   /*  Свободно блоков */
  __u16 bg_free_inodes_count;   /*  Свободно индексных дескрипторов */
  __u16 bg_used_dirs_count;     /*  Количество директорий */
  __u16 bg_pad;
  __u32 bg_reserved[3];
};

// Группа блоков = (инод-1) / s_inodes_per_group
// где s_inodes_per_group соответствующее поле в суперблоке

// Адрес = (инод-1) % s_inodes_per_group
// де % - деление по модулю

// Блок = (Адрес * inode_size) / block_size
// адрес блока

struct ext2_inode {
	__u16	i_mode;		/* Тип файла и права доступа (см.ниже) */
	__u16	i_uid;		/* UserID */
	__u32	i_size;		/* Размер в байтах */
	__u32	i_atime;	/* POSIX время последнего обращения к файлу */
	__u32	i_ctime;	/* POSIX время создания */
	__u32	i_mtime;	/* POSIX время последней модификации */
	__u32	i_dtime;	/* POSIX время удаления */
	__u16	i_gid;		/* GroupID */
	__u16	i_links_count;	/* Кол-во ссылок на дескриптор */
 	__u32	i_blocks;	/* Кол-во секторов (не блоки!) */
	__u32	i_flags;	/* Флаг (см.ниже) */
	union {
		struct {
			__u32  l_i_reserved1; /* Зарезервировано */
		} linux1;
		struct {
      __u32  h_i_translator; /* ??? */
		} hurd1;
		struct {
			__u32  m_i_reserved1; /* Зарезервировано */
		} masix1;
  } osd1;
	__u32	i_block[EXT2_N_BLOCKS];/* Указатели на блок */
	__u32	i_generation;	/* Версия файла (для NFS) */
	__u32	i_file_acl;	/* Доп. аттрибуты файла */
	__u32	i_dir_acl;	/* Доп. аттрибуты директории */
	__u32	i_faddr;	/* Адрес фрагмента */
	union {
		struct {
			__u8	l_i_frag;	/* Номер фрагмента */
			__u8	l_i_fsize;	/* Размер фрагмента */
			__u16	i_pad1;         /* Зарезервировано */
			__u16	l_i_uid_high;	/* 16 старших битов UserID */
			__u16	l_i_gid_high;	/* 16 старших битов GroupID */
			__u32	l_i_reserved2;  /* Зарезервировано */
		} linux2; /* LINUX */
		struct {
			__u8	h_i_frag;	/* Номер фрагмента */
			__u8	h_i_fsize;	/* Размер фрагмента */
			__u16	h_i_mode_high;  /* 16 старших битов T&P */
			__u16	h_i_uid_high;   /* 16 старших битов UserID */
			__u16	h_i_gid_high;   /* 16 старших битов GroupID */
			__u32	h_i_author;     /* UserID или автор */
		} hurd2; /* GNU HURD */
		struct {
			__u8	m_i_frag;	/* Номер фрагмента */
			__u8	m_i_fsize;      /* Размер фрагмента */
			__u16	m_pad1;         /* Зарезервировано */
			__u32	m_i_reserved2[2]; /* Зарезервировано */
		} masix2; /* MASIX */
	} osd2;				/* Специфичные значения */
};

/* FILE TYPE
0x1	FIFO
0x2	Символьное устройство
0x4	Директория
0x6	Блочное устройство
0x8	Регулярный файл
0xA	Ссылка
0xC	UNIX-cокет
*/


// http://samag.ru/archive/article/203
