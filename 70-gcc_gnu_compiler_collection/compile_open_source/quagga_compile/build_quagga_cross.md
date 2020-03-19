# Cross Compile
```
https://github.com/dramalife/note.git
AUTHOR : Dramalife@live.com
Init   : 2020.03.19
Update : 
```

### 1 Build
config.log
```
# warning : sysconfdir -- confdir of target !!!!
./configure --host=arm-linux-gnueabihf --with-sysroot=/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf --disable-nhrpd --prefix=/home/dramalife/prefix_quagga/usr/local --sysconfdir=/home/dramalife/prefix_quagga/usr/local/etc --enable-vtysh --enable-user=root --enable-group=root --enable-vty-group=root
```
#### 1.1 configure - libreadline

##### 1.1.1 ErrMsg
not found
```bash
configure: error: vtysh needs libreadline but was not found and usable on your system.
```
##### 1.1.2 config.log

```bash
# Error - configure
configure:18303: checking for main in -lreadline
configure:18322: arm-linux-gnueabihf-gcc -o conftest -g -O2 -g -Os -fstack-protector-strong --param=ssp-buffer-size=4 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -fpie -fno-omit-frame-pointer -Wall -Wextra -Wmissing-prototypes -Wmissing-declarations -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Wno-unused-result -Wno-unused-parameter -Wno-missing-field-initializers   conftest.c -lreadline   >&5
/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.4.1/../../../../arm-linux-gnueabihf/bin/ld: cannot find -lreadline
collect2: error: ld returned 1 exit status
```
##### 1.1.3 Solve
```bash
# Download source code
wget https://mirrors.sjtug.sjtu.edu.cn/gnu/readline/readline-8.0.tar.gz

# Install to sysroot of cross_tool, for compilation.
./configure --host=arm-linux-gnueabihf --prefix=/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf
# Install to target rootfs, for runtime.
./configure --host=arm-linux-gnueabihf --prefix=/home/dramalife/prefix_quagga

make
sudo make install
```
#### 1.2 configure - libncurses
##### 1.2.1 ErrMsg
found but not usable !
```bash
configure: error: vtysh needs libreadline but was not found and usable on your system.
```
##### 1.2.2 config.log
```bash
$ arm-linux-gnueabihf-gcc -o conftest -g -O2 -g -Os -fstack-protector-strong --param=ssp-buffer-size=4 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -fpie -fno-omit-frame-pointer -Wall -Wextra -Wmissing-prototypes -Wmissing-declarations -Wpointer-arith -Wbad-function-cast -Wwrite-strings -Wno-unused-result -Wno-unused-parameter -Wno-missing-field-initializers   conftest.c -L=/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/lib -lreadline
/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.4.1/../../../../arm-linux-gnueabihf/lib/libreadline.so: undefined reference to `tputs'
/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.4.1/../../../../arm-linux-gnueabihf/lib/libreadline.so: undefined reference to `tgoto'
/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.4.1/../../../../arm-linux-gnueabihf/lib/libreadline.so: undefined reference to `tgetflag'
/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.4.1/../../../../arm-linux-gnueabihf/lib/libreadline.so: undefined reference to `UP'
/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.4.1/../../../../arm-linux-gnueabihf/lib/libreadline.so: undefined reference to `tgetent'
/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.4.1/../../../../arm-linux-gnueabihf/lib/libreadline.so: undefined reference to `tgetnum'
/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.4.1/../../../../arm-linux-gnueabihf/lib/libreadline.so: undefined reference to `PC'
/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.4.1/../../../../arm-linux-gnueabihf/lib/libreadline.so: undefined reference to `tgetstr'
/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/bin/../lib/gcc/arm-linux-gnueabihf/7.4.1/../../../../arm-linux-gnueabihf/lib/libreadline.so: undefined reference to `BC'
collect2: error: ld returned 1 exit status
```
##### 1.2.3 Solve
```bash
# Download source code
wget https://mirrors.sjtug.sjtu.edu.cn/gnu/ncurses/ncurses-6.2.tar.gz

# Install to sysroot of cross_tool, for compilation.
./configure --host=arm-linux-gnueabihf --prefix=/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf
# Install to target rootfs, for runtime.
./configure --host=arm-linux-gnueabihf --prefix=/home/dramalife/prefix_quagga

make
sudo make install
```
#### 1.3 libtool - libcares (optional)
##### 1.3.1 ErrMsg
```
libtool: warning: library '/usr/local/lib/libcares.la' was moved.
libtool: warning: library '/usr/local/lib/libcares.la' was moved.
/usr/local/lib/libcares.so: file not recognized: File format not recognized
collect2: error: ld returned 1 exit status
Makefile:475: recipe for target 'nhrpd' failed
make[2]: *** [nhrpd] Error 1
make[2]: Leaving directory '/home/dramalife/temp/quagga-1.2.4/nhrpd'
Makefile:467: recipe for target 'all-recursive' failed
make[1]: *** [all-recursive] Error 1
make[1]: Leaving directory '/home/dramalife/temp/quagga-1.2.4'
Makefile:399: recipe for target 'all' failed
make: *** [all] Error 2
```
##### 1.3.2 Solve
```bash
# Download source code
wget https://c-ares.haxx.se/download/c-ares-1.15.0.tar.gz

# Install to sysroot of cross_tool, for compilation.
./configure --host=arm-linux-gnueabihf --prefix=/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf
# Install to target rootfs, for runtime.
./configure --host=arm-linux-gnueabihf --prefix=/home/dramalife/prefix_quagga

make
sudo make install
```

### 2 Install
```
root@Raisecom:/# cp /usr/local/lib/libzebra.* /lib
root@Raisecom:/# zebra --version                  
zebra version 1.2.4
Copyright 1996-2005 Kunihiro Ishiguro, et al.
configured with:
        --host=arm-linux-gnueabihf --with-sysroot=/usr/local/gcc-linaro-7.4.1-2019.02-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf --disable-nhrpd --prefix=/home/dramalife/prefix_quagga/usr/local --sysconfdir=/home/dramalife/prefix_quagga/usr/local/etc --enable-vtysh --enable-user=root --enable-group=root --enable-vty-group=root
root@Raisecom:/# uname -a
Linux Raisecom 4.1.15 #1 SMP PREEMPT Wed Jan 8 09:38:46 CST 20 armv7l GNU/Linux
root@Raisecom:/# cat /etc/issue
Freescale i.MX Release Distro 4.1.15-2.1.0 \n \l

root@Raisecom:/# 
```

### 3 Exec
```
root@Raisecom:/# telnet 127.0.0.1 01

Entering character mode
Escape character is '^]'.


Hello, this is Quagga (version 1.2.4).
Copyright 1996-2005 Kunihiro Ishiguro, et al.


User Access Verification

Password: 
Router> 
Router> enable
Password: 
Password: 
Router# 
Router# 
  clear      Clear stored data
  configure  Configuration from vty interface
  copy       Copy configuration
  debug      Debugging functions (see also 'undebug')
  disable    Turn off privileged mode command
  echo       Echo a message back to the vty
  enable     Turn on privileged mode command
  end        End current mode and change to enable mode.
  exit       Exit current mode and down to previous mode
  help       Description of the interactive help system
  list       Print command list
  logmsg     Send a message to enabled logging destinations
  no         Negate a command or set its defaults
  quit       Exit current mode and down to previous mode
  show       Show running system information
  terminal   Set terminal line parameters
  who        Display who is on vty
  write      Write running configuration to memory, network, or terminal
Router# 
```
