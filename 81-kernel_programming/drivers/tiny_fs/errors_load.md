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

