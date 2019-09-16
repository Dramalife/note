### 1. Prepare in kernel source tree

Makefile(kernel source tree)  
```diff
define filechk_kernel.release
-        echo "$(KERNELVERSION)$$($(CONFIG_SHELL) $(srctree)/scripts/setlocalversion $(srctree))"
+        echo "$(KERNELVERSION)$$($(CONFIG_SHELL) $(srctree)/scripts/setlocalversion $(srctree))-sunxi"
endef
```

```bash
# cd linux-4.19.38
make modules
make modules_install
# make modules_install creates "/lib/modules/4.19.38-sunxi/build"
```

### 2. Compile kernel module using kernel source tree.

```bash
# cd note/81-kernel_programming/fs/tiny_fs_symbol
# make -C /lib/modules/4.19.38-sunxi/build M=/root/note/81-kernel_programming/fs/tiny_fs_symbol modules

$ modinfo tinyfs.ko
filename:       /root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
license:        GPL
depends:        
name:           tinyfs
vermagic:       4.19.38-sunxi SMP mod_unload ARMv7 p2v8 

$ insmod tinyfs.ko
insmod: ERROR: could not insert module tinyfs.ko: Invalid module format

$ dmesg | grep tinyfs
[507630.093921] tinyfs: version magic '4.19.38-sunxi SMP mod_unload ARMv7 p2v8 ' should be '4.19.38-sunxi SMP mod_unload ARMv7 thumb2 p2v8 '
# "thumb2" ??
```

### 3. Just Load Successfully

TODO : steps compiling with patch.
```bash
root@orangepizero:~/note/81-kernel_programming/fs/tiny_fs_symbol# make
make -C /lib/modules/4.19.38-sunxi/build M=/root/note/81-kernel_programming/fs/tiny_fs_symbol modules
make[1]: Entering directory '/srv/dev-disk-by-id-ata-ST500LT012-9WS142_W0V33AJV-part1/source_code_500g/linux-4.19.y_38/tar_copy/linux-4.19.y'
CC [M]  /root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.o
Building modules, stage 2.
MODPOST 1 modules
CC      /root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.mod.o
LD [M]  /root/note/81-kernel_programming/fs/tiny_fs_symbol/tinyfs.ko
make[1]: Leaving directory '/srv/dev-disk-by-id-ata-ST500LT012-9WS142_W0V33AJV-part1/source_code_500g/linux-4.19.y_38/tar_copy/linux-4.19.y'

root@orangepizero:~/note/81-kernel_programming/fs/tiny_fs_symbol# modinfo ./tinyfs.ko
filename:       /root/note/81-kernel_programming/fs/tiny_fs_symbol/./tinyfs.ko
license:        GPL
depends:        
name:           tinyfs
vermagic:       4.19.38-sunxi SMP mod_unload ARMv7 thumb2 p2v8 

root@orangepizero:~/note/81-kernel_programming/fs/tiny_fs_symbol# insmod tinyfs.ko

root@orangepizero:~/note/81-kernel_programming/fs/tiny_fs_symbol# dmesg | grep tinyfs | grep init
[707610.830916] ########tinyfs_init,438######## 

root@orangepizero:~/note/81-kernel_programming/fs/tiny_fs_symbol# rmmod tinyfs 

root@orangepizero:~/note/81-kernel_programming/fs/tiny_fs_symbol# dmesg | grep tinyfs | grep exit 
[707630.737739] ########tinyfs_exit,445######## 
```

