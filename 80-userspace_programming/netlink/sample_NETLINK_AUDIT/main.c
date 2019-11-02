#include <stdio.h>


// Redefined func defined at "auparse/message.c"
//void audit_msg(void *au, int priority, const char *fmt, ...)
//{
//	printf(fmt,...);
//}

#define audit_msg(a,b,f,...) do{printf(f,__VA_ARGS__);}while(0)


int main(void)
{
	audit_msg(NULL,0,"%s,%d \n",__func__,__LINE__);
	return 0;
}
