#ifndef _LIB_DRAMALIFE_INET_LIB_H_
#define _LIB_DRAMALIFE_INET_LIB_H_

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* Debug Print */
#ifdef _DLINET_DEBUG_ENABLED_
#define dlinet_print(fmt,...)     do{\
	printf("[%s][%s : %s + %d] ","libdl-inet", __FILE__, __func__, __LINE__);\
	printf(fmt,##__VA_ARGS__);\
}while(0)
#else
#define dlinet_print(fmt,...)     do{}while(0)
#endif


const char *dl_inet_addr_binary2test(int af, const void *src, char *dst, socklen_t size);
int dl_inet_addr_text2binary(int af, const char *src, void *dst);

#endif
