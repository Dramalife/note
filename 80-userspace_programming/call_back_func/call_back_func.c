#include<stdio.h>

int handle_func(int arg1, char *arg2)
{
	printf("++%s+%d,arg1:%d,arg2:%s \n",__func__, __LINE__, arg1, arg2 ? arg2 : "null");
	return 1;
}

void call_func(int (*handle)(int, char*), int level1)
{
	printf("++%s,%d,arg2:%d \n",__func__,__LINE__, level1);
	(*handle)(__LINE__, "hhh");
}

int main(void)
{
	call_func(handle_func, 888);

	return 0;
}
/*
++call_func,11,arg2:888 
++handle_func+5,arg1:12,arg2:hhh
*/
