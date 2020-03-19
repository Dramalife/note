### Error1
#### Error msg
```
/usr/bin/arm-linux-gnueabihf-ld: znl.o: undefined reference to symbol 'socket@@GLIBC_2.4'
//lib/arm-linux-gnueabihf/libc.so.6: error adding symbols: DSO missing from command line
collect2: error: ld returned 1 exit status
Makefile:475: recipe for target 'nhrpd' failed
make[2]: *** [nhrpd] Error 1
make[2]: Leaving directory '/root/build_quagga/quagga-1.2.4/nhrpd'
Makefile:467: recipe for target 'all-recursive' failed
make[1]: *** [all-recursive] Error 1
make[1]: Leaving directory '/root/build_quagga/quagga-1.2.4'
Makefile:399: recipe for target 'all' failed
make: *** [all] Error 2
```
#### libc version
```
# /lib/arm-linux-gnueabihf/libc.so.6
GNU C Library (Ubuntu GLIBC 2.27-3ubuntu1) stable release version 2.27.
Copyright (C) 2018 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE.
Compiled by GNU CC version 7.3.0.
libc ABIs: UNIQUE
For bug reporting instructions, please see:
<https://bugs.launchpad.net/ubuntu/+source/glibc/+bugs>.
```
#### avoid error
Disable nhrpd
```
./configure --enable-vtysh --enable-user=root --enable-group=root --enable-vty-group=root  --disable-nhrpd
```
