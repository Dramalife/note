> \# note "kernel modules" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.09.13;  
\# Update : 2019.09.15, Refactoring : Theme of apt_source , org_source and linux-headers ; 
\# Update   
\#  
  

#### 1. Background

|SourceName		|FromWhere				|||
|--|--|--|--|
|linux-source-5.0.0(apt_source)	|apt-get install linux-source-5.0.0	|||
|linux-5.0(org_source)		|wget https://mirrors.edge.kernel.org/pub/linux/kernel/v5.x/linux-5.0.tar.xz	|||
|linux-headers(linux-headers)	|(local)/lib/modules/5.0.0-27-generic/build	|||

```bash
$ uname -a
Linux Lenovo 5.0.0-27-generic #28~18.04.1-Ubuntu SMP Thu Aug 22 03:00:32 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
```

```bash
$ sudo insmod tinyfs.ko
insmod: ERROR: could not insert module tinyfs.ko: Invalid module format

$ dmesg | grep tinyfs
[15794.970320] tinyfs: version magic '5.0.21 SMP mod_unload ' should be '5.0.0-27-generic SMP mod_unload '
```


### 2. Using source code tree(org_source) , package(apt_source)  OR  linux-headers when compiling kernel module

#### 2.1 Using source code tree(apt_source) when compiling kernel module.

```bash
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ make -f Makefile_source
make -C /usr/src/linux-source-5.0.0/linux-source-5.0.0 M=/home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol modules
make[1]: Entering directory '/usr/src/linux-source-5.0.0/linux-source-5.0.0'
  CC [M]  /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.mod.o
  LD [M]  /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
make[1]: Leaving directory '/usr/src/linux-source-5.0.0/linux-source-5.0.0'
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
depends:
retpoline:      Y
name:           tinyfs
vermagic:       5.0.21 SMP mod_unload modversions
$ sudo insmod tinyfs.ko
insmod: ERROR: could not insert module tinyfs.ko: Invalid module format
$ dmesg grep "tinyfs"
[154214.279676] tinyfs: version magic '5.0.21 SMP mod_unload ' should be '5.0.0-27-generic SMP mod_unload '

# Actually can`t insmod : "Invalid module format".
# vermagic error !!!
# Why 5.0.21 ???
```

#### 2.2 Using linux-headers(/lib/modules/5.0.0-27-generic/build) when compiling kernel module.

```bash
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ make
make -C /lib/modules/5.0.0-27-generic/build M=/home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol modules
make[1]: Entering directory '/usr/src/linux-headers-5.0.0-27-generic'
  CC [M]  /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.mod.o
  LD [M]  /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
make[1]: Leaving directory '/usr/src/linux-headers-5.0.0-27-generic'

dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
srcversion:     8FCD169E684F95FE9BF705E
depends:
retpoline:      Y
name:           tinyfs
vermagic:       5.0.0-27-generic SMP mod_unload

# Insmod successfully.
```

#### 2.3 Using linux source tree(kernel.org)(org_source) when compiling kernel module.

```bash
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ make -f Makefile_org
make -C /home/dramalife/linux-5.0 M=/home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol modules
make[1]: Entering directory '/home/dramalife/linux-5.0'
  CC [M]  /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.mod.o
  LD [M]  /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
make[1]: Leaving directory '/home/dramalife/linux-5.0'

dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
depends:
retpoline:      Y
name:           tinyfs
vermagic:       5.0.0 SMP mod_unload
# 	vermagic is "5.0.0", error.

# after change kernel.release, but print "Invalid module format" too.
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
depends:
retpoline:      Y
name:           tinyfs
vermagic:       5.0.0-27-generic SMP mod_unload
# 	srcversion is not set ?

# after enable "[] Source checksum for all modules", but still can not load.
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
srcversion:     8FCD169E684F95FE9BF705E
depends:
retpoline:      Y
name:           tinyfs
vermagic:       5.0.0-27-generic SMP mod_unload
# Still error :
#	# insmod tinyfs.ko
#	insmod: ERROR: could not insert module tinyfs.ko: Invalid module format
#	# dmesg |||
#	[101542.807625] module: x86/modules: Skipping invalid relocation target, existing value is nonzero for type 1, loc 000000004f3c889e, val ffffffffc1005710

# Try again(vermagic and srcversion of tihs module are both same as the module
# compiled with linux-keaders, section of ELF are different!! )
$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
srcversion:     8FCD169E684F95FE9BF705E
depends:
retpoline:      Y
name:           tinyfs
vermagic:       5.0.0-27-generic SMP mod_unload
$ sudo insmod tinyfs.ko
insmod: ERROR: could not insert module tinyfs.ko: Invalid module format
$ dmesg |||
[153280.484283] module: x86/modules: Skipping invalid relocation target, existing value is nonzero for type 1, loc 000000004f3c889e, val ffffffffc1005710
```

