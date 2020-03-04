### ERR1

```
cc -DDEBUG_PPPD -DTRUST_PPPD_TO_DIE -Os -Wall -Wextra -DSANITY -DLINUX -I./linux/include/ -DUSE_KERNEL -DIP_ALLOCATION -c contrib/pfc.c
contrib/pfc.c:14:23: fatal error: pcap-bpf.h: No such file or directory
# include <pcap-bpf.h>
^
compilation terminated.
Makefile:130: recipe for target 'pfc' failed
make: *** [pfc] Error 1
```
need libpcap
see libpcap_compile.md

