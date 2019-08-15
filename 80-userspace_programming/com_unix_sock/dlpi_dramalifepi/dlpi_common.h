/*
   note project dlpi related file
   Copyright (C) 2019 Dramalife@live.com

   This file is part of [note](https://github.com/Dramalife/note.git)

   note is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

   Init	2019.08.11 Dramalife,ubuntu_64_lenovo.
   Update 
*/
#ifndef _DLPI_COMMON_H
#define _DLPI_COMMON_H

#define DLPI_UNIX_PROCESS_MAIN "/tmp/.dlpi_socket"

typedef unsigned char u8_t;
typedef int (*func_cvi)(char *,void *,int *);

struct ctl_dlpi
{
	int cmd_type;
	char *data;
};

struct code2func
{
	int no;
	func_cvi func;
};

typedef struct dlpi_frame
{
	char *des_sock_path;	//specific sock path
	u8_t mechine_specific_code[2];	// specific mechine, not useful yet.
	u8_t lll_type[2];	//(toDES|to_others|)
	u8_t global_data_struct_code[2];//16 bit.
	void *buffer;		//(trans_to_datastruct|trans_to_DES_level)
}dlpi_frame;

#endif

