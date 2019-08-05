### OVERVIEW
```
LIBC_VERSION : libuClibc-0.9.30.so

CPU_INFO : 
system type		: Atheros AR934x
processor		: 0
cpu model		: MIPS 74Kc V4.12
BogoMIPS		: 279.55
wait instruction	: yes
microsecond timers	: yes
tlb_entries		: 32
extra interrupt vector	: yes
hardware watchpoint	: yes, count: 4, address/irw mask: [0x0000, 0x0ff8,
0x0783, 0x0f08]
ASEs implemented	: mips16 dsp
shadow register sets	: 1
core			: 0
VCED exceptions		: not available
VCEI exceptions		: not available

KERNEL_VER : Linux host 2.6.31 #51 Mon Aug 5 00:17:06 PDT 2019 mips GNU/Linux
```

### IMPROVE
quagga-1.2.4/lib/log.c

```c
/* Wrapper around strerror to handle case where it returns NULL. */
const char *
safe_strerror(int errnum)
{
	const char *s = strerror(errnum);                                                                                                                         
	return (s != NULL) ? s : "Unknown error";
}

```

### ERROR
strerror(17),return NULL !!!

In glibc never return NULL.()

