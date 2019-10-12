//ref : https://www.runoob.com/cprogramming/c-unions.html

#include <stdio.h>
#include <string.h>


/* Data Struct */
union Data
{
	int i;
	float f;
	char  str[20];
};



/* FUNC : "int endian_test(void)";
 * a.out: ELF 32-bit MSB executable, MIPS, MIPS32 rel2 version 1 (SYSV), dynamically linked, interpreter /lib/ld-, with debug_info, not stripped;
 * a.out: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/l, 
 *		for GNU/Linux 3.2.0, BuildID[sha1]=41f92edd2e1b30108089f2942a92db893e3e0485, not stripped;
 */
int endian_test(void)
{
	union Data data;

	printf("\n\n\n[%s,%d]vvvvv \n",__func__,__LINE__);

	data.i= 0x01020304;
	if( data.str[0] == 0x01 )
	{
		printf("Big Endian! \n");/* Tested passed on MIPS32(BE). */
	}
	else if( data.str[0] == 0x04 )
	{
		printf("Little Endian! \n");/* Tested passed on x86_64(LE). */
	}
	else
	{
		printf("Unknown! \n");
	}

	return 0;
}

int size_union(void)
{
	union Data data;        

	printf("\n\n\n[%s,%d]vvvvv \n",__func__,__LINE__);

#if (__SIZE_WIDTH__ == 64)
	printf( "Memory size occupied by data : %ld\n", sizeof(data));
#else
	printf( "Memory size occupied by data : %d\n", sizeof(data));
#endif

	return 0;
}

int value_set_overwrite(void)
{
	union Data data;        

	printf("\n\n\n[%s,%d]vvvvv \n",__func__,__LINE__);

	data.i = 10;
	data.f = 220.5;
	strcpy( data.str, "C Programming");

	printf( "data.i : %d\n", data.i);
	printf( "data.f : %f\n", data.f);
	printf( "data.str : %s\n", data.str);

	return 0;
}

int value_set(void)
{
	union Data data;        

	printf("\n\n\n[%s,%d]vvvvv \n",__func__,__LINE__);

	data.i = 10;
	printf( "data.i : %d\n", data.i);

	data.f = 220.5;
	printf( "data.f : %f\n", data.f);

	strcpy( data.str, "C Programming");
	printf( "data.str : %s\n", data.str);

	return 0;
}

#if 1
int main(void)
#else
int main_union(void)
#endif
{
	printf("[%s,%d]START! \n",__func__,__LINE__);

	size_union();
	value_set_overwrite();
	value_set();
	endian_test();
	return 0;
}

