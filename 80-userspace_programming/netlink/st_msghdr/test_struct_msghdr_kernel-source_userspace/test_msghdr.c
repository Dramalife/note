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
