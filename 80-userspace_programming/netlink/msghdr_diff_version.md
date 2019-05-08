## 1. include/linux/socket.h

### 1.1 [4.0.0-040000-generic]
```c
/*
 *      As we do 4.4BSD message passing we use a 4.4BSD message passing
 *      system, not 4.3. Thus msg_accrights(len) are now missing. They
 *      belong in an obscure libc emulation or the bin.
 */

struct msghdr {
        void            *msg_name;      /* ptr to socket address structure */
        int             msg_namelen;    /* size of socket address structure */
        struct iov_iter msg_iter;       /* data */
        void            *msg_control;   /* ancillary data */
        __kernel_size_t msg_controllen; /* ancillary data buffer length */
        unsigned int    msg_flags;      /* flags on received message */
};

```
### 1.2 [2.6.31](https://elixir.bootlin.com/linux/v2.6.31/source/include/linux/socket.h)
```c
/*
*	As we do 4.4BSD message passing we use a 4.4BSD message passing
*	system, not 4.3. Thus msg_accrights(len) are now missing. They
*	belong in an obscure libc emulation or the bin.
*/

struct msghdr {
	void	*	msg_name;	/* Socket name			*/
	int		msg_namelen;	/* Length of name		*/
	struct iovec *	msg_iov;	/* Data blocks			*/
	__kernel_size_t	msg_iovlen;	/* Number of blocks		*/
	void 	*	msg_control;	/* Per protocol magic (eg BSD file descriptor passing) */
	__kernel_size_t	msg_controllen;	/* Length of cmsg list */
	unsigned	msg_flags;
};
```
### 1.3	[4.1.15](https://elixir.bootlin.com/linux/v4.1.15/source/include/linux/socket.h)
```c
/*
*	As we do 4.4BSD message passing we use a 4.4BSD message passing
*	system, not 4.3. Thus msg_accrights(len) are now missing. They
*	belong in an obscure libc emulation or the bin.
*/

struct msghdr {
	void		*msg_name;	/* ptr to socket address structure */
	int		msg_namelen;	/* size of socket address structure */
	struct iov_iter	msg_iter;	/* data */
	void		*msg_control;	/* ancillary data */
	__kernel_size_t	msg_controllen;	/* ancillary data buffer length */
	unsigned int	msg_flags;	/* flags on received message */
	struct kiocb	*msg_iocb;	/* ptr to iocb for async requests */
};
```

