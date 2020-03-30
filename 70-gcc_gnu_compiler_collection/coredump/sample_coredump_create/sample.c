#include "lib_dramalife.h"

void main(void)
{
	printf("Lib function start ...\n");
	dl_set_coredump_unlimit();
	printf("Lib function end ...\n");

	char *ptr=NULL;
	*ptr = 'a';

	return;
}
