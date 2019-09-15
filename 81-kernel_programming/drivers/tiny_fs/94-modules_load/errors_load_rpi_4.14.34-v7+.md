> \# note "kernel modules insert" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.09.15;  
\# Update   
\#  
  


### 1. Overview

After change "vermagic" to be same as result of command "uname -r" and add "srcversion" to module.  

```bash
root@NETAC-SERVER:~/note/81-kernel_programming/fs/tiny_fs_symbol # make
make -C /lib/modules/4.14.34-v7+/build M=/root/note/81-kernel_programming/fs/tiny_fs_symbol modules
make[1]: Entering directory '/sharedfolders/ug2t-root/source_code/linux-4.14.34'
CC [M]  /root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o
Building modules, stage 2.
MODPOST 1 modules
CC      /root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.mod.o
LD [M]  /root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
make[1]: Leaving directory '/sharedfolders/ug2t-root/source_code/linux-4.14.34'

root@NETAC-SERVER:~/note/81-kernel_programming/fs/tiny_fs_symbol # modinfo tinyfs.ko
filename:       /root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
srcversion:     336E4298B6FDD36B91FB7BC
depends:        
name:           tinyfs
vermagic:       4.14.34-v7+ SMP mod_unload ARMv7 p2v8 

root@NETAC-SERVER:~/note/81-kernel_programming/fs/tiny_fs_symbol # sudo insmod tinyfs.ko
insmod: ERROR: could not insert module tinyfs.ko: Invalid module format

root@NETAC-SERVER:~/note/81-kernel_programming/fs/tiny_fs_symbol # dmesg | grep tinyfs
root@NETAC-SERVER:~/note/81-kernel_programming/fs/tiny_fs_symbol # 
```

