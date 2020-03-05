#include "header.h"

void functionb(void)
{
	gb = 999;
	printf("%s,%d,%d\n",__func__,__LINE__,gb);
}

