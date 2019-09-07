> \# note "tinyfs" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Source :  [source url](https://mp.weixin.qq.com/s/Sidfn8CZn4KxKh6xMH2uJQ)   
\# Ref : [Ref - error: ‘struct file’ has no member named ‘f_dentry’ - hn2zzzz1996](https://blog.csdn.net/hn2zzzz1996/article/details/79496282)
\# Ref : [KERNEL_VERSION](https://blog.csdn.net/whatday/article/details/98460720)  
\# Ref : [Ref - error: unknown field ‘readdir’ specified in initializer](https://blog.csdn.net/xiaominthere/article/details/17548949?utm_source=blogxgwz4)   
\# Ref :    
\# Init : 2019.09.05 ;   
\# Update   
\#  
  


### 1. USE

```bash
# insmod ./tinyfs.ko
# mount -t tinyfs none /mnt
```


### 2. ERRORs

$ uname -a
Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux

#### 2.1 ERROR1

```bash
# make > error 2>&1
make -C /lib/modules/4.0.0-040000-generic/build M=/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs modules
make[1]: Entering directory `/usr/src/linux-headers-4.0.0-040000-generic'
  CC [M]  /home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.o
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c: In function ‘tinyfs_readdir’:
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:65:31: error: ‘struct file’ has no member named ‘f_dentry’
  blk = (struct file_blk *)filp->f_dentry->d_inode->i_private;
                               ^
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c: At top level:
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:130:2: error: unknown field ‘readdir’ specified in initializer
  .readdir = tinyfs_readdir,
  ^
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:130:2: warning: initialization from incompatible pointer type [enabled by default]
/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.c:130:2: warning: (near initialization for ‘tinyfs_dir_operations.llseek’) [enabled by default]
make[2]: *** [/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs/tinyfs.o] Error 1
make[1]: *** [_module_/home/baohua/note/81-kernel_programming/device_drivers/tiny_fs] Error 2
make[1]: Leaving directory `/usr/src/linux-headers-4.0.0-040000-generic'
make: *** [all] Error 2
```

#### 2.1.1  error: ‘struct file’ has no member named ‘f_dentry’

```
Linux 3.19 compat: file_inode was added

struct access f->f_dentry->d_inode was replaced by accessor function
file_inode(f)

Signed-off-by: Joerg Thalheim <joerg@higgsboson.tk>
Signed-off-by: Brian Behlendorf <behlendorf1@llnl.gov>
使用file_inode(f)替换掉f->f_dentry->d_inode.
```

#### 2.1.2  error: unknown field ‘readdir’ specified in initializer

```diff
struct file_operations
{
//...
- readdir
+ iterate
//...
};
```

#### 2.2 

