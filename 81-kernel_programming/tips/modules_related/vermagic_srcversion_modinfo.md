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
  

root@Lenovo:~/linux-source-5.0.0# cat include/config/kernel.release
5.0.21

root@Lenovo:~/linux-source-5.0.0# cat Makefile | grep kernel.release
# Read KERNELRELEASE from include/config/kernel.release (if it exists)
KERNELRELEASE = $(shell cat include/config/kernel.release 2> /dev/null)
filechk_kernel.release = \
# Store (new) KERNELRELEASE string in include/config/kernel.release
include/config/kernel.release: $(srctree)/Makefile FORCE
	$(call filechk,kernel.release)
prepare3: include/config/kernel.release
include/generated/utsrelease.h: include/config/kernel.release FORCE
%pkg: include/config/kernel.release FORCE

