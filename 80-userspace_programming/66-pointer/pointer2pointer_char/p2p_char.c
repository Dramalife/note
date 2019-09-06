/*
 * note "Linux C - pointer to pointer" related file
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
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux
 * ;
 * 
 * Init : 2019.09.06 ;
 * Update 
 *
 */

#define TEST_PTR_SIZE	1

#include <string.h>
#include <stdio.h>
#if TEST_PTR_SIZE
#include <stdlib.h>
#endif

/* Can change value of argin */
void func_chg_arg(void *ptr)
{
	printf("ARGINN:%s\n",(char *)ptr);
	strcpy((char *)ptr,"changed_by_other");

}

int main(void)
{
#define ARRAY_LEN	1024
	char arr[ARRAY_LEN];
	memset(arr,0,ARRAY_LEN);
	printf("array_size:%d\n",sizeof(arr));/* WILL SHOW : "array_size:(ARRAY_LEN)". */
	strcpy(arr,"init_in_main");

#if TEST_PTR_SIZE/* Additional test : sizeof pointer. */
	char *ptr1;
	ptr1 = (char *)malloc(100 * sizeof(char));
	printf("ptr1_size:%d \n",sizeof(ptr1));/* ptr1_size:4 */
	char *ptr2 = (char *)malloc(200 * sizeof(char));
	printf("ptr2_size:%d \n",sizeof(ptr2));/* ptr2_size:4 */
#endif

	printf("BEFORE:%s\n",arr);/* WILL SHOW : "init_in_main" */
	func_chg_arg(&arr);/* "arr" is a char type array, "&arr" is a pointer that point to pointer. */
	printf("ARGERR:%s\n",arr);/* WILL SHOW : "changed_by_other" */

	return 0;
}

