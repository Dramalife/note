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
\# Update   
\#  
  


#### 1. insmod: ERROR: could not insert module tinyfs.ko: Invalid module format

**common**
```bash
$ sudo insmod tinyfs.ko
insmod: ERROR: could not insert module tinyfs.ko: Invalid module format

$ dmesg | grep tinyfs
[15794.970320] tinyfs: version magic '5.0.21 SMP mod_unload ' should be '5.0.0-27-generic SMP mod_unload '
```

##### 1.1 x86_64 linux-5.0.0

```bash
# source_code : linux-source-5.0.0
$ uname -a
Linux Lenovo 5.0.0-27-generic #28~18.04.1-Ubuntu SMP Thu Aug 22 03:00:32 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux
```

##### 1.2 armv7 linux-4.14.34
```bash
# source_code : linux-4.14.34 
$ uname -a
Linux NETAC-SERVER 4.14.34-v7+ #1110 SMP Mon Apr 16 15:18:51 BST 2018 armv7l GNU/Linux
```

#### 2. Using source code tree OR package when compiling kernel module

```bash
# Using source code tree(apt-get) when compiling kernel module.
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ make -f Makefile_source
make -C /usr/src/linux-source-5.0.0/linux-source-5.0.0 M=/home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol modules
make[1]: Entering directory '/usr/src/linux-source-5.0.0/linux-source-5.0.0'
  CC [M]  /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.mod.o
  LD [M]  /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
make[1]: Leaving directory '/usr/src/linux-source-5.0.0/linux-source-5.0.0'
# Actually can`t insmod : "Invalid module format".
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
depends:
retpoline:      Y
name:           tinyfs
vermagic:       5.0.21 SMP mod_unload modversions

# Using package when compiling kernel module.
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ make
make -C /lib/modules/5.0.0-27-generic/build M=/home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol modules
make[1]: Entering directory '/usr/src/linux-headers-5.0.0-27-generic'
  CC [M]  /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o
  Building modules, stage 2.
  MODPOST 1 modules
  CC      /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.mod.o
  LD [M]  /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
make[1]: Leaving directory '/usr/src/linux-headers-5.0.0-27-generic'
# Insmod successfully.
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
srcversion:     8FCD169E684F95FE9BF705E
depends:
retpoline:      Y
name:           tinyfs
vermagic:       5.0.0-27-generic SMP mod_unload

# Using linux source tree(kernel.org) when compiling kernel module.
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
# after change kernel.release, but print "Invalid module format" too.
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
depends:
retpoline:      Y
name:           tinyfs
vermagic:       5.0.0-27-generic SMP mod_unload
# after enable "[] Source checksum for all modules", but still can not load.
dramalife@Lenovo:~/note/81-kernel_programming/fs/tiny_fs_symbol$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
srcversion:     8FCD169E684F95FE9BF705E
depends:
retpoline:      Y
name:           tinyfs
vermagic:       5.0.0-27-generic SMP mod_unload


```

