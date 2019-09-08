
```bash
make -C /lib/modules/5.0.0-25-generic/build M=/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs modules
make[1]: Entering directory '/usr/src/linux-headers-5.0.0-25-generic'
  CC [M]  /home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.o
/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c: In function ‘tinyfs_do_create’:
/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:239:53: error: ‘CURRENT_TIME’ undeclared (first use in this function); did you mean ‘CURRENT_MASK’?
  inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
                                                     ^~~~~~~~~~~~
                                                     CURRENT_MASK
/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:239:53: note: each undeclared identifier is reported only once for each function it appears in
/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c: In function ‘tinyfs_iget’:
/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:300:53: error: ‘CURRENT_TIME’ undeclared (first use in this function); did you mean ‘CURRENT_MASK’?
  inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
                                                     ^~~~~~~~~~~~
                                                     CURRENT_MASK
/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c: In function ‘tinyfs_fill_super’:
/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:381:68: error: ‘CURRENT_TIME’ undeclared (first use in this function); did you mean ‘CURRENT_MASK’?
  root_inode->i_atime = root_inode->i_mtime = root_inode->i_ctime = CURRENT_TIME;
                                                                    ^~~~~~~~~~~~
                                                                    CURRENT_MASK
scripts/Makefile.build:291: recipe for target '/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.o' failed
make[2]: *** [/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.o] Error 1
Makefile:1606: recipe for target '_module_/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs' failed
make[1]: *** [_module_/home/dramalife/note/81-kernel_programming/device_drivers/tiny_fs] Error 2
make[1]: Leaving directory '/usr/src/linux-headers-5.0.0-25-generic'
Makefile:28: recipe for target 'all' failed
make: *** [all] Error 2
```

