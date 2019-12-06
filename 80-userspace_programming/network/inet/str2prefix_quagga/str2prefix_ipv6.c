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

#define COMPILE_SUCCESSFULLY_FIRST	1

#define DL_STR2PREFIX_IPV6_COPY_CODE_FROM_ZEBRA	1


#if (1 == DL_STR2PREFIX_IPV6_COPY_CODE_FROM_ZEBRA)

#define HAVE_IPV6	1

//quagga/lib/prefix.h
#define IPV6_MAX_BITLEN    128
#if (!COMPILE_SUCCESSFULLY_FIRST)
/* IPv4 and IPv6 unified prefix structure. */
struct prefix
{
  u_char family;
  u_char prefixlen;
  union 
  {
    u_char prefix;
    struct in_addr prefix4;
#ifdef HAVE_IPV6
    struct in6_addr prefix6;
#endif /* HAVE_IPV6 */
    struct 
    {
      struct in_addr id;
      struct in_addr adv_router;
    } lp;
    struct ethaddr prefix_eth;	/* AF_ETHERNET */
    u_char val[8];
    uintptr_t ptr;
  } u __attribute__ ((aligned (8)));
};
#endif
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

#if(!COMPILE_SUCCESSFULLY_FIRST)
/* 
 * Return 1 if the address/netmask contained in the prefix structure
 * is the same, and else return 0.  For this routine, 'same' requires
 * that not only the prefix length and the network part be the same,
 * but also the host part.  Thus, 10.0.0.1/8 and 10.0.0.2/8 are not
 * the same.  Note that this routine has the same return value sense
 * as '==' (which is different from prefix_cmp).
 */
int
prefix_same (const struct prefix *p1, const struct prefix *p2)
{
  if (p1->family == p2->family && p1->prefixlen == p2->prefixlen)
    {
      if (p1->family == AF_INET)
	if (IPV4_ADDR_SAME (&p1->u.prefix4.s_addr, &p2->u.prefix4.s_addr))
	  return 1;
#ifdef HAVE_IPV6
      if (p1->family == AF_INET6 )
	if (IPV6_ADDR_SAME (&p1->u.prefix6.s6_addr, &p2->u.prefix6.s6_addr))
	  return 1;
#endif /* HAVE_IPV6 */
      if (p1->family == AF_ETHERNET) {
	if (!memcmp(p1->u.prefix_eth.octet, p2->u.prefix_eth.octet, ETHER_ADDR_LEN))
	    return 1;
      }
    }
  return 0;
}

/*
 * Return 0 if the network prefixes represented by the struct prefix
 * arguments are the same prefix, and 1 otherwise.  Network prefixes
 * are considered the same if the prefix lengths are equal and the
 * network parts are the same.  Host bits (which are considered masked
 * by the prefix length) are not significant.  Thus, 10.0.0.1/8 and
 * 10.0.0.2/8 are considered equivalent by this routine.  Note that
 * this routine has the same return sense as strcmp (which is different
 * from prefix_same).
 */
int
prefix_cmp (const struct prefix *p1, const struct prefix *p2)
{
  int offset;
  int shift;

  /* Set both prefix's head pointer. */
  const u_char *pp1 = (const u_char *)&p1->u.prefix;
  const u_char *pp2 = (const u_char *)&p2->u.prefix;

  if (p1->family != p2->family || p1->prefixlen != p2->prefixlen)
    return 1;

  offset = p1->prefixlen / PNBBY;
  shift = p1->prefixlen % PNBBY;

  if (shift)
    if (maskbit[shift] & (pp1[offset] ^ pp2[offset]))
      return 1;

  while (offset--)
    if (pp1[offset] != pp2[offset])
      return 1;

  return 0;
}
#endif//(!COMPILE_SUCCESSFULLY_FIRST)
#endif  //(1 == DL_STR2PREFIX_IPV6_COPY_CODE_FROM_ZEBRA)

#define DL_LIB_STR2PREFIX_IPV6_HAVE_MAIN	1
#if (defined DL_LIB_STR2PREFIX_IPV6_HAVE_MAIN) && (1 == DL_LIB_STR2PREFIX_IPV6_HAVE_MAIN)
int main(void)
#else
int sample_dl_lib_str2prefix_ipv6(void)
#endif
{
	int i;
	const char *s1="fe80::1234/64";
	const char *s2="fe80::5678/64";
	struct prefix_ipv6 prefix_data1;
	struct prefix_ipv6 prefix_data2;
	struct prefix_ipv6 *p1;
	struct prefix_ipv6 *p2;

	p1 = &prefix_data1;
	p2 = &prefix_data2;
	memset(p1, 0, sizeof(struct prefix_ipv6));
	memset(p2, 0, sizeof(struct prefix_ipv6));

	str2prefix_ipv6(s1, p1);
	str2prefix_ipv6(s2, p2);

	printf("[%s,%d] prefixlen(%d,%d),family(0x%x,0x%x) \n"
			,__func__,__LINE__
			,p1->prefixlen,p2->prefixlen
			,p1->family,p2->family
	      );

	for(i=0; i<4; i++)
	{
		printf("[%s,%d] (0x%08x)\n",__func__,__LINE__,p1->prefix.s6_addr32[i]);
		printf("[%s,%d] (0x%08x)\n",__func__,__LINE__,p2->prefix.s6_addr32[i]);
	}

	for(i=0; i<16; i++)
	{
		printf("[%s,%d] (0x%02x)\n",__func__,__LINE__,p1->prefix.s6_addr[i]);
		printf("[%s,%d] (0x%02x)\n",__func__,__LINE__,p2->prefix.s6_addr[i]);
		//..................^^2*4bit
	}

#if (!COMPILE_SUCCESSFULLY_FIRST)
	printf("[%s,%d] prefix_same(%d), prefix_cmp(%d) \n"
			,__func__,__LINE__
			,prefix_same((struct prefix *)p1,(struct prefix *)p2)
			,prefix_cmp ((struct prefix *)p1,(struct prefix *)p2)
	      );
#endif

	return 0;
}
