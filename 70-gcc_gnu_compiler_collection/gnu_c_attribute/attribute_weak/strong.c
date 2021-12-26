#include <stdio.h>

int func(void)
{
	printf("%s,%s,%d \n", __FILE__,  __func__, __LINE__);
	return 0;
}
