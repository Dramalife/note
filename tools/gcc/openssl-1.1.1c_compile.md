> \# note compile openssl related file
\# Copyright (C) 2019 Dramalife@live.com
\# 
\# This file is part of [note](https://github.com/Dramalife/note.git)
\# 
\# note is distributed in the hope that it will be useful, but
\# WITHOUT ANY WARRANTY; without even the implied warranty of
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


> Ref URL :
	[-D_GNU_SOURCE] : https://dazhilao.iteye.com/blog/791899
	[./libcrypto.so: undefined reference to]
					: https://blog.csdn.net/artyoung0421/article/details/83017033

Version : openssl-1.1.1c
Source : https://www.openssl.org/source/openssl-1.1.1c.tar.gz

### 1. LOCAL COMPILE

```bash
# $ gcc --version
# gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
# Copyright (C) 2015 Free Software Foundation, Inc.
# This is free software; see the source for copying conditions.  There is NO
# warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# $ uname -a
# Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux

./config
make
```

### 2. CROSS COMPILE
#### 2.1 ERROR 1	‘PTHREAD_MUTEX_RECURSIVE’ undecleared

```bash
# Edit Makefile
vi Makefile
```

```diff
-CFLAGS=-Wall -O3 -fomit-frame-pointer
-CXXFLAGS=-Wall -O3
+CFLAGS=-Wall -O3 -fomit-frame-pointer -D_GNU_SOURCE
+CXXFLAGS=-Wall -O3 -D_GNU_SOURCE
```

#### 2.2 ERROR 2 ./libcrypto.so: undefined reference to ...

```bash
./libcrypto.so: warning: gethostbyname is obsolescent, use getnameinfo() instead.
./libcrypto.so: undefined reference to `getcontext'
./libcrypto.so: undefined reference to `setcontext'
./libcrypto.so: undefined reference to `makecontext'

# no-async: 交叉编译工具链没有提供GNU C的ucontext库 
./config no-asm shared --prefix=~/openssl-1.1.1/build_arm --cross-compile-prefix=arm-linux-gnueabihf-  no-async 
```

