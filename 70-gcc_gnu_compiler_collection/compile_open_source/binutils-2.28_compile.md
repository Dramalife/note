```
binutils-2.28 used by crosstool-NG (gcc-6.3.0)
```

#### 1. Download && Configure && Make && Install

##### native
```bash
# "NOTE/tools/00-source_code_of_tools/wget-binutils-2.28.sh"
./configure
make -j4
sudo make install
```

##### cross (statically linked)
```bash
./configure --host=arm-linux-gnueabihf --disable-werror --prefix=/usr LDFLAGS="--static -s"
make

## GCC Version
## arm-linux-gnueabihf-gcc (Linaro GCC 7.4-2019.02) 7.4.1 20181213 [linaro-7.4-2019.02 revision 56ec6f6b99cc167ff0c2f8e1a2eed33b1edc85d4]
## Copyright (C) 2017 Free Software Foundation, Inc.
## This is free software; see the source for copying conditions.  There is NO
## warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
