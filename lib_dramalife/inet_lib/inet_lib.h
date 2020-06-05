#ifndef _LIB_DRAMALIFE_INET_LIB_H_
#define _LIB_DRAMALIFE_INET_LIB_H_


/***
 * Headers
 */
// For form convert
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// For UDP socket
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/***
 * MACRO Functions
 */
// Debug Print
#ifdef _DLINET_DEBUG_ENABLED_
#define dlinet_print(fmt,...)     do{\
	printf("[%s][%s : %s + %d] ","libdl-inet", __FILE__, __func__, __LINE__);\
	printf(fmt,##__VA_ARGS__);\
}while(0)
#else
#define dlinet_print(fmt,...)     do{}while(0)
#endif


/***
 * Declearations
 */
extern const char *dl_inet_addr_binary2test(int af, const void *src, char *dst, socklen_t size);
extern int dl_inet_addr_text2binary(int af, const char *src, void *dst);


#endif
