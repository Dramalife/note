> \# note "kernel-fs-struct_inode" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Ref Url : [内核中inode结构体 - 做一个有追求的工程师](https://blog.csdn.net/liebao_han/article/details/78912595)   
\#  
\# Init : 2019.09.11;  
\# Update   
\#  



### 1. struct inode

```c
struct inode {
	umode_t         i_mode;//文件的访问权限（eg:rwxrwxrwx）
	unsigned short      i_opflags;
	kuid_t          i_uid;//inode拥有者id
	kgid_t          i_gid;//inode拥有者组id
	unsigned int        i_flags;//inode标志，可以是S_SYNC,S_NOATIME,S_DIRSYNC等

#ifdef CONFIG_FS_POSIX_ACL
	struct posix_acl    *i_acl;
	struct posix_acl    *i_default_acl;
#endif

	const struct inode_operations   *i_op;//inode操作
	struct super_block  *i_sb;//所属的超级快
	/*
	   address_space并不代表某个地址空间，而是用于描述页高速缓存中的页面的一个文件对应一个address_space，一个address_space与一个偏移量能够确定一个一个也高速缓存中的页面。i_mapping通常指向i_data,不过两者是有区别的，i_mapping表示应该向谁请求页面，i_data表示被改inode读写的页面。
	 */
	struct address_space    *i_mapping;

#ifdef CONFIG_SECURITY
	void            *i_security;
#endif

	/* Stat data, not accessed from path walking */
	unsigned long       i_ino;//inode号
	/*
	 * Filesystems may only read i_nlink directly.  They shall use the
	 * following functions for modification:
	 *
	 *    (set|clear|inc|drop)_nlink
	 *    inode_(inc|dec)_link_count
	 */
	union {
		const unsigned int i_nlink;//硬链接个数
		unsigned int __i_nlink;
	};
	dev_t           i_rdev;//如果inode代表设备，i_rdev表示该设备的设备号
	loff_t          i_size;//文件大小
	struct timespec     i_atime;//最近一次访问文件的时间
	struct timespec     i_mtime;//最近一次修改文件的时间
	struct timespec     i_ctime;//最近一次修改inode的时间
	spinlock_t      i_lock; /* i_blocks, i_bytes, maybe i_size */
	unsigned short          i_bytes;//文件中位于最后一个块的字节数
	unsigned int        i_blkbits;//以bit为单位的块的大小
	blkcnt_t        i_blocks;//文件使用块的数目

#ifdef __NEED_I_SIZE_ORDERED
	seqcount_t      i_size_seqcount;//对i_size进行串行计数
#endif

	/* Misc */
	unsigned long       i_state;//inode状态，可以是I_NEW,I_LOCK,I_FREEING等
	struct mutex        i_mutex;//保护inode的互斥锁

	//inode第一次为脏的时间 以jiffies为单位
	unsigned long       dirtied_when;   /* jiffies of first dirtying */

	struct hlist_node   i_hash;//散列表
	struct list_head    i_wb_list;  /* backing dev IO list */
	struct list_head    i_lru;      /* inode LRU list */
	struct list_head    i_sb_list;//超级块链表
	union {
		struct hlist_head   i_dentry;//所有引用该inode的目录项形成的链表
		struct rcu_head     i_rcu;
	};
	u64         i_version;//版本号 inode每次修改后递增
	atomic_t        i_count;//引用计数
	atomic_t        i_dio_count;
	atomic_t        i_writecount;//记录有多少个进程以可写的方式打开此文件
	const struct file_operations    *i_fop; /* former ->i_op->default_file_ops */
	struct file_lock    *i_flock;//文件锁链表
	struct address_space    i_data;
#ifdef CONFIG_QUOTA
	struct dquot        *i_dquot[MAXQUOTAS];//inode磁盘限额
#endif
	/*
	   公用同一个驱动的设备形成链表，比如字符设备，在open时，会根据i_rdev字段查找相应的驱动程序，并使i_cdev字段指向找到的cdev，然后inode添加到struct cdev中的list字段形成的链表中
	 */
	struct list_head    i_devices;，
		union {
			struct pipe_inode_info  *i_pipe;//如果文件是一个管道则使用i_pipe
			struct block_device *i_bdev;//如果文件是一个块设备则使用i_bdev
			struct cdev     *i_cdev;//如果文件是一个字符设备这使用i_cdev
		};

	__u32           i_generation;

#ifdef CONFIG_FSNOTIFY
	//目录通知事件掩码
	__u32           i_fsnotify_mask; /* all events this inode cares about */
	struct hlist_head   i_fsnotify_marks;
#endif

#ifdef CONFIG_IMA
	atomic_t        i_readcount; /* struct files open RO */
#endif
	//存储文件系统或者设备的私有信息
	void            *i_private; /* fs or device private pointer */
};

```

