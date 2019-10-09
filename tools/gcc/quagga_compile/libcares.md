> \# note "compile-quagga-libcares" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.10.09;  
\# Update   
\#  
  



#### 1. Error - Package requirements (libcares) were not met

```bash
dramalife@server:~/quagga-1.2.4 $ ./configure --enable-vtysh --enable-user=root --enable-group=root --enable-vty-group=root

#... ...

checking for CARES... no
configure: error: Package requirements (libcares) were not met:

No package 'libcares' found

Consider adjusting the PKG_CONFIG_PATH environment variable if you
installed software in a non-standard prefix.

Alternatively, you may set the environment variables CARES_CFLAGS
and CARES_LIBS to avoid the need to call pkg-config.
See the pkg-config man page for more details.

```

#### 2. Solve - Install c-ares(libcares)

```bash
# Download c-ares (Recommanded !)
wget https://c-ares.haxx.se/download/c-ares-1.15.0.tar.gz
# Or git Source(Create "configure" file first !)
git clone https://github.com/c-ares/c-ares.git --depth 1

# Compile
./configure
make -j4
sudo make install
```

