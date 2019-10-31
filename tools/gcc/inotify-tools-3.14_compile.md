> \# note "inotify-tools" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.10.31, SOURCE_CODE_VERSION:inotify-tools-3.14;  
\# Update   
\#  
  


### 1. Prepare

version : inotify-tools-3.14  
```
checking build system type... x86_64-unknown-linux-gnu
checking host system type... Invalid configuration `aarch64-linux-gnu': machine `aarch64' not recognized
configure: error: /bin/bash ./config.sub aarch64-linux-gnu failed
```
```
find . -name "config.guess"
find . -name "config.sub"
cp ~/open_source_code/tools_note/strace5_syscall_trace/config.guess .
cp ~/open_source_code/tools_note/strace5_syscall_trace/config.sub .
```


### 2. Config && Make

#### 2.1 Config && make

```bash
./configure --prefix=/tmp/wjy --host=aarch64-linux
make CC=aarch64-linux-gnu-gcc
```

#### 2.2 Config && make (Recommanded !)

```bash
./configure --prefix=/tmp/wjy --host=aarch64-linux-gnu
make
```

### 3. Install

make install

$ file /tmp/wjy/bin/inotifywait 
/tmp/bin/inotifywait: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/l, for GNU/Linux 3.2.0, BuildID[sha1]=6bf640f09643edba377689b6ff670bed918f7e97, with debug_info, not stripped


