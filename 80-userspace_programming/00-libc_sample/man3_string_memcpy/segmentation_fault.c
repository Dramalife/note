//dramalife@server:~/note/80-userspace_programming/00-libc_sample/man3_string_memcpy $ cat array_memcpy_segv.c
#include <string.h>
int main(void)
{
	unsigned char as[6],ad[6];
	memcpy(ad, as, 51200);
	return 0;
}
//
//dramalife@server:~/note/80-userspace_programming/00-libc_sample/man3_string_memcpy $ gcc array_memcpy_segv.c -Wall
//
//dramalife@server:~/note/80-userspace_programming/00-libc_sample/man3_string_memcpy $ ./a.out
//Segmentation fault (core dumped)
