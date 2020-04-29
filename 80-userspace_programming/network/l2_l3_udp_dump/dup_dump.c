#include <stdio.h>
#include <sys/socket.h>//socket
#include <arpa/inet.h>//htons
#include <netinet/ether.h>//ETH_P_ALL
#include <unistd.h>//close
#include <string.h>
#include <pthread.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(int argc, char const *argv[])
{
	int fd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
	printf("fd = %d\n",fd);

	while(1)
	{	
		unsigned char buf[1500]="";
		int len = recvfrom(fd,buf,sizeof(buf),0,NULL,NULL);

		//buf格式==[6字节的目的mac][6字节的源mac][2字节的协议类型][data]
		// ifconfig-ether-f6:6b:58:90:53:be
		char src_mac[18] = "";//Mac-src
		char dst_mac[18] = "";//Mac-dest
		unsigned short type = 0;

		sprintf(dst_mac,"%02x:%02x:%02x:%02x:%02x:%02x",buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
		sprintf(src_mac,"%02x:%02x:%02x:%02x:%02x:%02x",buf[0+6],buf[1+6],buf[2+6],buf[3+6],buf[4+6],buf[5+6]);
		type = ntohs( *(unsigned short *)(buf+12));
		if(type == 0x0800)
		{
			unsigned char *ip = buf+14;
			// buf : mac frame
			//buf:***********************************
			//	^5desMac ^11srcMac ^12type
			//ip:				   ^14

			char src_ip[16]="";
			char dst_ip[16]="";
			sprintf(src_ip,"%d.%d.%d.%d",ip[12],ip[13],ip[14],ip[15]);
			sprintf(dst_ip,"%d.%d.%d.%d",ip[12+4],ip[13+4],ip[14+4],ip[15+4]);
			//buf - l2(mac)
			//ip  - l3(ip)
			//udp - l4(udp)
			if(ip[9] == 17)
			{
				// 14-mac 20-ip 8-udp 1:DATA(udp)
				if(buf[14+20+8+1]==1||buf[14+20+8+1]==2)
				{
					continue;
				}
				unsigned char *udp = buf+14+(ip[0]&0x0f)*4;// ip[0]&0x0f : header length
				unsigned short src_port  = ntohs(*(unsigned short *)udp);
				unsigned short dst_port  = ntohs(*(unsigned short *)(udp+2));

				unsigned short len = ntohs(*(unsigned short *)(udp+4));//data len

				printf("******Dump UDP PACKET!******\n");
				printf("****************************\n");
				printf("L3_type(%04x) (IP==0x0800)\n", type);
				printf("L4_type(%d) (UDP==17) \n", ip[9]);
				printf("mac_des(%s) \n", dst_mac);
				printf("mac_src(%s) \n", src_mac);
				printf("ip_src(%s) \n", src_ip);
				printf("ip_des(%s) \n", dst_ip);
				printf("port_src(%d) \n", src_port);
				printf("port_des(%d) \n", dst_port);
				printf("udp_data_len(%d) \n",len);
				char *ptr = buf+14+20+8+1;
				int index = 0;
				printf("udp_data:");
				for(;index < len; index++)
				{
					//printf("udp_data(%s) \n", buf+14+20+8+1);
					printf("0x%02x", ptr+index);
				}
				printf("\n");
				printf("****************************\n");

				fflush(stdout);

			}
		}

	}
	while(1);
	return 0;
}
