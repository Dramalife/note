/*
 * $ uname -a
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux
 * $ gcc --version
 * gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <setjmp.h>
#include <errno.h>
#include <linux/if.h>

#define PACKET_SIZE     4096
#define MAX_WAIT_TIME   5
#define MAX_NO_PACKETS  100000

#define IFNAME_MAXLEN	30 /* for example, on device running openmediavault, name of eth is "enxb827ebf521d8" */

static int datalen = 56;
struct badping
{
	char sendpacket[PACKET_SIZE];
	char arg_ifname[IFNAME_MAXLEN];
	char arg_addr[20];
	int sockfd;
	int nsend;
	struct sockaddr_in dest_addr;
	pid_t pid;
	pthread_t send_thread;
};

unsigned short cal_chksum(unsigned short *addr, int len, struct badping *bdp);
static int pack(int pack_no,struct badping *bdp);
void send_packet(struct badping *bdp);
void tv_sub(struct timeval *out, struct timeval *in);
void main_b(void);
int main_c(void *arg);
void print(struct badping *bdp);
int stop = 0;

/*校验和算法*/
unsigned short cal_chksum(unsigned short *addr, int len, struct badping *bdp)
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = addr;
	unsigned short answer = 0;

	/*把ICMP报头二进制数据以2字节为单位累加起来 */
	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}
	/*若ICMP报头为奇数个字节，会剩下最后一字节。把最后一个字节视为一个2字节数据的高字节，这个2字节数据的低字节为0，继续累加 */
	if (nleft == 1) {
		*(unsigned char *)(&answer) = *(unsigned char *)w;
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return answer;
}

/*设置ICMP报头*/
static int pack(int pack_no,struct badping *bdp)
{
	int i, packsize;
	struct icmp *icmp;
	struct timeval *tval;

	icmp = (struct icmp *)bdp->sendpacket;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_seq = pack_no;
	icmp->icmp_id = bdp->pid;
	packsize = 8 + datalen;
	tval = (struct timeval *)icmp->icmp_data;
	gettimeofday(tval, NULL);	/*记录发送时间 */
	icmp->icmp_cksum = cal_chksum((unsigned short *)icmp, packsize, bdp);	/*校验算法 */

	return packsize;
}

/*发送三个ICMP报文*/
void send_packet(struct badping *bdp)
{
	int packetsize;
	while (1){
		bdp->nsend++;
		packetsize = pack(bdp->nsend, bdp);	/*设置ICMP报头 */
		if (sendto(bdp->sockfd, bdp->sendpacket, packetsize, 0,
					(struct sockaddr *)&(bdp->dest_addr),
					sizeof(bdp->dest_addr)) < 0)
		{
			//perror("sendto error");
			continue;
		}
	}
}

char add[20];
char nam[IFNAME_MAXLEN];
int main(int argc, char *argv[])
{
	int num;
	if (argc < 4)
	{
		printf("usage:sudo %s ip if thread_num\n", argv[0]);
		exit(1);
	}
	strcpy(nam, argv[2]);
	strcpy(add, argv[1]);
	if(NULL != argv[3])
	{
		num = atoi(argv[3]);
	}
	else
	{
		num = 5;
	}
	printf("all:%d  \n",num);

	while(num--)
	{
		main_b();
	}
	while(1)
	{

	}
	return 0;
}

void print(struct badping *bdp)
{
	while(1)
	{
#if (defined __SIZEOF_POINTER__) && (__SIZEOF_POINTER__ == 4)/* 32 bit */
		printf("thread%d,%d packets transmitted\n",pthread_self(), bdp->nsend);
#elif (defined __SIZEOF_POINTER__) && (__SIZEOF_POINTER__ == 8)/* 64 bit */
		printf("thread%lu,%d packets transmitted\n",pthread_self(), bdp->nsend);
#endif
		sleep(5);
	}
	return;
}

void main_b(void)
{
	struct badping *bdp = malloc(sizeof(struct badping));
	bdp->nsend = 0;
	strcpy(bdp->arg_ifname, nam);
	strcpy(bdp->arg_addr, add);
	pthread_t trd;
	if (pthread_create(&trd, NULL, (void *)main_c, bdp) != 0)
	{
		perror("thread create");
	}


	pthread_t trd2;
	if (pthread_create(&trd2, NULL, (void *)print, bdp) != 0)
	{
		perror("thread create");
	}

	return;
}

int main_c(void *arg)
{
	struct badping *bdp = (struct badping *)arg;

	struct hostent *host;
	struct protoent *protocol;
	unsigned long inaddr = 0l;
	int waittime = MAX_WAIT_TIME;
	int size = 50 * 1024;
	struct ifreq interface;

	if ((protocol = getprotobyname("icmp")) == NULL) {
		perror("getprotobyname");
		exit(1);
	}
	/*生成使用ICMP的原始套接字,这种套接字只有root才能生成 */
	if ((bdp->sockfd = socket(AF_INET, SOCK_RAW, protocol->p_proto)) < 0) {
		perror("socket error, pls run sudo");
		exit(1);
	}
	printf("ifname:%s\n", bdp->arg_ifname);
	strncpy(interface.ifr_ifrn.ifrn_name, bdp->arg_ifname, IFNAMSIZ);
	if (setsockopt
			(bdp->sockfd, SOL_SOCKET, SO_BINDTODEVICE, (char *)&interface,
			 sizeof(interface)) < 0) {
		printf("SO_BINDTODEVICE failed");
		exit(1);
	}

	/* 回收root权限,设置当前用户权限 */
	setuid(getuid());
	/*扩大套接字接收缓冲区到50K这样做主要为了减小接收缓冲区溢出的
	  的可能性,若无意中ping一个广播地址或多播地址,将会引来大量应答 */
	setsockopt(bdp->sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
	bzero(&(bdp->dest_addr), sizeof(bdp->dest_addr));
	bdp->dest_addr.sin_family = AF_INET;
	/*判断是主机名还是ip地址 */
	if (inaddr = inet_addr(bdp->arg_addr) == INADDR_NONE) {
		if ((host = gethostbyname(bdp->arg_addr)) == NULL) {	/*是主机名 */
			perror("gethostbyname error");
			exit(1);
		}
		memcpy((char *)&(bdp->dest_addr).sin_addr, host->h_addr,
				host->h_length);
	} else {		/*是ip地址 */
		struct in_addr ip_addr;
		ip_addr.s_addr = inet_addr(bdp->arg_addr);
		bdp->dest_addr.sin_addr = ip_addr;
	}
	bdp->pid = getpid();/*获取main的进程id,用于设置ICMP的标志符 */
	printf("ping %s(%s): %d bytes data in ICMP packets.\n", bdp->arg_addr,
			inet_ntoa(bdp->dest_addr.sin_addr), datalen);
	send_packet(bdp);/*发送所有ICMP报文 */
	return 0;
	free(bdp);
}

/*两个timeval结构相减*/
void tv_sub(struct timeval *out, struct timeval *in)
{
	if ((out->tv_usec -= in->tv_usec) < 0) {
		--out->tv_sec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}
