/*
 * note "ipv6 address convertion" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-70-generic #79-Ubuntu SMP Tue Nov 12 10:36:11 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux;
 * 
 * Init : 2019.11.20, 
 *		COPY FROM quagga-1.2.4/lib/prefix.c;
 * Update 
 *
 */

#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//quagga/lib/prefix.h
#define IPV6_MAX_BITLEN    128
struct prefix_ipv6
{
	u_char family;
	u_char prefixlen;
	struct in6_addr prefix __attribute__ ((aligned (8)));
};


/* If given string is valid return pin6 else return NULL */
	int
str2prefix_ipv6 (const char *str, struct prefix_ipv6 *p)
{
	char *pnt;
	char *cp;
	int ret;

	pnt = strchr (str, '/');

	/* If string doesn't contain `/' treat it as host route. */
	if (pnt == NULL)
	{
		ret = inet_pton (AF_INET6, str, &p->prefix);
		if (ret == 0)
			return 0;
		p->prefixlen = IPV6_MAX_BITLEN;
	}
	else
	{
		int plen;

#if 0 //CHANGED!
		cp = XMALLOC (MTYPE_TMP, (pnt - str) + 1);
#else
		cp = (char *)malloc( (pnt - str + 1)*sizeof(char) );
#endif
		strncpy (cp, str, pnt - str);
		*(cp + (pnt - str)) = '\0';
		ret = inet_pton (AF_INET6, cp, &p->prefix);
		free (cp);
		if (ret == 0)
			return 0;
		plen = (u_char) atoi (++pnt);
		if (plen > IPV6_MAX_BITLEN)
			return 0;
		p->prefixlen = plen;
	}
	p->family = AF_INET6;

	return ret;
}

#define DL_LIB_STR2PREFIX_IPV6_HAVE_MAIN	1
#if (defined DL_LIB_STR2PREFIX_IPV6_HAVE_MAIN) && (1 == DL_LIB_STR2PREFIX_IPV6_HAVE_MAIN)
int main(void)
#else
int sample_dl_lib_str2prefix_ipv6(void)
#endif
{
	int i;
	const char *addr="fe80::1234/64";
	struct prefix_ipv6 prefix;

	str2prefix_ipv6(addr, &prefix);

	for(i=0; i<4; i++)
	{
		printf("[%s,%d] (0x%08x)\n",__func__,__LINE__,prefix.prefix.s6_addr32[i]);
	}

	for(i=0; i<16; i++)
	{
		printf("[%s,%d] (0x%02x)\n",__func__,__LINE__,prefix.prefix.s6_addr[i]);
		//..................^^2*4bit
	}

	return 0;
}
