/*
 * note "tinyfs" related file
 * Copyright (C) 2019 Dramalife@live.com
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux;
 * 
 * Source :  https://mp.weixin.qq.com/s/Sidfn8CZn4KxKh6xMH2uJQ
 * Init : 2019.09.05, COPY FROM https://github.com/charliekernelmode/tinyfs.git;
 * Update 
 *
 */

#define MAXLEN 8
#define MAX_FILES	32
#define MAX_BLOCKSIZE  512

/*
 * The directory entry.
 */
struct tiny_dir_entry {
	char filename[MAXLEN];/* File name */
	uint8_t idx;
};

struct tiny_file_blk {
	uint8_t	busy;
	mode_t mode;
	uint8_t idx;

	union {
		uint8_t file_size;
		uint8_t dir_children;
	};
	char data[0];
};

