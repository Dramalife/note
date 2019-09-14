/*
 * note "tinyfs" related file
 * Copyright (C) 2019 Dramalife@live.com
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux;
 * 
 * Source :  https://mp.weixin.qq.com/s/Sidfn8CZn4KxKh6xMH2uJQ
 * Init : 2019.09.05, COPY FROM https://github.com/charliekernelmode/tinyfs.git;
 * Update 2019.09.05, Compatibles for "4.0.0-040000-generic"; 
 * Update 2019.09.06, Add "int tinyfs_readdir4 (...)" to Fix bug that Calling Trace and blocking shell when running "ls" command after touching a file;
 * Update 2019.09.07, Modified "int tinyfs_readdir4 (...)" to Fix bug that blocking shell when running "ls" command after touching a file;
 *		      Add "ssize_t tinyfs_read4(...)"______^^^^^^^^^^;
 * Update 
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include <linux/version.h>
#if !defined(KERNEL_VERSION) || !defined(LINUX_VERSION_CODE)
#error KERNEL_VERSION undefined !
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,0,0)
#include <linux/time.h>
#endif

#include "tinyfs.h"


struct tiny_file_blk block[MAX_FILES+1];
int curr_count = 0; //count of dir and file;

// 获得一个尚未使用的文件块，保存新创建的文件或者目录
static int get_block(void)
{
	int i;

	// 就是一个遍历，但实现快速。
	for (i = 2; i < MAX_FILES; i++) {
		if (!block[i].busy) {
			block[i].busy = 1;
			return i;
		}
	}
	return -1;
}

static struct inode_operations tinyfs_inode_ops;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,0,0)
/*
 * M-20190907:
 * 	- pos=filearg->f_pos;
 * 	+ pos=ctxarg->pos;
 * ex. Running "ls" command will call this func.
 */
int tinyfs_readdir4 (struct file *filearg,  struct dir_context *ctxarg)
{
	struct tiny_file_blk *blk;
	struct tiny_dir_entry *de;
	struct inode *inode = file_inode(filearg);/* inode - filearg */
	int i;

	printk("%s,%d:FUNC IN! \n",__func__,__LINE__);
	if (ctxarg->pos) {
		printk("%s,%d:FUNC EXIT! \n",__func__,__LINE__);
		return 0;
	}

	blk = (struct tiny_file_blk *)inode->i_private;/* blk - inode - filearg */

	if (!S_ISDIR(blk->mode)) {
		printk("%s,%d:FUNC EXIT! \n",__func__,__LINE__);
		return -ENOTDIR;
	}

	de = (struct tiny_dir_entry *)&blk->data[0];/* de - blk - inode - filearg */
	for (i = 0; i < blk->dir_children; i++) {
		printk("%s,%d,pos:%llu \n",__func__,__LINE__, (long long)ctxarg->pos);
		ctxarg->actor(ctxarg, de[i].filename, MAXLEN, ctxarg->pos, de[i].idx, DT_UNKNOWN);
		filearg->f_pos += sizeof(struct tiny_dir_entry);
		ctxarg->pos += sizeof(struct tiny_dir_entry);
	}

	printk("%s,%d:FUNC EXIT! \n",__func__,__LINE__);
	return 0;
}

ssize_t tinyfs_read4(struct file * filp, char __user * buf, size_t len, loff_t *ppos)
{
	struct tiny_file_blk *blk;
	struct inode *inode = file_inode(filp);
	char *buffer;

	blk = (struct tiny_file_blk *)inode->i_private;
	if (*ppos >= blk->file_size)
		return 0;

	buffer = (char *)&blk->data[0];
	len = min((size_t) blk->file_size, len);

	if (copy_to_user(buf, buffer, len)) {
		return -EFAULT;
	}
	*ppos += len;

	return len;
}
#else
//int 	(*readdir) 	 (struct file *,     void *,       filldir_t);/* Linux 3.6 */
static int tinyfs_readdir(struct file *filp, void *dirent, filldir_t filldir)
{
	loff_t pos;
	struct tiny_file_blk *blk;
	struct tiny_dir_entry *entry;
	int i;

	pos = filp->f_pos;
	if (pos)
		return 0;

	blk = (struct tiny_file_blk *)filp->f_dentry->d_inode->i_private;

	if (!S_ISDIR(blk->mode)) {
		return -ENOTDIR;
	}

	// 循环获取一个目录的所有文件的文件名
	entry = (struct tiny_dir_entry *)&blk->data[0];
	for (i = 0; i < blk->dir_children; i++) {
		//int (*filldir_t)     (void *, const char *,      int,   loff_t, u64,        unsigned);/* Linux 3.6 */
		filldir(dirent, entry[i].filename, MAXLEN, pos, entry[i].idx, DT_UNKNOWN);
		filp->f_pos += sizeof(struct tiny_dir_entry);
		pos += sizeof(struct tiny_dir_entry);
	}

	return 0;
}

