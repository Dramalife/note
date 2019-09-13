> \# note "apt-get source" related file  
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
  


#### 1. source.list

make sure your "/etc/apt/sources.list" contains "deb-src":

```
deb http://httpredir.debian.org/debian stretch main contrib non-free
deb-src http://httpredir.debian.org/debian stretch main contrib non-free

deb http://httpredir.debian.org/debian stretch-updates main contrib non-free
deb-src http://httpredir.debian.org/debian stretch-updates main contrib non-free


deb http://security.debian.org/ stretch/updates main contrib non-free
deb-src http://security.debian.org/ stretch/updates main contrib non-free
```

#### 2. apt-get source

sample : get "sl" source code.
```bash
root@orangepizero:~/note/tools/apt-get/test# apt-get source sl
Reading package lists... Done
Need to get 21.1 kB of source archives.
Get:1 http://cdn-fastly.deb.debian.org/debian stretch/main sl 3.03-17 (dsc) [1692 B]
Get:2 http://cdn-fastly.deb.debian.org/debian stretch/main sl 3.03-17 (tar) [3776 B]
Get:3 http://cdn-fastly.deb.debian.org/debian stretch/main sl 3.03-17 (diff) [15.6 kB]
Fetched 21.1 kB in 1s (13.1 kB/s)
dpkg-source: info: extracting sl in sl-3.03
dpkg-source: info: unpacking sl_3.03.orig.tar.gz
dpkg-source: info: unpacking sl_3.03-17.debian.tar.gz
dpkg-source: info: applying modify_Makefile.patch
dpkg-source: info: applying remove_SIGINT.patch
dpkg-source: info: applying add_-e_option.patch
dpkg-source: info: applying apply_sl-h.patch
dpkg-source: info: applying set_curs.patch
W: Download is performed unsandboxed as root as file 'sl_3.03-17.dsc' couldn't be accessed by user '_apt'. - pkgAcquire::Run (13: Permission denied)
root@orangepizero:~/note/tools/apt-get/test# ls
sl-3.03  sl_3.03-17.debian.tar.gz  sl_3.03-17.dsc  sl_3.03.orig.tar.gz
root@orangepizero:~/note/tools/apt-get/test#
```
