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

