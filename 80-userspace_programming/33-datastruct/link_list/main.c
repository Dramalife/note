/*
* note datastruct link_list related file
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
* 
* $ uname -a
* Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015
* i686 i686 i686 GNU/Linux
* 
*/
#include<stdio.h>

#include"../../../lib_dramalife/link_list_lib/link_list.h"

#if (1 == HAVE_GCC_REL_SHOW)
#include "../../../lib_dramalife/gcc_related_lib/gcc_related_show.h"
#endif

ll_data_type *head;

int main(void)
{
	ll_data_type tmp;

	gcc_related_show_no_arg_in( GCC_R_SHOW_VERSION | GCC_R_SHOW_DATE | GCC_R_SHOW_TIME );

	head = add_elem_dlll(NULL, NULL, 0);/* Init a linklist */
	debug_dlll(head);//should not print
	printf("LINE:%d................\n",__LINE__);

	/*head =*/ add_elem_dlll(head,"aaaa", 1111);/* Add item to the linklist */
	debug_dlll(head);
	printf("LINE:%d................\n",__LINE__);
#if 0
	/*head =*/ add_elem_dlll(head,"bbbb", 2222);
	debug_dlll(head);
	printf("LINE:%d................\n",__LINE__);
#endif
	chg_elem_dlll(head,"aaaa",3333);/* Change value of item of the linklist */
	debug_dlll(head);
	printf("LINE:%d................\n",__LINE__);

	chg_elem_dlll(head,"aaaa",-1);/* Delete item of the linklist */
	debug_dlll(head);
	printf("LINE:%d................\n",__LINE__);

	/*head = */add_elem_dlll(head,"aaaa", 666);
	debug_dlll(head);
	printf("LINE:%d................\n",__LINE__);

	/* Add some items */
	int i;
	for(i = 0;i < 10; i++)
	{
		char nameaaa[20];
		sprintf(nameaaa,"eman%d",i);
		add_elem_dlll(head,nameaaa, i);
	}
	debug_dlll(head);/* Print out all item(s) */

	if( 0 == find_fifo_dlll(head, &tmp) )
		printf("FIFO---name:%s,type:%d\n",tmp.name, tmp.address_type);
	debug_dlll(head);

	if( 0 == find_filo_dlll(head, &tmp) )
		printf("FILO---name:%s,type:%d\n",tmp.name, tmp.address_type);
	debug_dlll(head);

test_dlll(head, 60000, 0);/* testing */

	return 0;
}

