    #include "stdio.h"
    #include "stdlib.h"
    #include "string.h"

    #include "net/if.h"
    #include "arpa/inet.h"
    #include "linux/sockios.h"

    int main(int argc,char *argv[])
    {
        char *dev = "eth0";
        char *ip = "192.168.1.252";

        struct ifreq ifr;
        if( strlen(dev) >= IFNAMSIZ)
            printf("device name error.\n"), exit(0);
        else
            strcpy( ifr.ifr_name, dev);

        int sockfd = socket(AF_INET,SOCK_DGRAM,0);

        //get inet addr
        if( ioctl( sockfd, SIOCGIFADDR, &ifr) == -1)
            printf("ioctl error.\n"), exit(0);

        struct sockaddr_in *addr = (struct sockaddr_in *)&(ifr.ifr_addr);
        char * address = inet_ntoa(addr->sin_addr);

        printf("current inet addr: %s\n",address);

        //set inet addr
        struct sockaddr_in *p = (struct sockaddr_in *)&(ifr.ifr_addr);

        p->sin_family = AF_INET;
        inet_aton( ip, &(p->sin_addr));

        if( ioctl( sockfd, SIOCSIFADDR, &ifr) == -1)
         printf("ioctl error.\n"), exit(0);
        else
            printf("change inet addr to: %s\n", ip);

        //any OS need active dev.
        /*ifr.ifr_flags |= IFF_UP;
        if( ioctl( sockfd, SIOCSIFFLAGS, &ifr) == -1)
            printf("active fault.\n"), exit(0);
        else
            printf("%s[%s] is working...\n", dev, ip);
        */

        close(sockfd);
        exit(1);
        //end
    }
/*
屏蔽的代码用于设置IP后, 激活新设置. 多数系统不需要这步操作.
而且这步仅作演示. 真实使用的时候, 至少应该
1. 获取当前ifr.ifr_flags
2. ifr.ifr_flags |= IFF_UP;
*/
