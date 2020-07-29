/*
 * COPY FROM : 21cnbao-git(/training/call_printf_in_signal.c)
 * Update : Del code unrelated to SIGSEGV;
 */



#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
void handler(int s)
{
	if(s==SIGSEGV)printf("now got segmentation fault\n");
	exit(1);
}
int main(void)
{
	int *p=NULL;
	signal(SIGSEGV,handler);
	*p=0;
	return 0;
}
