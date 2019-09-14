> \# note "kernel modules - modinfo" related file  
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
  

### 1. What does it like (see "srcversion" and "vermagic" first)

```bash
$ uname -a
Linux Lenovo 5.0.0-27-generic #28~18.04.1-Ubuntu SMP Thu Aug 22 03:00:32 UTC 2019 x86_64 x86_64 x86_64 GNU/Linux


$ modinfo tinyfs.ko
filename:       /home/dramalife/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
srcversion:     8FCD169E684F95FE9BF705E
depends:        
retpoline:      Y
name:           tinyfs
vermagic:       5.0.0-27-generic SMP mod_unload 
```

### 2. How to add "srcversion" to your modules ?

changedir to your "kernel source tree", and run "make menuconfig",
then enable "[*]   Source checksum for all modules" options.



### 3. How to change vermagic ?

#### 3.1 What is vermagic 

vermagic is saved in section ".modinfo" of ELF file.
String "vermagic" coming from VERMAGIC_STRING that defined at "include/linux/vermagic.h" 
```
					|
					|
				   ----------------------------------------------------------------------
(include/linux/vermagic.h)--------| VERMAGIC_STRING |                                                   
				  | #define VERMAGIC_STRING \                   
				  |     UTS_RELEASE " " \ ----<KERNELRELEASE>----(include/config/kernel.release) 
				  |     MODULE_VERMAGIC_SMP MODULE_VERMAGIC_PREEMPT \       
				  |     MODULE_VERMAGIC_MODULE_UNLOAD MODULE_VERMAGIC_MODVERSIONS \
				  |     MODULE_ARCH_VERMAGICLINE                                    
				  ``````````````````````````````````````````````````````````````````````
					|
					|
			   -------------------------------
(kernel/module.c)---------| static const char vermagic[] |
			  ```````````````````````````````
					|
					|
				    -----------
(YOUR_MODULE.ko)-------------------| .modinfo |
				   ```````````
					|
					|
			      --------------------------------------------------
(command - modinfo)----------| vermagic:       5.0.0-27-generic SMP mod_unload |
			     ``````````````````````````````````````````````````
```

#### 3.2 "kernel.release" that was auto generated   should be same as   result of command "uname -r"

```bash
$ cat include/config/kernel.release 
5.0.0-27-generic

$ uname -r
5.0.0-27-generic
```