// read实现
ssize_t tinyfs_read(struct file * filp, char __user * buf, size_t len, loff_t *ppos)
{
	struct tiny_file_blk *blk;
	char *buffer;

	blk = (struct tiny_file_blk *)filp->f_path.dentry->d_inode->i_private;
	if (*ppos >= blk->file_size)
		return 0;

	buffer = (char *)&blk->data[0];
	len = min((size_t) blk->file_size, len);

	if (copy_to_user(buf, buffer, len)) {
		return -EFAULT;
	}
	*ppos += len;

	return len;
}
#endif

// write实现
ssize_t tinyfs_write(struct file * filp, const char __user * buf, size_t len, loff_t * ppos)
{
	struct tiny_file_blk *blk;
	char *buffer;

	blk = filp->f_path.dentry->d_inode->i_private;

	buffer = (char *)&blk->data[0];
	buffer += *ppos;

	if (copy_from_user(buffer, buf, len)) {
		return -EFAULT;
	}
	*ppos += len;
	blk->file_size = *ppos;

	return len;
}

const struct file_operations tinyfs_file_operations = {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,0,0)
	.read = tinyfs_read4,
#else
	.read = tinyfs_read,
#endif
	.write = tinyfs_write,
};

const struct file_operations tinyfs_dir_operations = {
	.owner = THIS_MODULE,
#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,0,0)
	.iterate = tinyfs_readdir4,
#else
	.readdir = tinyfs_readdir,
#endif
};

// 创建文件的实现
static int tinyfs_do_create(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct inode *inode;
	struct super_block *sb;
	struct tiny_dir_entry *entry;
	struct tiny_file_blk *blk, *pblk;
	int idx;

	sb = dir->i_sb;

	if (curr_count >= MAX_FILES) {
		return -ENOSPC;
	}

	if (!S_ISDIR(mode) && !S_ISREG(mode)) {
		return -EINVAL;
	}

	inode = new_inode(sb);
	if (!inode) {
		return -ENOMEM;
	}

	inode->i_sb = sb;
	inode->i_op = &tinyfs_inode_ops;
#if LINUX_VERSION_CODE > KERNEL_VERSION(4,0,0)
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
#else
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
#endif

	idx = get_block(); // 获取一个空闲的文件块保存新文件

	blk = &block[idx];
	inode->i_ino = idx;
	blk->mode = mode;
	curr_count ++;

	if (S_ISDIR(mode)) {
		blk->dir_children = 0;
		inode->i_fop = &tinyfs_dir_operations;
	} else if (S_ISREG(mode)) {
		blk->file_size = 0;
		inode->i_fop = &tinyfs_file_operations;
	}

	inode->i_private = blk;
	pblk = (struct tiny_file_blk *)dir->i_private;

	entry = (struct tiny_dir_entry *)&pblk->data[0];
	entry += pblk->dir_children;
	pblk->dir_children ++;

	entry->idx = idx;
	strcpy(entry->filename, dentry->d_name.name);

	// VFS穿针引线的关键步骤，将VFS的inode链接到链表
	inode_init_owner(inode, dir, mode); 
	d_add(dentry, inode);

	return 0;
}

static int tinyfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	return tinyfs_do_create(dir, dentry, S_IFDIR | mode);
}

static int tinyfs_create(struct inode *dir, struct dentry *dentry, umode_t mode, bool excl)
{
	return tinyfs_do_create(dir, dentry, mode);
}

static struct inode *tinyfs_iget(struct super_block *sb, int idx)
{
	struct inode *inode;
	struct tiny_file_blk *blk;

	inode = new_inode(sb);
	inode->i_ino = idx;
	inode->i_sb = sb;
	inode->i_op = &tinyfs_inode_ops;

	blk = &block[idx];

