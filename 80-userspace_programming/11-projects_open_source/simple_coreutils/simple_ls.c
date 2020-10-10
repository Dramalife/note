/*
 * note "simple coreutils - ls" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 5.5.0-12ubuntu1) 5.5.0 20171010
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-99-generic #100-Ubuntu SMP Wed Apr 22 20:32:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Tue Jun  9 11:12:09 CST 2020
 * 	Copy from : https://www.cnblogs.com/torres-9/p/5948635.html;
 * Update : Tue Jun  9 11:12:09 CST 2020
 * 	Change func name;
 *  
 * Update
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define MAX_PATH 1024

#define SIZE_STACK_LS_ARRAY_MEMBER	128
char stack_ls_array[26][SIZE_STACK_LS_ARRAY_MEMBER] = {0};
int stack_ls_index = 0;


void show_dir(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	struct dirent *dp;
	DIR *dfd;

	if ((dfd = opendir(dir)) == NULL) {
		fprintf(stderr, "%s:can not open %s\n", __func__, dir);
		return;
	}
	
#if JUST_FOR_REF______ && 0
	struct dirent {
		ino_t          d_ino;       /* Inode number */
		off_t          d_off;       /* Not an offset; see below */
		unsigned short d_reclen;    /* Length of this record */
		unsigned char  d_type;      /* Type of file; not supported
					       by all filesystem types */
		char           d_name[256]; /* Null-terminated filename */
	};
#endif
	while ((dp = readdir(dfd)) != NULL) {
		if ((strcmp(dp->d_name, ".") == 0) || (strcmp(dp->d_name, "..") == 0))
			continue;
		if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name)) {
			fprintf(stderr, "%s: name %s %s too long\n", __func__, dir, dp->d_name);
		} else {
			sprintf(name, "%s/%s", dir, dp->d_name);
			if( fcn )
			{
				(*fcn)(name);
			}
		}
	}
	closedir(dfd);
}

void show_files(char *name)
{
	printf("%s\n", name?name:"nullptr");
}


void show_file_or_dir_ls_dir_no_recursion(char *name)
{
	struct stat file_status;
	if (stat(name, &file_status) != 0) {
		fprintf(stderr, "%s:can not access to %s\n", __func__, name);
		return;
	}
	if ((file_status.st_mode & S_IFMT) == S_IFDIR) {
		//show_dir(name, show_file_or_dir_ls);
	}
	//printf("%8ld %s\n", file_status.st_size, name);
	sprintf(stack_ls_array[stack_ls_index++], "%8ld %s", file_status.st_size, name);
	if(stack_ls_index >= sizeof(stack_ls_array))
		stack_ls_index = 0;
}
void show_file_or_dir_ls(char *name)
{
	struct stat file_status;
	printf("[%s]\n", name);
	if (stat(name, &file_status) != 0) {
		fprintf(stderr, "%s:can not access to %s\n", __func__, name);
		return;
	}
	if ((file_status.st_mode & S_IFMT) == S_IFDIR) {
		show_dir(name, show_file_or_dir_ls_dir_no_recursion);
	}
	//printf("%8ld %s\n", file_status.st_size, name);
	memset(stack_ls_array[stack_ls_index++], 0, SIZE_STACK_LS_ARRAY_MEMBER);
	sprintf(stack_ls_array[stack_ls_index++], "%8ld %s", file_status.st_size, name);
	if(stack_ls_index >= sizeof(stack_ls_array))
		stack_ls_index = 0;
	while(stack_ls_index>=0)
	{
		if( 0 == strncmp(name, stack_ls_array[stack_ls_index], strlen(name)))
			printf("%s :\n", stack_ls_array[stack_ls_index]);
		else
			printf("%s\n", stack_ls_array[stack_ls_index]);
		stack_ls_index--;
	}
	stack_ls_index = 0;
}

void show_file_or_dir(char *name)
{
	struct stat file_status;
	if (stat(name, &file_status) != 0) {
		fprintf(stderr, "%s:can not access to %s\n", __func__, name);
		return;
	}
	if ((file_status.st_mode & S_IFMT) == S_IFDIR) {
		show_dir(name, show_file_or_dir);
	}
	printf("%8ld %s\n", file_status.st_size, name);
}


//#define MAIN_FUNC_CALL	show_file_or_dir
#define MAIN_FUNC_CALL	show_file_or_dir_ls
int main(int argc, char *argv[])
{
	if (argc == 1)
		MAIN_FUNC_CALL(".");
	else 
		while (--argc > 0)
			MAIN_FUNC_CALL(*++argv);
	return 0;
}
