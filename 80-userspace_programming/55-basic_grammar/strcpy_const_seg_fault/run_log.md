```bash
baohua@ubuntu:~/note/80-userspace_programming/55-basic_grammar/strcpy_const_seg_fault
$ ./a_demo.out 
Start: 0xb7fdc000
End: 0xb7fde000
Bytes: 8192
asdfghjkl 
08048000-0804a000 r-xp 00000000 08:01 403201
/home/baohua/note/80-userspace_programming/55-basic_grammar/strcpy_const_seg_fault/a_demo.out
0804a000-0804b000 r--p 00001000 08:01 403201
/home/baohua/note/80-userspace_programming/55-basic_grammar/strcpy_const_seg_fault/a_demo.out
0804b000-0804c000 rw-p 00002000 08:01 403201
/home/baohua/note/80-userspace_programming/55-basic_grammar/strcpy_const_seg_fault/a_demo.out
0804c000-0806d000 rw-p 00000000 00:00 0          [heap]
b7e06000-b7e07000 rw-p 00000000 00:00 0 
b7e07000-b7fb2000 r-xp 00000000 08:01 528625
/lib/i386-linux-gnu/libc-2.19.so
b7fb2000-b7fb4000 r--p 001aa000 08:01 528625
/lib/i386-linux-gnu/libc-2.19.so
b7fb4000-b7fb5000 rw-p 001ac000 08:01 528625
/lib/i386-linux-gnu/libc-2.19.so
b7fb5000-b7fb8000 rw-p 00000000 00:00 0 
b7fd8000-b7fda000 rw-p 00000000 00:00 0 
b7fda000-b7fdc000 r--p 00000000 00:00 0          [vvar]
b7fdc000-b7fde000 r-xp 00000000 00:00 0          [vdso]
b7fde000-b7ffe000 r-xp 00000000 08:01 528622     /lib/i386-linux-gnu/ld-2.19.so
b7ffe000-b7fff000 r--p 0001f000 08:01 528622     /lib/i386-linux-gnu/ld-2.19.so
b7fff000-b8000000 rw-p 00020000 08:01 528622     /lib/i386-linux-gnu/ld-2.19.so
bffdf000-c0000000 rw-p 00000000 00:00 0          [stack]

##############Backtrace_Start(11)#############
backtrace() returned 6 addresses
[00] ./a_demo.out() [0x80488a6]
[01] ./a_demo.out() [0x804899e]
[02] [0xb7fdccac]
[03] ./a_demo.out() [0x8048bcb]
[04] /lib/i386-linux-gnu/libc.so.6(__libc_start_main+0xf3) [0xb7e20af3]
[05] ./a_demo.out() [0x80487b1]

##############Backtrace_End__(11)#############
Segmentation fault
baohua@ubuntu:~/note/80-userspace_programming/55-basic_grammar/strcpy_const_seg_fault$
```
vdso.so
```ass
00000cac <__kernel_sigreturn>:                                                                                                                                                        
cac:   58                      pop    %eax		/* cac */
cad:   b8 77 00 00 00          mov    $0x77,%eax
cb2:   cd 80                   int    $0x80
cb4:   90                      nop 
cb5:   8d 76 00                lea    0x0(%esi),%esi

```


