#include <stdio.h>

__attribute__((weak)) int func(void)
{
	printf("%s,%s,%d \n", __FILE__,  __func__, __LINE__);
	return 0;
}

int main(void)
{
	if(func)
	  func();
	return 0;
}
