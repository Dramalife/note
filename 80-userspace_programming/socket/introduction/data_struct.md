2021/12 


##### sockaddr

BIND(2)
The  actual  structure  passed  for  the  addr  argument will depend on the address family.  The sockaddr structure is
defined as something like:
```
    struct sockaddr {
        sa_family_t sa_family;
        char        sa_data[14];
    }
```
The only purpose of this structure is to cast the structure pointer passed in addr in order to  avoid  compiler  warn‐
ings.  See EXAMPLE below.

##### sockaddr_un
```
#define UNIX_PATH_MAX	108

struct sockaddr_un {
	__kernel_sa_family_t sun_family; /* AF_UNIX */
	char sun_path[UNIX_PATH_MAX];	/* pathname */
};
```

##### sockaddr_in
```
/* Structure describing an Internet (IP) socket address. */
#if  __UAPI_DEF_SOCKADDR_IN
#define __SOCK_SIZE__	16		/* sizeof(struct sockaddr)	*/
struct sockaddr_in {
  __kernel_sa_family_t	sin_family;	/* Address family		*/
  __be16		sin_port;	/* Port number			*/
  struct in_addr	sin_addr;	/* Internet address		*/

  /* Pad to size of `struct sockaddr'. */
  unsigned char		__pad[__SOCK_SIZE__ - sizeof(short int) -
			sizeof(unsigned short int) - sizeof(struct in_addr)];
};
#define sin_zero	__pad		/* for BSD UNIX comp. -FvK	*/
#endif

#if __UAPI_DEF_IN_ADDR
/* Internet address. */
struct in_addr {
	__be32	s_addr;
};
#endif

/* Internet address.  */
typedef uint32_t in_addr_t;
struct in_addr
  {
    in_addr_t s_addr;
  };
```
