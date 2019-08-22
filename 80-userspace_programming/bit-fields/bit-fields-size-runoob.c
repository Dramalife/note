/*
	Source url : https://www.runoob.com/cprogramming/c-bit-fields.html
	Change	: auto format
*/
#include <stdio.h>
#include <string.h>

/* ����򵥵Ľṹ */
struct
{
	unsigned int widthValidated;
	unsigned int heightValidated;
} status1;

/* ����λ��ṹ */
struct
{
	unsigned int widthValidated : 1;
	unsigned int heightValidated : 1;
} status2;

int main( )
{
	printf( "Memory size occupied by status1 : %d\n", sizeof(status1));
	printf( "Memory size occupied by status2 : %d\n", sizeof(status2));

	return 0;
}
