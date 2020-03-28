## 0 Needed
- the prog produce core file
- the core file

## 1 Key words
- strip;

```
 $ ./a_demo_strip.out seg
 $ gdb a_demo.out core-a_demo_strip.ou-5741-1585300909
```

## 2 GDB
### 2.1 gdb-backtrace - using not stripped program
```
(gdb) bt
#0  0x0000561812cb5871 in sample_segment_err1 ()
#1  0x0000561812cb5935 in main ()
```
### 2.2 gdb-backtrace - using stripped program
```
(gdb) bt
#0  0x0000561812cb5871 in ?? ()
#1  0x0000561812cb5935 in ?? ()
#2  0x00007fe507525b97 in __libc_start_main (main=0x561812cb58d6, argc=2, argv=0x7fff46b37728, init=<optimized out>, fini=<optimized out>, 
    rtld_fini=<optimized out>, stack_end=0x7fff46b37718) at ../csu/libc-start.c:310
#3  0x0000561812cb577a in ?? ()
```

## 3. Disassemble
```bash
 $ objdump -d a_demo.out > notstrip.ass
 $ objdump -d a_demo_strip.out > stripped.ass
```
search 0x0000561812cb5871 

### 3.1 disassemble - not stripped program
```ass
0000000000000850 <frame_dummy>:
850:   55                      push   %rbp
851:   48 89 e5                mov    %rsp,%rbp
854:   5d                      pop    %rbp
855:   e9 66 ff ff ff          jmpq   7c0 <register_tm_clones>

000000000000085a <sample_segment_err1>:
85a:   55                      push   %rbp
85b:   48 89 e5                mov    %rsp,%rbp
85e:   c7 45 f4 00 00 00 00    movl   $0x0,-0xc(%rbp)
865:   48 c7 45 f8 00 00 00    movq   $0x0,-0x8(%rbp)
86c:   00
86d:   48 8b 45 f8             mov    -0x8(%rbp),%rax
871:   c7 00 01 00 00 00       movl   $0x1,(%rax)
877:   48 8b 45 f8             mov    -0x8(%rbp),%rax
87b:   48 8d 50 04             lea    0x4(%rax),%rdx
87f:   48 89 55 f8             mov    %rdx,-0x8(%rbp)
883:   8b 00                   mov    (%rax),%eax
885:   89 45 f4                mov    %eax,-0xc(%rbp)
888:   8b 45 f4                mov    -0xc(%rbp),%eax
88b:   5d                      pop    %rbp
88c:   c3                      retq

000000000000088d <sample_syscall_kill1>:
88d:   55                      push   %rbp
88e:   48 89 e5                mov    %rsp,%rbp
891:   48 8d 3d e0 01 00 00    lea    0x1e0(%rip),%rdi        # a78 <_IO_stdin_used+0x8>
898:   e8 8b fe ff ff          callq  728 <.plt.got+0x8>
89d:   b8 00 00 00 00          mov    $0x0,%eax
8a2:   5d                      pop    %rbp
8a3:   c3                      retq
```

### 3.2 disassemble - stripped program
```ass
850:   55                      push   %rbp
851:   48 89 e5                mov    %rsp,%rbp
854:   5d                      pop    %rbp
855:   e9 66 ff ff ff          jmpq   7c0 <_init@@Base+0xd0>
85a:   55                      push   %rbp
85b:   48 89 e5                mov    %rsp,%rbp
85e:   c7 45 f4 00 00 00 00    movl   $0x0,-0xc(%rbp)
865:   48 c7 45 f8 00 00 00    movq   $0x0,-0x8(%rbp)
86c:   00
86d:   48 8b 45 f8             mov    -0x8(%rbp),%rax
871:   c7 00 01 00 00 00       movl   $0x1,(%rax)
877:   48 8b 45 f8             mov    -0x8(%rbp),%rax
87b:   48 8d 50 04             lea    0x4(%rax),%rdx
87f:   48 89 55 f8             mov    %rdx,-0x8(%rbp)
883:   8b 00                   mov    (%rax),%eax
885:   89 45 f4                mov    %eax,-0xc(%rbp)
888:   8b 45 f4                mov    -0xc(%rbp),%eax
88b:   5d                      pop    %rbp
88c:   c3                      retq
88d:   55                      push   %rbp
88e:   48 89 e5                mov    %rsp,%rbp
891:   48 8d 3d e0 01 00 00    lea    0x1e0(%rip),%rdi        # a78 <_fini@@Base+0x14>
898:   e8 8b fe ff ff          callq  728 <_init@@Base+0x38>
89d:   b8 00 00 00 00          mov    $0x0,%eax
8a2:   5d                      pop    %rbp
8a3:   c3                      retq
```