实际上，inode是VFS使用的一个对象，用于存放内核在操作文件或目录时所需要的全部信息。索引节点有两种，一种是这里所说的VFS索引节点，存在内存中；另一种是具体文件系统的索引节点，存在于磁盘上，使用时将其读入内存填充VFS的索引节点，之后对VFS索引节点的任何修改都将写回磁盘更新磁盘的索引节点。     
对于inod需要知道：     
1）对于Unix风格的文件系统来说，这些信息可以从磁盘索引节点直接读入。如果一个文件 系统没有索引节点，那么不管这些相关信息在磁盘上市怎么存放的，文件系统都必须从中提取这些信息。没有索引的文件系统通常将文件的描述信息作为文件的一部分来存放。这些文件系统与Unix风格的文件系统不同，没有将数据与控制信息分开存放。而有些现代的文件系统使用数据库来存储文件的数据。但是不管哪种情况、采用哪种方式，索引节点对象必须在内存中创建，以便文件系统来使用。     
2）一个索引节点代表了文件系统的一个文件，在文件创建时创建文件删除时销毁，但是索引节点仅在当文件被访问时，才在内存中创建，且无论有多少个副本访问这个文件，inode只存在一份。     
3）inode只是用于描述文件的元数据信息，并不是文件的数据，文件的数据会根据inode的信息存放在一个数据块中（例如：test.txt文件ls -l看到的信息就是它的属性元信息，“hello”数据存放在另一个数据块中）。     
4）可以简单理解为ls -l 看到的就是此文件的inode信息。     
5）inode可以描述像普通文件、目录这样的磁盘文件，他也可以描述设备或者管道这样的文件，不过这些特殊的文件一般只存在inode块不分配数据块（因为索引节点中有一些特殊文件相关的项，比如i_pipe项就指向一个代表有名管道的数据结构，i_bdev块设备结构体，i_cdev指向字符设备结构体。这三个指针被放在一个共用体中，因为一个给定的索引节点每次只能表示三者之一（或者均不））。     
6）有时，某些文件系统可能并不能完整地包含索引节点结构体所要求的所有信息。例如，有的文件系统可能并不记录文件的访问时间，这时，该文件系统可以在实现中选择合适的办法来解决和这个问题。它可以在i_atime中存储0，或者让i_atime等于i_mtime,或者只在内存中更新i_atime而不将其写回磁盘，或者由文件系统 的实现者来决定。    


### 2. struct inode_operations

```c
truct inode_operations {
	struct dentry * (*lookup) (struct inode *,struct dentry *, unsigned int);
	void * (*follow_link) (struct dentry *, struct nameidata *);
	int (*permission) (struct inode *, int);
	struct posix_acl * (*get_acl)(struct inode *, int);

	int (*readlink) (struct dentry *, char __user *,int);
	void (*put_link) (struct dentry *, struct nameidata *, void *);

	int (*create) (struct inode *,struct dentry *, umode_t, bool);
	int (*link) (struct dentry *,struct inode *,struct dentry *);
	int (*unlink) (struct inode *,struct dentry *);
	int (*symlink) (struct inode *,struct dentry *,const char *);
	int (*mkdir) (struct inode *,struct dentry *,umode_t);
	int (*rmdir) (struct inode *,struct dentry *);
	int (*mknod) (struct inode *,struct dentry *,umode_t,dev_t);
	int (*rename) (struct inode *, struct dentry *,
			struct inode *, struct dentry *);
	int (*setattr) (struct dentry *, struct iattr *);
	int (*getattr) (struct vfsmount *mnt, struct dentry *, struct kstat *);
	int (*setxattr) (struct dentry *, const char *,const void *,size_t,int);
	ssize_t (*getxattr) (struct dentry *, const char *, void *, size_t);
	ssize_t (*listxattr) (struct dentry *, char *, size_t);
	int (*removexattr) (struct dentry *, const char *);
	int (*fiemap)(struct inode *, struct fiemap_extent_info *, u64 start,
			u64 len);
	int (*update_time)(struct inode *, struct timespec *, int);
	int (*atomic_open)(struct inode *, struct dentry *,
			struct file *, unsigned open_flag,
			umode_t create_mode, int *opened);
	int (*tmpfile) (struct inode *, struct dentry *, umode_t);
	int (*set_acl)(struct inode *, struct posix_acl *, int);
} ____cacheline_aligned;

```

下面介绍常用的各种借口函数：在给定的节点上，可能是由VFS执行这些函数，也可能由具体的文件系统执行：    
struct dentry * (*lookup) (struct inode *dir,struct dentry *dentry , unsigned int )    
该函数在在特定目录中寻找索引节点，改索引节点要对应于dentry中给出的文件名。   
   
int (*create) (struct inode *dir,struct dentry *dentry , umode_t mode, bool )    
VFS通过系统调用create()和open()来调用改函数，从而为dentry对象创建一个新的索引节点。在创建时使用mode指定初始模式   
   
int (link) (struct dentry *old_denrty,struct inode dir,struct dentry *dentry);    
该函数被系统调用link()调用，用来创建硬链接。硬链接名称由dentry指定，连接对象是dir目录中old_denrty目录项所代表的文件。   
   
int (unlink) (struct inode *dir,struct dentry dentry);    
该函数被系统调用ulink()调用，从目录dir中删除由目录项dentry指定的索引节点对象。   
   
int (*symlink) (struct inode *dir,struct dentry *dentry ,const char *symname);    
该函数被系统调用symlink()调用,创建符号链接。改符号链接的名称由symname指定，连接对象是dir目录中的dentry目录项。   
   
int (*mkdir) (struct inode *dir,struct dentry *dentry ,umode_t mode);    
该函数被系统调用mkdir()调用,创建一个新的目录。创建时使用mode指定初始模式。   
   
int (*rmdir) (struct inode *dir,struct dentry *dentry );    
该函数被系统调用rmdir()调用,删除dir目录中的dentry 目录项代表的文件。   
   
int (*mknod) (struct inode *dir,struct dentry *dentry ,umode_t mode,dev_t rdev);    
该函数被系统调用mknod()调用,创建特殊文件（设备文件、命名管道或套接字）。要创建的文件在dir目录中，其目录项为dentry，关联的设备为rdev,初始权限有mode指定。   
   
int (*rename) (struct inode *old_dir, struct dentry *old_dentry ,struct inode *new_dir ,struct dentry *new_dentry );    
VFS调用该函数来移动文件。文件路径在old_dir目录中，源文件由old_dentry目录项指定，目标路径在new_dir中，目标文件由new_dentry指定。   

