/*
 * note "inet - convert form" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 5.5.0-12ubuntu1) 5.5.0 20171010
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-99-generic #100-Ubuntu SMP Wed Apr 22 20:32:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Fri Jun  5 10:39:39 CST 2020
 * 	Ref : INET_PTON(3), INET_NTOP(3) ;
 * Update : Fri Jun  5 10:39:39 CST 2020
 * 	Make lib_dramalife, support lib && demo ;
 *  
 * Update
 *
 */



#include "lib_dramalife.h"

/* Data struct just for ref */
#if JUST_SHOW_____ && 0
typedef uint32_t in_addr_t;

struct in_addr {
	in_addr_t s_addr;
};
#endif


/* Lib code */
#if _DL_INET_LIB_ENABLE_


/***
 * TODO
 */
	const char *
dl_inet_addr_binary2test(int af, const void *src, char *dst, socklen_t size)
{
	const char *ret;

	/* Parameter check */
	if( AF_INET == af ){
		if( size < INET_ADDRSTRLEN ){
			dlinet_print("ERR : buff len is (%d), at least(%d)!\n", size, INET_ADDRSTRLEN);
			return NULL;
		}
	}
	else if( AF_INET6 == af ){
		if( size < INET6_ADDRSTRLEN ){
			dlinet_print("ERR : buff len is (%d), at least(%d)!\n", size, INET6_ADDRSTRLEN);
			return NULL;
		}
	}

	/* Data process */
	if ( NULL == (ret = inet_ntop(af, src, dst, size)) ) {
		dlinet_print("ERR : inet_ntop! (%s)\n", strerror(errno));
	}

	return ret;
}

/***
 * TODO
 */
	int 
dl_inet_addr_text2binary(int af, const char *src, void *dst)
{
	int ret_p2n;
	switch ((  ret_p2n = inet_pton( af, src, dst)  ))
	{
		case 1:
			dlinet_print("convert done!\n");
			return 0;
			break;
		case 0:
			dlinet_print("ERR : Not in presentation format.\n");
			return -2;
			break;
		case -1:
			dlinet_print("ERR : inet_pton! (%s)\n", strerror(errno));
			return -1;
			break;
		default:
			dlinet_print("ERR : never! BLOCK!\n");
			while(1)
			{
			}
			break;
	}
}
#endif/* _DL_INET_LIB_ENABLE_ */


/* Main for demo */
#if _DRAMALIFE_LIB_HAS_FUNC_MAIN_
int main(int argc, char *argv[])
{
	//unsigned char buf[sizeof(struct in6_addr)];
	unsigned char buf[sizeof(struct in_addr)];
	char str[INET_ADDRSTRLEN];

	// text -> binary
	dl_inet_addr_text2binary(AF_INET, "127.1.2.3", buf);

	// binary -> test
	dl_inet_addr_binary2test(AF_INET, buf, str, INET_ADDRSTRLEN);

	dlinet_print("string:%s\n", str);

	exit(EXIT_SUCCESS);
}
#endif/* _DRAMALIFE_LIB_HAS_FUNC_MAIN_ */

