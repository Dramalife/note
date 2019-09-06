> \# note "tinyfs" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Source :  [source url](https://mp.weixin.qq.com/s/Sidfn8CZn4KxKh6xMH2uJQ)   
\# Ref : [Ref - error: ‘struct file’ has no member named ‘f_dentry’ - hn2zzzz1996](https://blog.csdn.net/hn2zzzz1996/article/details/79496282)
\# Ref : [KERNEL_VERSION](https://blog.csdn.net/whatday/article/details/98460720)  
\# Ref : [Ref - error: unknown field ‘readdir’ specified in initializer](https://blog.csdn.net/xiaominthere/article/details/17548949?utm_source=blogxgwz4)   
\# Ref :    
\# Init : 2019.09.05 ;   
\# Update   
\#  
  


### 1. USE

```bash
# insmod ./tinyfs.ko
# mount -t tinyfs none /mnt
```


### 2. ERRORs

$ uname -a
Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux

#### 2.1 ERROR1

```bash
# make > error 2>&1
make -C /lib/modules/4.0.0-040000-generic/build M=/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs modules
make[1]: Entering directory `/usr/src/linux-headers-4.0.0-040000-generic'
  CC [M]  /home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.o
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c: In function ‘tinyfs_readdir’:
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:65:31: error: ‘struct file’ has no member named ‘f_dentry’
  blk = (struct file_blk *)filp->f_dentry->d_inode->i_private;
                               ^
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c: At top level:
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:130:2: error: unknown field ‘readdir’ specified in initializer
  .readdir = tinyfs_readdir,
  ^
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:130:2: warning: initialization from incompatible pointer type [enabled by default]
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:130:2: warning: (near initialization for ‘tinyfs_dir_operations.llseek’) [enabled by default]
make[2]: *** [/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.o] Error 1
make[1]: *** [_module_/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs] Error 2
make[1]: Leaving directory `/usr/src/linux-headers-4.0.0-040000-generic'
make: *** [all] Error 2
```

#### 2.1.1  error: ‘struct file’ has no member named ‘f_dentry’

```
Linux 3.19 compat: file_inode was added

struct access f->f_dentry->d_inode was replaced by accessor function
file_inode(f)

Signed-off-by: Joerg Thalheim <joerg@higgsboson.tk>
Signed-off-by: Brian Behlendorf <behlendorf1@llnl.gov>
使用file_inode(f)替换掉f->f_dentry->d_inode.
```

#### 2.1.2  error: unknown field ‘readdir’ specified in initializer

```diff
struct file_operations
{
//...
- readdir
+ iterate
//...
};
```

