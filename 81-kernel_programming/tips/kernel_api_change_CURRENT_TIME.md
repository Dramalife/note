> \# note "kernel-api" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Ref Url : [linux各个版本的changelog - lieye_leaves](https://blog.csdn.net/lieye_leaves/article/details/68935584)  
\# Source Url : [https://kernelnewbies.org](https://kernelnewbies.org) 
\#  
\# Init : 2019.09.11;  
\# Update   
\#  



### 1. Search Recording

[kernelnewbies.org](https://kernelnewbies.org) > "查找网页" > CURRENT_TIME    
[search_result](https://kernelnewbies.org/%E6%9F%A5%E6%89%BE%E7%BD%91%E9%A1%B5?action=fullsearch&advancedsearch=1&and_terms=&or_terms=CURRENT_TIME&not_terms=&mtime=&categories=&language=&mimetype=)    
[result_content](https://kernelnewbies.org/y2038/vfs?highlight=%28CURRENT_TIME%29)    
[related_1](https://lkml.org/lkml/2016/2/3/34)    
[related_2](https://lkml.org/lkml/2016/2/22/506)    



### 2. Details

#### 2.1 Plan for VFS

Replace current_time and current_time_sec

This patch series is aimed at getting rid of CURRENT_TIME and CURRENT_TIME_SEC macros. The macros: CURRENT_TIME and CURRENT_TIME_SEC are primarily used for filesystem timestamps. to the granularity as required by the filesystem. There will also be another series to add range checks and clamping to filesystem time functions that are meant to substitute the above macros:

```c
	struct timespec current_fs_time(struct super_block *sb)
	struct timespec current_fs_time_sec(struct super_block *sb)
```

These time functions will also be transitioned along with VFS to use struct timespec64 instead of struct timespec. Any use of these macros outside of filesystem timestamps will be replaced by ktime_get*/ get_seconds functions.
	
Links to posted patches:
1. http://thread.gmane.org/gmane.linux.file-systems/106912 (Infrastructure patch)
2. https://lkml.org/lkml/2016/2/3/34
3. https://lkml.org/lkml/2016/2/22/506


#### 2.2 lkml.org/lkml/2016/2/3/34

```
From	Deepa Dinamani <>
Subject	[PATCH 00/10] Remove CURRENT_TIME and CURRENT_TIME_SEC - PART 1
Date	Tue, 2 Feb 2016 22:07:40 -0800
share
Introduction

This patch series is aimed at getting rid of CURRENT_TIME and CURRENT_TIME_SEC
macros.

The idea for the series evolved from my discussions with Arnd Bergmann.

This was originally part of the RFC series[2]:
https://lkml.org/lkml/2016/1/7/20 (under discussion).

Dave Chinner suggested moving bug fixes out of the feature series to keep the
original series simple.

There are 354 occurrences of the the above macros in the kernel.
The series will be divided into 4 or 5 parts to keep the parts manageable
and so that each part could be reviewed and merged independently.
This is part 1 of the series. 

Motivation

The macros: CURRENT_TIME and CURRENT_TIME_SEC are primarily used for
filesystem timestamps.
But, they are not accurate as they do not perform clamping according to
filesystem timestamps ranges, nor do they truncate the nanoseconds value
to the granularity as required by the filesystem.

The series is also viewed as an ancillary to another upcoming series[2]
that attempts to transition file system timestamps to use 64 bit time to
make these y2038 safe.

There will also be another series[3] to add range checks and clamping to
filesystem time functions that are meant to substitute the above macros.

Solution

CURRENT_TIME macro has an equivalent function:

struct timespec current_fs_time(struct super_block *sb)

These will be the changes to the above function:
1. Function will return the type y2038 safe timespec64 in [2].
2. Function will use y2038 safe 64 bit functions in [2].
3. Function will be extended to perform range checks in [3].

A new function will be added to substitute for CURRENT_TIME_SEC macro
in the current series:

struct timespec current_fs_time_sec(void)

These will be the changes to the above function:
1. Function will return the type y2038 safe timespec64 in [2].
2. Function will use y2038 safe 64 bit functions in [2].
3. Function will be extended to perform range checks in [3].

Any use of these macros outside of filesystem timestamps will
be replaced by function calls to appropriate time functions.

Deepa Dinamani (10):
  fs: Add current_fs_time_sec() function
  vfs: Replace CURRENT_TIME by current_fs_time()
  fs: cifs: Replace CURRENT_TIME with current_fs_time()
  fs: cifs: Replace CURRENT_TIME with ktime_get_real_ts()
  fs: cifs: Replace CURRENT_TIME by get_seconds
  fs: ext4: Replace CURRENT_TIME_SEC with current_fs_time_sec()
  fs: ext4: Replace CURRENT_TIME with ext4_current_time()
  fs: ceph: replace CURRENT_TIME by current_fs_time()
  fs: ceph: Replace CURRENT_TIME by ktime_get_real_ts()
  fs: btrfs: Replace CURRENT_TIME by current_fs_time()

 fs/btrfs/file.c        |  4 ++--
 fs/btrfs/inode.c       | 25 +++++++++++++------------
 fs/btrfs/ioctl.c       |  8 ++++----
 fs/btrfs/root-tree.c   |  2 +-
 fs/btrfs/transaction.c |  7 +++++--
 fs/btrfs/xattr.c       |  2 +-
 fs/ceph/file.c         |  4 ++--
 fs/ceph/inode.c        |  2 +-
 fs/ceph/mds_client.c   |  2 +-
 fs/ceph/xattr.c        |  4 ++--
 fs/cifs/cifsencrypt.c  |  4 +++-
 fs/cifs/cifssmb.c      | 10 +++++-----
 fs/cifs/inode.c        | 15 +++++++--------
 fs/ext4/ext4.h         |  2 +-
 fs/ext4/super.c        |  2 +-
 fs/libfs.c             | 21 +++++++++++++--------
 fs/nsfs.c              |  3 ++-
 fs/pipe.c              |  3 ++-
 fs/posix_acl.c         |  2 +-
 include/linux/fs.h     |  5 +++++
 20 files changed, 72 insertions(+), 55 deletions(-)

-- 
1.9.1
```

#### 2.3 lkml.org/lkml/2016/2/22/506

```
From	Deepa Dinamani <>
Subject	[PATCH 0/8] Remove CURRENT_TIME and CURRENT_TIME_SEC - PART 2
Date	Mon, 22 Feb 2016 07:17:46 -0800
share
Introduction

This patch series is aimed at getting rid of CURRENT_TIME and CURRENT_TIME_SEC
macros.

The idea for the series evolved from my discussions with Arnd Bergmann.

This was originally part of the RFC series[2]:
https://lkml.org/lkml/2016/1/7/20 (under discussion).

Dave Chinner suggested moving bug fixes out of the feature series to keep the
original series simple.

There are 354 occurrences of the the above macros in the kernel.
The series will be divided into 4 or 5 parts to keep the parts manageable
and so that each part could be reviewed and merged independently.
This is part 2 of the series.

Motivation

The macros: CURRENT_TIME and CURRENT_TIME_SEC are primarily used for
filesystem timestamps.
But, they are not accurate as they do not perform clamping according to
filesystem timestamps ranges, nor do they truncate the nanoseconds value
to the granularity as required by the filesystem.

The series is also viewed as an ancillary to another upcoming series[2]
that attempts to transition file system timestamps to use 64 bit time to
make these y2038 safe.

There will also be another series[3] to add range checks and clamping to
filesystem time functions that are meant to substitute the above macros.

Solution

CURRENT_TIME macro has an equivalent function:

struct timespec current_fs_time(struct super_block *sb)

These will be the changes to the above function:
1. Function will return the type y2038 safe timespec64 in [2].
2. Function will use y2038 safe 64 bit functions in [2].
3. Function will be extended to perform range checks in [3].

A new function will be added to substitute for CURRENT_TIME_SEC macro
in the current series:

struct timespec current_fs_time_sec(struct super_block *sb)

These will be the changes to the above function:
1. Function will return the type y2038 safe timespec64 in [2].
2. Function will use y2038 safe 64 bit functions in [2].
3. Function will be extended to perform range checks in [3].

Any use of these macros outside of filesystem timestamps will
be replaced by function calls to appropriate time functions.

Deepa Dinamani (8):
  fs: debugfs: Replace CURRENT_TIME by current_fs_time()
  fs: logfs: Replace CURRENT_TIME by current_fs_time()
  fs: devpts: Replace CURRENT_TIME by current_fs_time()
  fs: configfs: Replace CURRENT_TIME by current_fs_time()
  fs: proc: Replace CURRENT_TIME by current_fs_time()
  fs: ramfs: Replace CURRENT_TIME by current_fs_time()
  fs: kernfs: Replace CURRENT_TIME by current_fs_time()
  net: sunrpc: Replace CURRENT_TIME by current_fs_time()

 fs/configfs/inode.c   |  8 +++++---
 fs/debugfs/inode.c    |  3 ++-
 fs/devpts/inode.c     |  9 ++++++---
 fs/kernfs/dir.c       |  8 +++++---
 fs/kernfs/inode.c     | 15 ++++++++++-----
 fs/logfs/dir.c        | 11 +++++++----
 fs/logfs/file.c       |  2 +-
 fs/logfs/inode.c      |  3 +--
 fs/logfs/readwrite.c  |  7 ++++---
 fs/proc/base.c        |  3 ++-
 fs/proc/inode.c       |  6 ++++--
 fs/proc/proc_sysctl.c |  3 ++-
 fs/proc/self.c        |  3 ++-
 fs/proc/thread_self.c |  3 ++-
 fs/ramfs/inode.c      | 13 ++++++++-----
 net/sunrpc/rpc_pipe.c |  4 +++-
 16 files changed, 64 insertions(+), 37 deletions(-)

-- 
1.9.1
```
