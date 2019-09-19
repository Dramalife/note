#include <stdio.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
void func(void)
{
	printf("%s,%d ,For little endian \n",__func__,__LINE__);
}
#else
void func(void)
{
	printf("%s,%d ,For big endian \n",__func__,__LINE__);
}
#endif

void main(void)
{
	func();
}

