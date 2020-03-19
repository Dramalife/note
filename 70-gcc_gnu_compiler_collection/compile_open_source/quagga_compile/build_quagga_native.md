# Native compile
```
https://github.com/dramalife/note.git
AUTHOR : Dramalife@live.com
Init   : 2019.01.21
Update : ... ...
Update : 2020.03.19
Update : 
```


### 1 Build
#### 1.1 Error1 - libreadline
error: vtysh needs libreadline but was not found and usable on your system.
```bash
sudo apt-get install libreadline-dev
```

#### 1.2 Error2 - libtool version
missing: line 81: aclocal-1.15: command not found
libtool: Version mismatch error.  This is libtool 2.4.2 Debian-2.4.2-1.7ubuntu1, but the
libtool: definition of this LT_INIT comes from libtool 2.4.6.
```bash
autoreconf --force --install
```

#### 1.3 Error3 - libtool
```bash
# Ref : https://blog.csdn.net/github_29989383/article/details/51886234 
#
# libtool: Version mismatch error. This is libtool 2.4.2 , but the
# libtool: definition of this LT_INIT comes from libtool 2.4.6.
# libtool: You should recreate aclocal.m4 with macros from libtool 2.4.2 
# libtool: and run autoconf again

# make maintainer-clean 清理干净后，在运行上面的命令
autoreconf --force --install
./configure
make
```

### 2 install&runquagga
./configure --enable-vtysh --enable-user=root --enable-group=root --enable-vty-group=root
make
sudo make install

zebra: error while loading shared libraries: libzebra.so.1: cannot open shared object file: No such file or directory
```bash
sudo cp /usr/local/lib/libzebra.so* /usr/lib
```

### 3 Exec
```bash
# /etc/services    #zebra  2601/tcp  #zebra vty 
sudo zebra -d
telnet 7.0.0.1 2601
# usr:admin passwd:zebra,,,enablepasswd:zebra
```

