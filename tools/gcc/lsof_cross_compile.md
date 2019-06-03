### EXEC ERR
--------
```bash
root@localhost:~# cat /proc/cpuinfo 
processor	: 0
model name	: ARMv7 Processor rev 5 (v7l)
BogoMIPS	: 6.00
Features	: half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 idiva idivt vfpd32 lpae 
CPU implementer	: 0x41
CPU architecture: 7
CPU variant	: 0x0
CPU part	: 0xc07
CPU revision	: 5

Hardware	: Freescale i.MX6 Ultralite (Device Tree)
Revision	: 0000
Serial		: 0000000000000000
```
```bash
root@localhost:~# ./lsof77 
-sh: ./lsof77: No such file or directory
#make CC=arm-linux-gnueabi-gcc  #exec ERR
#make CC=arm-linux-gnueabihf-gcc #exec OK
```

### CROSS COMPILE ERR
--------
```bash
arm-linux-gnueabihf-gcc -o lsof dfile.o dmnt.o dnode.o dproc.o dsock.o dstore.o arg.o main.o misc.o node.o print.o proc.o store.o usage.o util.o -L./lib -llsof 
/usr/lib/gcc-cross/arm-linux-gnueabihf/4.8/../../../../arm-linux-gnueabihf/bin/ld: skipping incompatible ./lib/liblsof.a when searching for -llsof
/usr/lib/gcc-cross/arm-linux-gnueabihf/4.8/../../../../arm-linux-gnueabihf/bin/ld: cannot find -llsof
collect2: error: ld returned 1 exit status
make: *** [lsof] Error 1

#Makefile
#/lsof-4.86+dfsg.orig/Makefile
#/lsof-4.86+dfsg.orig/lib/Makefile
# or
#make CC=arm-linux-gnueabihf-gcc
```

