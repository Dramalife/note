/*
	Source url : https://www.runoob.com/cprogramming/c-bit-fields.html
	Change : auto format
*/
#include <stdio.h>
#include <string.h>

struct
{
	unsigned int age : 3;
} Age;

int main( )
{
	Age.age = 4;
	printf( "Sizeof( Age ) : %d\n", sizeof(Age) );
	printf( "Age.age : %d\n", Age.age );

	Age.age = 7;
	printf( "Age.age : %d\n", Age.age );

	Age.age = 8; /* 1000 in binary, over */  /* 二进制表示为 1000 有四位，超出 */
	printf( "Age.age : %d\n", Age.age );

	return 0;
}

