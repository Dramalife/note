> \# note "kernel modules insmod" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.09.14;  
\# Update   
\#  
  

Insert module that compiled with kernel source tree which downloaded from kernel.org   into   a running distribute linux.  

### 1. Background

```bash
dramalife@Lenovo:~/linux-5.0$ gcc --version
gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
Copyright (C) 2017 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

###################################################################################

dramalife@Lenovo:~/linux-5.0$ bash --version
GNU bash, version 4.4.20(1)-release (x86_64-pc-linux-gnu)
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>

This is free software; you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

###################################################################################

dramalife@Lenovo:~/linux-5.0$ uname -a
Linux Lenovo 5.0.0-27-generic #28~18.04.1-Ubuntu SMP Thu Aug 22 03:00:32 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux

###################################################################################

dramalife@Lenovo:~/linux-5.0$ make --version
GNU Make 4.1
Built for x86_64-pc-linux-gnu
Copyright (C) 1988-2014 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

###################################################################################

dramalife@Lenovo:~/linux-5.0$ cat ./include/generated/uapi/linux/version.h
\#define LINUX_VERSION_CODE 327680
\#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))

###################################################################################

git log
commit 4246cdd591cccd67d867aa18c81451510f23b994 (HEAD -> master_fixed_fork0611copy, origin/master_fixed_fork0611copy, origin/HEAD)
Author: Dramalife(wjy) <Dramalife@live.com>
Date:   Sat Sep 14 09:27:23 2019 +0800

    [add] uname_r.txt; [mod] errors_load.md ...

###################################################################################

```


### 2. elfread_org_err.txt

```
	$(MAKE) -C /home/dramalife/linux-5.0 M=$(PWD) modules
```


### 3. elfread_pack_ok.txt

```
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
```

