> \# note "kernel-programming" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.09.10;  
\# Update   
\#  
  

### 0. Content

[1. tiny_fs](/81-kernel_programming/device_drivers/tiny_fs)  
[2. kernel changelog - CURRENT_TIME](/81-kernel_programming/tips/kernel_api_change_CURRENT_TIME.md)
[3. linux-headers](/81-kernel_programming/tips/modules_related/linux_headers_create.txt)
[4. modules : vermagic & srcversion](/81-kernel_programming/tips/modules_related/vermagic_srcversion_modinfo.md)


### 1. Preparing

#### 1.1 Install sanitised kernel headers

```bash
linux $ make help | grep headers
headers_install - Install sanitised kernel headers to INSTALL_HDR_PATH

$ make headers_install
```

#### 1.2 sudo apt-get install linux-source-5.0.0

```bash
sudo apt-get install linux-source-5.0.0
```


