### 1. /bin/sh: 1: scripts/mod/modpost: not found

```
$ cd KERNEL_DIR
$ make scripts
```

### 2. OPI build

#### 2.1 Get linux source tree

```bash
# Linux source tree : linux-4.19.38(mainline) , OrangePi.build.compile.sh patched , cross compiled;
# COPY TO : orangepi/usr/src/linux-4.19.38-sunxi_opi-crossbuild
```

#### 2.2 Install source tree and kernel modules

```bash
# Change dir to linux source tree
cd /usr/src/linux-4.19.38-sunxi_opi-crossbuild

# Will create "/lib/modules/linux-4.19.38-sunxi" folder
make modules_install

```

#### 2.3 Re-compile scripts in linux source tree

Error occured(The source tree was compiled at HOST_X86_64, compiling scripts in the source must be updated)
```bash
make
make -C /lib/modules/4.19.38-sunxi/build M=/root/note/81-kernel_programming/fs/tiny_fs_symbol modules
make[1]: Entering directory '/usr/src/linux-4.19.38-sunxi_opi-crossbuild'
CC [M]  /root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o
/bin/sh: 1: scripts/basic/fixdep: Exec format error
scripts/Makefile.build:309: recipe for target '/root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o' failed
make[2]: *** [/root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o] Error 2
make[2]: *** Deleting file '/root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o'
Makefile:1524: recipe for target '_module_/root/note/81-kernel_programming/fs/tiny_fs_symbol' failed
make[1]: *** [_module_/root/note/81-kernel_programming/fs/tiny_fs_symbol] Error 2
make[1]: Leaving directory '/usr/src/linux-4.19.38-sunxi_opi-crossbuild'
Makefile:30: recipe for target 'all' failed
make: *** [all] Error 2

# Change dir to linux source tree
cd /usr/src/linux-4.19.38-sunxi_opi-crossbuild
# Re-make scripts
make scripts
# Then compiling of modules will be successful
# [171497.152243] ########tinyfs_init,438######## 
# [171504.098896] ########tinyfs_exit,445######## 
```

