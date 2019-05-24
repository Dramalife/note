#! /bin/bash

# error: vtysh needs libreadline but was not found and usable on your system.
sudo apt-get install libreadline-dev

# missing: line 81: aclocal-1.15: command not found
# libtool: Version mismatch error.  This is libtool 2.4.2 Debian-2.4.2-1.7ubuntu1, but the
# libtool: definition of this LT_INIT comes from libtool 2.4.6.
autoreconf --force --install

# install&runquagga
./configure --enable-vtysh --enable-user=root --enable-group=root --enable-vty-group=root
make
sudo make install

# zebra: error while loading shared libraries: libzebra.so.1: cannot open shared object file: No such file or directory
#sudo cp /usr/local/lib/libzebra.so.1 /lib

sudo zebra -d

# /etc/services    #zebra  2601/tcp  #zebra vty 
telnet 127.0.0.1 2601
# usr:admin passwd:zebra,,,enablepasswd:zebra

#$	### libtool
#$	```bash
#$	# libtool: Version mismatch error. This is libtool 2.4.2 , but the
#$	# libtool: definition of this LT_INIT comes from libtool 2.4.6.
#$	# libtool: You should recreate aclocal.m4 with macros from libtool 2.4.2 
#$	# libtool: and run autoconf again
#$	#  
#$	# 运行命令
#$	# autoreconf --force --install
#$	# ./configure
#$	# make
#$	#  
#$	# 如果没有生效
#$	# make maintainer-clean 清理干净后，在运行上面的命令
#$	# 原文：https://blog.csdn.net/github_29989383/article/details/51886234 
#$	```
