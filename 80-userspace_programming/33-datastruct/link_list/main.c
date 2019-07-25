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

	head = add_if_down2up(NULL, NULL, 0);/* Init a linklist */
	debug_if_down2up(head);//should not print
	printf("LINE:%d................\n",__LINE__);

	/*head =*/ add_if_down2up(head,"aaaa", 1111);/* Add item to the linklist */
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);
#if 0
	/*head =*/ add_if_down2up(head,"bbbb", 2222);
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);
#endif
	chg_if_down2up(head,"aaaa",3333);/* Change value of item of the linklist */
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);

	chg_if_down2up(head,"aaaa",-1);/* Delete item of the linklist */
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);

	/*head = */add_if_down2up(head,"aaaa", 666);
	debug_if_down2up(head);
	printf("LINE:%d................\n",__LINE__);

	/* Add some items */
	int i;
	for(i = 0;i < 10; i++)
	{
		char nameaaa[20];
		sprintf(nameaaa,"eman%d",i);
		add_if_down2up(head,nameaaa, i);
	}
	debug_if_down2up(head);/* Print out all item(s) */

	if( 0 == find_by_fifo_down2up(head, &tmp) )
		printf("FIFO---name:%s,type:%d\n",tmp.name, tmp.address_type);
	debug_if_down2up(head);

	if( 0 == find_by_filo_down2up(head, &tmp) )
		printf("FILO---name:%s,type:%d\n",tmp.name, tmp.address_type);
	debug_if_down2up(head);

//test_func_down2up(head, 60000, 0);/* testing */

	return 0;
}

