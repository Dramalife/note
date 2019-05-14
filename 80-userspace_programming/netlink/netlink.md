### Learning Process

item : NETLINK_ROUTE  
link : [zebra-rt_netlink.c,func netlink_parse_info\(\)](/tools/quagga-1.2.4/zebra/rt_netlink.c)  
  
item : NETLINK_USER_DEFINE  
link : [single demo, kernel-userspace-com](/80-userspace_programming/netlink/demo_netlink__NETLINK_USER_DEFINE)  
  
item : NETLINK_KOBJECT_UEVENT  
link : [udev,from baohua](/80-userspace_programming/netlink/udev__NETLINK_KOBJECT_UEVENT)  


### includes

ex
```c
/*
   get : gcc -v
   Linux 5b2vdev 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux
 */
#include <sys/socket.h> // /usr/include/i386-linux-gnu/sys/socket.h > bits/socket.h > /usr/include/i386-linux-gnu/bits/socket.h
#include <linux/netlink.h> // /usr/include/linux/netlink.h
```

#### sys/socket.h
```c
/*
   uname -a :: Linux 5b2vdev 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux
   /usr/include/i386-linux-gnu/bits/socket.h
 */


/* Structure describing messages sent by
   `sendmsg' and received by `recvmsg'.  */
struct msghdr
{
	void *msg_name;		/* Address to send to/receive from.  */
	socklen_t msg_namelen;	/* Length of address data.  */

	struct iovec *msg_iov;	/* Vector of data to send/receive into.  */
	size_t msg_iovlen;		/* Number of elements in the vector.  */

	void *msg_control;		/* Ancillary data (eg BSD filedesc passing). */
	size_t msg_controllen;	/* Ancillary data buffer length.
				   !! The type should be socklen_t but the
				   definition of the kernel is incompatible
				   with this.  */

	int msg_flags;		/* Flags on received message.  */
};



```

#### linux/netlink.h
```c
/*
   uname -a :: Linux 5b2vdev 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux
   /usr/include/linux/netlink.h
 */



#define NETLINK_ROUTE		0	/* Routing/device hook				*/
#define NETLINK_UNUSED		1	/* Unused number				*/
#define NETLINK_USERSOCK	2	/* Reserved for user mode socket protocols 	*/
#define NETLINK_FIREWALL	3	/* Unused number, formerly ip_queue		*/
#define NETLINK_SOCK_DIAG	4	/* socket monitoring				*/
#define NETLINK_NFLOG		5	/* netfilter/iptables ULOG */
#define NETLINK_XFRM		6	/* ipsec */
#define NETLINK_SELINUX		7	/* SELinux event notifications */
#define NETLINK_ISCSI		8	/* Open-iSCSI */
#define NETLINK_AUDIT		9	/* auditing */
#define NETLINK_FIB_LOOKUP	10	
#define NETLINK_CONNECTOR	11
#define NETLINK_NETFILTER	12	/* netfilter subsystem */
#define NETLINK_IP6_FW		13
#define NETLINK_DNRTMSG		14	/* DECnet routing messages */
#define NETLINK_KOBJECT_UEVENT	15	/* Kernel messages to userspace */
#define NETLINK_GENERIC		16
/* leave room for NETLINK_DM (DM Events) */
#define NETLINK_SCSITRANSPORT	18	/* SCSI Transports */
#define NETLINK_ECRYPTFS	19
#define NETLINK_RDMA		20
#define NETLINK_CRYPTO		21	/* Crypto layer */

#define NETLINK_INET_DIAG	NETLINK_SOCK_DIAG

#define MAX_LINKS 32		


/* vim::28,36s/\s*$//g  */
struct sockaddr_nl {
	__kernel_sa_family_t    nl_family;      /* AF_NETLINK   */
	unsigned short  nl_pad;         /* zero         */
	__u32           nl_pid;         /* port ID      */
	__u32           nl_groups;      /* multicast groups mask */
};


struct nlmsghdr {
	__u32		nlmsg_len;	/* Length of message including header */
	__u16		nlmsg_type;	/* Message content */
	__u16		nlmsg_flags;	/* Additional flags */
	__u32		nlmsg_seq;	/* Sequence number */
	__u32		nlmsg_pid;	/* Sending process port ID */
};

```

