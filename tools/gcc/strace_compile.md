> \# note "gcc - strace" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.06.11;  
\# Update : 2019.10.31, Add "armv8","error-m32";   
\# Update   
\#  
  

 README.md
>INSTALL-git.md		(./bootstrap)
>README-configure	(::Specifying the System Type)

./bootstrap


```
If you are _building_ compiler tools for cross-compiling, you should
use the option '--target=TYPE' to select the type of system they will
produce code for.

If you want to _use_ a cross compiler, that generates code for a
platform different from the build platform, you should specify the 
"host" platform (i.e., that on which the generated programs will
eventually be run) with '--host=TYPE'.

```

#### armv7
CC=arm-linux-gnueabihf-gcc LD=arm-linux-gnueabihf-ld RANLIB=arm-linux-gnueabihf-ranlib ./configure --host=arm-linux --target=arm-linux

#### armv8
CC=aarch64-linux-gnu-gcc LD=aarch64-linux-gnu-ld RANLIB=aarch64-linux-gnu-ranlib ./configure --host=aarch64-linux --target=aarch64-linux


#### armv8 Error:"configure: error: Cannot enable m32 personality support"
CC=aarch64-linux-gnu-gcc LD=aarch64-linux-gnu-ld RANLIB=aarch64-linux-gnu-ranlib ./configure --host=aarch64-linux --target=aarch64-linux --enable-mpers=no