	if (S_ISDIR(blk->mode))
		inode->i_fop = &tinyfs_dir_operations;
	else if (S_ISREG(blk->mode))
		inode->i_fop = &tinyfs_file_operations;

#if LINUX_VERSION_CODE > KERNEL_VERSION(4,0,0)
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
#else
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
#endif
	inode->i_private = blk;

	return inode;
}

struct dentry *tinyfs_lookup(struct inode *parent_inode, struct dentry *child_dentry, unsigned int flags)
{
	struct super_block *sb = parent_inode->i_sb;
	struct tiny_file_blk *blk;
	struct tiny_dir_entry *entry;
	int i;

	blk = (struct tiny_file_blk *)parent_inode->i_private;
	entry = (struct tiny_dir_entry *)&blk->data[0];
	for (i = 0; i < blk->dir_children; i++) {
		if (!strcmp(entry[i].filename, child_dentry->d_name.name)) {
			struct inode *inode = tinyfs_iget(sb, entry[i].idx);
			struct tiny_file_blk *inner = (struct tiny_file_blk *)inode->i_private;
			inode_init_owner(inode, parent_inode, inner->mode);
			d_add(child_dentry, inode);
			return NULL;
		}
	}

	return NULL;
}

int tinyfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = dentry->d_inode;
	struct tiny_file_blk *blk = (struct tiny_file_blk *)inode->i_private;

	blk->busy = 0;
	return simple_rmdir(dir, dentry);
}

int tinyfs_unlink(struct inode *dir, struct dentry *dentry)
{
	int i;
	struct inode *inode = dentry->d_inode;
	struct tiny_file_blk *blk = (struct tiny_file_blk *)inode->i_private;
	struct tiny_file_blk *pblk = (struct tiny_file_blk *)dir->i_private;
	struct tiny_dir_entry *entry;

	// 更新其上层目录
	entry = (struct tiny_dir_entry *)&pblk->data[0];
	for (i = 0; i < pblk->dir_children; i++) {
		if (!strcmp(entry[i].filename, dentry->d_name.name)) {
			int j;
			for (j = i; j < pblk->dir_children - 1; j++) {
				memcpy(&entry[j], &entry[j+1], sizeof(struct tiny_dir_entry));
			}
			pblk->dir_children --;
			break;
		}
	}

	blk->busy = 0;
	return simple_unlink(dir, dentry);
}

static struct inode_operations tinyfs_inode_ops = {
	.create = tinyfs_create,
	.lookup = tinyfs_lookup,
	.mkdir = tinyfs_mkdir,
	.rmdir = tinyfs_rmdir,
	.unlink = tinyfs_unlink,
};

int tinyfs_fill_super(struct super_block *sb, void *data, int silent)
{
	struct inode *inode;
	int mode = S_IFDIR;

	inode = new_inode(sb);
	inode->i_ino = 1;
	inode_init_owner(inode, NULL, mode);
	inode->i_sb = sb;
	inode->i_op = &tinyfs_inode_ops;
	inode->i_fop = &tinyfs_dir_operations;
#if LINUX_VERSION_CODE > KERNEL_VERSION(4,0,0)
	inode->i_atime = inode->i_mtime = inode->i_ctime = current_time(inode);
#else
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
#endif

	block[1].mode = mode;
	block[1].dir_children = 0;
	block[1].idx = 1;
	block[1].busy = 1;
	inode->i_private = &block[1];

	sb->s_root = d_make_root(inode);
	curr_count ++;

	return 0;
}

static struct dentry *tinyfs_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
{
	return mount_nodev(fs_type, flags, data, tinyfs_fill_super);
}

static void tinyfs_kill_superblock(struct super_block *sb)
{
	kill_anon_super(sb);
}

struct file_system_type tinyfs_fs_type = {
	.owner = THIS_MODULE,
	.name = "tinyfs",
	.mount = tinyfs_mount,
	.kill_sb = tinyfs_kill_superblock,
};

static int tinyfs_init(void)
{
	int ret;

	memset(block, 0, sizeof(block));
	ret = register_filesystem(&tinyfs_fs_type);
	if (ret)
		printk("register tinyfs failed\n");

	printk("########%s,%d######## \n",__func__,__LINE__);
	return ret;
}

static void tinyfs_exit(void)
{
	unregister_filesystem(&tinyfs_fs_type);
	printk("########%s,%d######## \n",__func__,__LINE__);
}

module_init(tinyfs_init);
module_exit(tinyfs_exit);

MODULE_LICENSE("GPL");