Linux 4.0.0
```
[260613.015536] kernel tried to execute NX-protected page - exploit attempt? (uid: 0)
[260613.015545] BUG: unable to handle kernel paging request at f9a1d060
[260613.015553] IP: [<f9a1d060>] tinyfs_dir_operations+0x0/0xffffffa0 [tinyfs]
[260613.015566] *pdpt = 0000000001baf001 *pde = 000000003326a067 *pte = 80000000332e1161 
[260613.015575] Oops: 0011 [#1] SMP 
[260613.015582] Modules linked in: tinyfs(OE) vboxsf(OE) xt_addrtype xt_conntrack ipt_MASQUERADE nf_nat_masquerade_ipv4 iptable_nat nf_conntrack_ipv4 nf_defrag_ipv4 nf_nat_ipv4 iptable_filter ip_tables x_tables nf_nat nf_conntrack bridge stp llc dm_thin_pool dm_persistent_data dm_bio_prison dm_bufio libcrc32c bnep rfcomm bluetooth iosf_mbi crc32_pclmul aesni_intel joydev aes_i586 xts lrw dm_multipath gf128mul ablk_helper scsi_dh cryptd serio_raw vboxguest(OE) i2c_piix4 8250_fintek mac_hid video nfsd auth_rpcgss nfs_acl nfs lockd grace sunrpc binfmt_misc fscache parport_pc ppdev lp parport hid_generic usbhid hid ahci vmw_pvscsi vmxnet3 psmouse libahci e1000
[260613.015684] CPU: 2 PID: 24379 Comm: ls Tainted: G           OE   4.0.0-040000-generic #201504121935
[260613.015689] Hardware name: innotek GmbH VirtualBox/VirtualBox, BIOS VirtualBox 12/01/2006
[260613.015694] task: f4151900 ti: f47e2000 task.ti: f47e2000
[260613.015699] EIP: 0060:[<f9a1d060>] EFLAGS: 00010206 CPU: 2
[260613.015705] EIP is at tinyfs_dir_operations+0x0/0xffffffa0 [tinyfs]
[260613.015710] EAX: f47e3f84 EBX: f9a1e26c ECX: 00000008 EDX: f9a1e26c
[260613.015714] ESI: 00000000 EDI: f9a1d060 EBP: f47e3f48 ESP: f47e3f08
[260613.015718]  DS: 007b ES: 007b FS: 00d8 GS: 00e0 SS: 0068
[260613.015722] CR0: 80050033 CR2: f9a1d060 CR3: 34183000 CR4: 000407f0
[260613.015735] DR0: 00000000 DR1: 00000000 DR2: 00000000 DR3: 00000000
[260613.015738] DR6: fffe0ff0 DR7: 00000400
[260613.015741] Stack:
[260613.015744]  f9a1c094 00000000 00000000 00000032 00000000 00000000 f9a1e266 f9a1d060
[260613.015756]  f47e3f84 f403c300 00000000 00000000 00000000 fffffffe f403c300 00000001
[260613.015768]  f47e3f74 c11bf1b7 096081d4 f2e96240 f47e3fb4 096081d4 c7c27e9c f47e3f84
[260613.015781] Call Trace:
[260613.015790]  [<f9a1c094>] ? tinyfs_readdir+0x94/0xd0 [tinyfs]
[260613.015803]  [<c11bf1b7>] iterate_dir+0xa7/0x140
[260613.015811]  [<c11bf412>] SyS_getdents64+0x72/0xd0
[260613.015817]  [<c11bee20>] ? SyS_ioctl+0xa0/0xa0
[260613.015861]  [<c170395f>] sysenter_do_call+0x12/0x12
[260613.015867] Code: 61 69 6c 65 64 0a 00 74 69 6e 79 66 73 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 <c0> e0 a1 f9 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
[260613.015946] EIP: [<f9a1d060>] tinyfs_dir_operations+0x0/0xffffffa0 [tinyfs] SS:ESP 0068:f47e3f08
[260613.015955] CR2: 00000000f9a1d060
[260613.015962] ---[ end trace d3fb50990e12cc63 ]---
```

#### 2.3 sub-Dir

```bash
root@ubuntu:/mnt # echo 36 > b.txt
root@ubuntu:/mnt # ls
111  b.txt
root@ubuntu:/mnt # cat b.txt 
36
root@ubuntu:/mnt # ls
111  b.txt
root@ubuntu:/mnt # mkdir good
root@ubuntu:/mnt # ls
111  b.txt  good
root@ubuntu:/mnt # echo goodha > good/c.txt
root@ubuntu:/mnt # ls
111  b.txt  good
root@ubuntu:/mnt # tree
.
├── 111
├── b.txt
└── good

1 directory, 2 files
root@ubuntu:/mnt # cat good/c.txt
goodha
root@ubuntu:/mnt # tree
.
├── 111
├── b.txt
└── good

1 directory, 2 files
root@ubuntu:/mnt # ls good/c.txt^Ggo 
ls: cannot access good/c.txtgo: No such file or directory
root@ubuntu:/mnt # ls good/c.txt
good/c.txt
root@ubuntu:/mnt # ls good/*
ls: cannot access good/c.txtgo: No such file or directory
root@ubuntu:/mnt # 
```

