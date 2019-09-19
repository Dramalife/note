#include <stdio.h>

void test_endian(void)
{
	int i;

	/* objdump:
	 * 804847e:       c7 45 f0 6c 6c 62 62    movl   $0x62626c6c,-0x10(%ebp)   
	 */
	char str[4]="llbb";

	/*RESULT : little endian ,l=0x6C,b=0x62*/
//	printf("%s endian ,l=0x%X,b=0x%X\n", str[0] == 'l' ? "little" : "big", 'l', 'b' );

	return ;
}

int main(void)
{
	test_endian();
}
