ubus : from openwrt17	x86_64 libc(musl)
x.out: from Ubuntu18	X86_64 libc(glibc)

### ELF
```
dramalife@server:~/note/90-operating_system/elf_process $ readelf -e ubus | grep interpreter
      [Requesting program interpreter: /lib/ld-musl-x86_64.so.1]
dramalife@server:~/note/90-operating_system/elf_process $ readelf -e backtrace_funcs.out | grep interpreter
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
```

### Libc version of OS
```
root@OpenWrt:~# /lib/libc.so 
musl libc (x86_64)
Version 1.1.19
Dynamic Program Loader
Usage: /lib/libc.so [options] [--] pathname [args]
```

### Exec
```
dramalife@server:~/build_openwrt $ ./ubus
bash: ./ubus: No such file or directory
dramalife@server:~/build_openwrt $ ldd ubus
./ubus: error while loading shared libraries: /usr/lib/x86_64-linux-gnu/libc.so: invalid ELF header
dramalife@server:~/build_openwrt $ file ubus
ubus: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib/ld-, with debug_info, not stripped
dramalife@server:~/build_openwrt $ uname -a
Linux server 4.15.0-91-generic #92-Ubuntu SMP Fri Feb 28 11:09:48 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
```

### Symbols - LIBC VERSION
```
dramalife@server:~/note/90-operating_system/elf_process $ nm backtrace_funcs.out | grep LIBC
U backtrace@@GLIBC_2.2.5
U backtrace_symbols@@GLIBC_2.2.5
w __cxa_finalize@@GLIBC_2.2.5
U exit@@GLIBC_2.2.5
U free@@GLIBC_2.2.5
U getpid@@GLIBC_2.2.5
U __libc_start_main@@GLIBC_2.2.5
U perror@@GLIBC_2.2.5
U __printf_chk@@GLIBC_2.3.4
U raise@@GLIBC_2.2.5
U signal@@GLIBC_2.2.5
U __sprintf_chk@@GLIBC_2.3.4
U __stack_chk_fail@@GLIBC_2.4
U strncmp@@GLIBC_2.2.5
U system@@GLIBC_2.2.5
dramalife@server:~/note/90-operating_system/elf_process $ nm ubus | grep LIBC
dramalife@server:~/note/90-operating_system/elf_process $ 
```
