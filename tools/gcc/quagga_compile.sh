#! /bin/bash

# error: vtysh needs libreadline but was not found and usable on your system.
sudo apt-get install libreadline-dev

# missing: line 81: aclocal-1.15: command not found
make maintainer-clean
autoreconf --force --install

# install&runquagga
./configure --enable-vtysh --enable-user=root --enable-group=root --enable-vty-group=root
make
sudo make install
sudo zebra -d
telnet 127.0.0.1 2601

#$	### libtool
#$	```bash
#$	# libtool: Version mismatch error. This is libtool 2.4.2 , but the
#$	# libtool: definition of this LT_INIT comes from libtool 2.4.6.
#$	# libtool: You should recreate aclocal.m4 with macros from libtool 2.4.2 
#$	# libtool: and run autoconf again
#$	#  
#$	# ��������
#$	# autoreconf --force --install
#$	# ./configure
#$	# make
#$	#  
#$	# ���û����Ч
#$	# make maintainer-clean ����ɾ������������������
#$	# ԭ�ģ�https://blog.csdn.net/github_29989383/article/details/51886234 
#$	```
