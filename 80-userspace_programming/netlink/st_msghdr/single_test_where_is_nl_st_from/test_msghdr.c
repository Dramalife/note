/*
验证结构体“struct msghdr”的来源；
userspace programming including file , use "gcc -v" : 
		#include "..." search starts here:
		#include <...> search starts here:
		/usr/lib/gcc/i686-linux-gnu/4.8/include
		/usr/local/include
		/usr/lib/gcc/i686-linux-gnu/4.8/include-fixed
		/usr/include/i386-linux-gnu
		/usr/include
		End of search list.
filesystem, not kernel source code !
*/
#include<sys/socket.h>
#include<linux/netlink.h>
#include<stdio.h>

/* local compile
gcc xxx.c --sysroot=/
*/


void main(void)
{

printf("size:%d\n", sizeof(struct msghdr));
//printf("size:%d\n", sizeof(struct user_msghdr));/* error,only for kernel */

return;
}
