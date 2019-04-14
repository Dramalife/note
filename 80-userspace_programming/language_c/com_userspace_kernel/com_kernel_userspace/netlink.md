[source url](https://www.cnblogs.com/wenqiang/p/6306727.html)

一、什么是Netlink通信机制

Netlink套接字是用以实现用户进程与内核进程通信的一种特殊的进程间通信(IPC) ,也是网络应用程序与内核通信的最常用的接口。

Netlink 是一种特殊的 socket，它是 Linux 所特有的，类似于 BSD 中的AF_ROUTE 但又远比它的功能强大，目前在Linux 内核中
使用netlink 进行应用与内核通信的应用很多; 包括：路由 daemon（NETLINK_ROUTE），用户态 socket 协议（NETLINK_USERSOCK），
防火墙（NETLINK_FIREWALL），netfilter 子系统（NETLINK_NETFILTER），内核事件向用户态通知（NETLINK_KOBJECT_UEVENT），
通用 netlink（NETLINK_GENERIC）等。

Netlink 是一种在内核与用户应用间进行双向数据传输的非常好的方式，用户态应用使用标准的 socket API 就可以使用 netlink 提供的强大功能，
内核态需要使用专门的内核 API 来使用 netlink。
Netlink 相对于系统调用，ioctl 以及 /proc文件系统而言具有以下优点：
 1. netlink使用简单，只需要在include/linux/netlink.h中增加一个新类型的 netlink 协议定义即可,(如 #define NETLINK_TEST 20 然后，内核和用户态应用就可以立即通过 socket API 使用该 netlink 协议类型进行数据交换);
 2. netlink是一种异步通信机制，在内核与用户态应用之间传递的消息保存在socket缓存队列中，发送消息只是把消息保存在接收者的socket的接收队列，而不需要等待接收者收到消息；
 3. 使用 netlink 的内核部分可以采用模块的方式实现，使用 netlink 的应用部分和内核部分没有编译时依赖;
 4. netlink 支持多播，内核模块或应用可以把消息多播给一个netlink组，属于该neilink 组的任何内核模块或应用都能接收到该消息，内核事件向用户态的通知机制就使用了这一特性；
 5. 内核可以使用 netlink 首先发起会话;

二、Netlink常用数据结构及函数

　用户态应用使用标准的 socket API有（sendto()），recvfrom()； sendmsg(), recvmsg()）

　下面简单介绍几种NETLINK用户态通信的常用数据结构

　1、用户态数据结构

   Netlink通信跟常用UDP Socket通信类似：
　struct sockaddr_nl 是netlink通信地址跟普通socket struct sockaddr_in类似
  struct sockaddr_nl结构：　
```c
  struct sockaddr_nl{
    __kernel_sa_family_tnl_family;  /*AF_NETLINK（跟AF_INET对应*/
    unsigned short  nl_pad; /* zero */
    __u32   nl_pid; /* port ID  （通信端口号）*/
    __u32   nl_groups;  /* multicast groups mask */
  };
```
struct nlmsghd 结构：
```c
/* struct nlmsghd 是netlink消息头*/
struct nlmsghdr {   
__u32   nlmsg_len;  /* Length of message including header */
__u16   nlmsg_type; /* Message content */
__u16   nlmsg_flags;/* Additional flags */
__u32   nlmsg_seq;  /* Sequence number */
__u32   nlmsg_pid;  /* Sending process port ID */
};
```
（1）nlmsg_len：整个netlink消息的长度（包含消息头）；
（2）nlmsg_type：消息状态，内核在include/uapi/linux/netlink.h中定义了以下4种通用的消息类型，它们分别是：
```c
#define NLMSG_NOOP  0x1 /* Nothing. */
#define NLMSG_ERROR 0x2 /* Error*/
#define NLMSG_DONE  0x3 /* End of a dump*/
#define NLMSG_OVERRUN   0x4 /* Data lost*/

#define NLMSG_MIN_TYPE  0x10/* < 0x10: reserved control messages */

/*NLMSG_NOOP：不执行任何动作，必须将该消息丢弃；
NLMSG_ERROR：消息发生错误；
NLMSG_DONE：标识分组消息的末尾；
NLMSG_OVERRUN：缓冲区溢出，表示某些消息已经丢失。
NLMSG_MIN_TYPEK：预留 */
```
（3）nlmsg_flags：消息标记，它们用以表示消息的类型，如下
```c
/* Flags values */

#define NLM_F_REQUEST   1   /* It is request message.   */
#define NLM_F_MULTI 2   /* Multipart message, terminated by NLMSG_DONE */
#define NLM_F_ACK   4   /* Reply with ack, with zero or error code */
#define NLM_F_ECHO  8   /* Echo this request*/
#define NLM_F_DUMP_INTR 16  /* Dump was inconsistent due to sequence change */

/* Modifiers to GET request */
#define NLM_F_ROOT  0x100   /* specify tree root*/
#define NLM_F_MATCH 0x200   /* return all matching  */
#define NLM_F_ATOMIC0x400   /* atomic GET   */
#define NLM_F_DUMP  (NLM_F_ROOT|NLM_F_MATCH)

/* Modifiers to NEW request */
#define NLM_F_REPLACE   0x100   /* Override existing*/
#define NLM_F_EXCL  0x200   /* Do not touch, if it exists   */
#define NLM_F_CREATE0x400   /* Create, if it does not exist */
#define NLM_F_APPEND0x800   /* Add to end of list   */
```
（4）nlmsg_seq：消息序列号，用以将消息排队，有些类似TCP协议中的序号（不完全一样），但是netlink的这个字段是可选的，不强制使用；
（5）nlmsg_pid：发送端口的ID号，对于内核来说该值就是0，对于用户进程来说就是其socket所绑定的ID号。

struct msghdr 结构体
```c
struct iovec {/* Scatter/gather array items */
 void  *iov_base;  /* Starting address */
 size_t iov_len;   /* Number of bytes to transfer */
 };
  /* iov_base: iov_base指向数据包缓冲区，即参数buff，iov_len是buff的长度。msghdr中允许一次传递多个buff，
以数组的形式组织在 msg_iov中，msg_iovlen就记录数组的长度 （即有多少个buff）
  */
 struct msghdr {
 void *msg_name;   /* optional address */
 socklen_t msg_namelen;/* size of address */
 struct iovec *msg_iov;/* scatter/gather array */
 size_tmsg_iovlen; /* # elements in msg_iov */
 void *msg_control;/* ancillary data, see below */
 size_tmsg_controllen; /* ancillary data buffer len */
 int   msg_flags;  /* flags on received message */
 };
 /* msg_name： 数据的目的地址，网络包指向sockaddr_in, netlink则指向sockaddr_nl;
msg_namelen: msg_name 所代表的地址长度
msg_iov: 指向的是缓冲区数组
msg_iovlen: 缓冲区数组长度
msg_control: 辅助数据，控制信息(发送任何的控制信息)
msg_controllen: 辅助信息长度
msg_flags: 消息标识
 */
```
2. netlink 内核数据结构、常用宏及函数：

netlink消息类型：
```c
#define NETLINK_ROUTE   0   /* Routing/device hook  */
#define NETLINK_UNUSED  1   /* Unused number*/
#define NETLINK_USERSOCK2   /* Reserved for user mode socket protocols  */
#define NETLINK_FIREWALL3   /* Unused number, formerly ip_queue */
#define NETLINK_SOCK_DIAG   4   /* socket monitoring*/
#define NETLINK_NFLOG   5   /* netfilter/iptables ULOG */
#define NETLINK_XFRM6   /* ipsec */
#define NETLINK_SELINUX 7   /* SELinux event notifications */
#define NETLINK_ISCSI   8   /* Open-iSCSI */
#define NETLINK_AUDIT   9   /* auditing */
#define NETLINK_FIB_LOOKUP  10  
#define NETLINK_CONNECTOR   11
#define NETLINK_NETFILTER   12  /* netfilter subsystem */
#define NETLINK_IP6_FW  13
#define NETLINK_DNRTMSG 14  /* DECnet routing messages */
#define NETLINK_KOBJECT_UEVENT  15  /* Kernel messages to userspace */
#define NETLINK_GENERIC 16
/* leave room for NETLINK_DM (DM Events) */
#define NETLINK_SCSITRANSPORT   18  /* SCSI Transports */
#define NETLINK_ECRYPTFS19
#define NETLINK_RDMA20
#define NETLINK_CRYPTO  21  /* Crypto layer */

#define NETLINK_INET_DIAG   NETLINK_SOCK_DIAG

#define MAX_LINKS 32
```
netlink常用宏：
```c
#define NLMSG_ALIGNTO   4U
/* 宏NLMSG_ALIGN(len)用于得到不小于len且字节对齐的最小数值 */
#define NLMSG_ALIGN(len) ( ((len)+NLMSG_ALIGNTO-1) & ~(NLMSG_ALIGNTO-1) )

/* Netlink 头部长度 */
#define NLMSG_HDRLEN ((int) NLMSG_ALIGN(sizeof(struct nlmsghdr)))

/* 计算消息数据len的真实消息长度（消息体 +　消息头）*/
#define NLMSG_LENGTH(len) ((len) + NLMSG_HDRLEN)

/* 宏NLMSG_SPACE(len)返回不小于NLMSG_LENGTH(len)且字节对齐的最小数值 */
#define NLMSG_SPACE(len) NLMSG_ALIGN(NLMSG_LENGTH(len))

/* 宏NLMSG_DATA(nlh)用于取得消息的数据部分的首地址，设置和读取消息数据部分时需要使用该宏 */
#define NLMSG_DATA(nlh)  ((void*)(((char*)nlh) + NLMSG_LENGTH(0)))

/* 宏NLMSG_NEXT(nlh,len)用于得到下一个消息的首地址, 同时len 变为剩余消息的长度 */
#define NLMSG_NEXT(nlh,len)  ((len) -= NLMSG_ALIGN((nlh)->nlmsg_len), \
  (struct nlmsghdr*)(((char*)(nlh)) + NLMSG_ALIGN((nlh)->nlmsg_len)))

/* 判断消息是否 >len */
#define NLMSG_OK(nlh,len) ((len) >= (int)sizeof(struct nlmsghdr) && \
   (nlh)->nlmsg_len >= sizeof(struct nlmsghdr) && \
   (nlh)->nlmsg_len <= (len))

/* NLMSG_PAYLOAD(nlh,len) 用于返回payload的长度*/
#define NLMSG_PAYLOAD(nlh,len) ((nlh)->nlmsg_len - NLMSG_SPACE((len)))
```
netlink 内核常用函数：

netlink_kernel_create内核函数用于创建 内核socket用用户态通信
```c
static inline struct sock *
netlink_kernel_create(struct net *net, int unit, struct netlink_kernel_cfg *cfg)
/* net: net指向所在的网络命名空间, 一般默认传入的是&init_net(不需要定义);  定义在net_namespace.c(extern struct net init_net);
   unit：netlink协议类型
   cfg： cfg存放的是netlink内核配置参数（如下）
*/

/* optional Netlink kernel configuration parameters */
struct netlink_kernel_cfg {
unsigned intgroups;  
unsigned intflags;  
void(*input)(struct sk_buff *skb); /* input 回调函数 */
struct mutex*cb_mutex;
void(*bind)(int group);
bool(*compare)(struct net *net, struct sock *sk);
};
```
 单播netlink_unicast() 和 多播netlink_broadcast()
 ```c
 /* 来发送单播消息 */
extern int netlink_unicast(struct sock *ssk, struct sk_buff *skb, __u32 portid, int nonblock);
/* ssk: netlink socket
   skb: skb buff 指针
   portid： 通信的端口号
   nonblock：表示该函数是否为非阻塞，如果为1，该函数将在没有接收缓存可利用时立即返回，而如果为0，该函数在没有接收缓存可利用 定时睡眠
*/

/* 用来发送多播消息 */
extern int netlink_broadcast(struct sock *ssk, struct sk_buff *skb, __u32 portid,
 __u32 group, gfp_t allocation);
/* ssk: 同上（对应netlink_kernel_create 返回值）、
   skb: 内核skb buff
   portid： 端口id
   group: 是所有目标多播组对应掩码的"OR"操作的合值。
   allocation: 指定内核内存分配方式，通常GFP_ATOMIC用于中断上下文，而GFP_KERNEL用于其他场合。
这个参数的存在是因为该API可能需要分配一个或多个缓冲区来对多播消息进行clone
*/
```
三、netlink实例
（1）用户态程序 （sendto()， recvfrom()）
```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <linux/netlink.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>

#define NETLINK_TEST30
#define MSG_LEN125
#define MAX_PLOAD125

typedef struct _user_msg_info
{
struct nlmsghdr hdr;
char  msg[MSG_LEN];
} user_msg_info;

int main(int argc, char **argv)
{
int skfd;
int ret;
user_msg_info u_info;
socklen_t len;
struct nlmsghdr *nlh = NULL;
struct sockaddr_nl saddr, daddr;
char *umsg = "hello netlink!!";

/* 创建NETLINK socket */
skfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_TEST);
if(skfd == -1)
{
perror("create socket error\n");
return -1;
}

memset(&saddr, 0, sizeof(saddr));
saddr.nl_family = AF_NETLINK; //AF_NETLINK
saddr.nl_pid = 100;  //端口号(port ID)
saddr.nl_groups = 0;
if(bind(skfd, (struct sockaddr *)&saddr, sizeof(saddr)) != 0)
{
perror("bind() error\n");
close(skfd);
return -1;
}

memset(&daddr, 0, sizeof(daddr));
daddr.nl_family = AF_NETLINK;
daddr.nl_pid = 0; // to kernel
daddr.nl_groups = 0;

nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PLOAD));
memset(nlh, 0, sizeof(struct nlmsghdr));
nlh->nlmsg_len = NLMSG_SPACE(MAX_PLOAD);
nlh->nlmsg_flags = 0;
nlh->nlmsg_type = 0;
nlh->nlmsg_seq = 0;
nlh->nlmsg_pid = saddr.nl_pid; //self port

memcpy(NLMSG_DATA(nlh), umsg, strlen(umsg));
ret = sendto(skfd, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&daddr, sizeof(struct sockaddr_nl));
if(!ret)
{
perror("sendto error\n");
close(skfd);
exit(-1);
}
printf("send kernel:%s\n", umsg);

memset(&u_info, 0, sizeof(u_info));
len = sizeof(struct sockaddr_nl);
ret = recvfrom(skfd, &u_info, sizeof(user_msg_info), 0, (struct sockaddr *)&daddr, &len);
if(!ret)
{
perror("recv form kernel error\n");
close(skfd);
exit(-1);
}

printf("from kernel:%s\n", u_info.msg);
close(skfd);

free((void *)nlh);
return 0;
}
```
Netlink 内核模块代码：
```c
/****************************************
* Author: zhangwj
* Date: 2017-01-19
* Filename: netlink_test.c
* Descript: netlink of kernel
* Kernel: 3.10.0-327.22.2.el7.x86_64
* Warning:
******************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <net/sock.h>
#include <linux/netlink.h>

#define NETLINK_TEST 30
#define MSG_LEN125
#define USER_PORT100

MODULE_LICENSE("GPL");
MODULE_AUTHOR("zhangwj");
MODULE_DESCRIPTION("netlink example");

struct sock *nlsk = NULL;
extern struct net init_net;

int send_usrmsg(char *pbuf, uint16_t len)
{
struct sk_buff *nl_skb;
struct nlmsghdr *nlh;

int ret;

/* 创建sk_buff 空间 */
nl_skb = nlmsg_new(len, GFP_ATOMIC);
if(!nl_skb)
{
printk("netlink alloc failure\n");
return -1;
}

/* 设置netlink消息头部 */
nlh = nlmsg_put(nl_skb, 0, 0, NETLINK_TEST, len, 0);
if(nlh == NULL)
{
printk("nlmsg_put failaure \n");
nlmsg_free(nl_skb);
return -1;
}

/* 拷贝数据发送 */
memcpy(nlmsg_data(nlh), pbuf, len);
ret = netlink_unicast(nlsk, nl_skb, USER_PORT, MSG_DONTWAIT);

return ret;
}

static void netlink_rcv_msg(struct sk_buff *skb)
{
struct nlmsghdr *nlh = NULL;
char *umsg = NULL;
char *kmsg = "hello users!!!";

if(skb->len >= nlmsg_total_size(0))
{
nlh = nlmsg_hdr(skb);
umsg = NLMSG_DATA(nlh);
if(umsg)
{
printk("kernel recv from user: %s\n", umsg);
send_usrmsg(kmsg, strlen(kmsg));
}
}
}

struct netlink_kernel_cfg cfg = {
.input  = netlink_rcv_msg, /* set recv callback */
};  

int test_netlink_init(void)
{
/* create netlink socket */
nlsk = (struct sock *)netlink_kernel_create(&init_net, NETLINK_TEST, &cfg);
if(nlsk == NULL)
{   
printk("netlink_kernel_create error !\n");
return -1;
}   
printk("test_netlink_init\n");

return 0;
}

void test_netlink_exit(void)
{
if (nlsk){
netlink_kernel_release(nlsk); /* release ..*/
nlsk = NULL;
}   
printk("test_netlink_exit!\n");
}

module_init(test_netlink_init);
module_exit(test_netlink_exit);
```

Makeflie
```Makefile
#
#Desgin of Netlink
#

MODULE_NAME :=netlink_test
obj-m :=$(MODULE_NAME).o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all:
$(MAKE) -C $(KERNELDIR) M=$(PWD)

clean:
$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
```

运行结果：

首先将编译出来的Netlink内核模块插入到系统当中（insmod netlink_test.ko）可以看到如下：
```bash
[root@localhost nt_2nd]# insmod netlink_test.ko
[root@localhost nt_2nd]# dmesg
[25024.276345] test_netlink_init
```
接着运行应用程序：./a.out
```c
[root@localhost nt_2nd]# ./a.out
send kernel:hello netlink!!
from kernel:hello users!!!
[root@localhost nt_2nd]# dmesg
[25024.276345] test_netlink_init
[25117.548350] kernel recv from user: hello netlink!!
[root@localhost nt_2nd]#
```
