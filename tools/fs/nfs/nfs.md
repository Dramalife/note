REF : https://www.cnblogs.com/becool-168-com/p/11430243.html
REF : https://blog.csdn.net/qq_37860012/article/details/86717891

## Install
```bash
# nfs-utils：包含NFS服务端守护进程和NFS客户端的工具
# rpcbind：提供RPC的端口映射的守护进程及其相关文档、执行文件等
#
# RedHat / CentOS
yum -y install nfs-utils rpcbind
#
# Debian / Ubuntu
# Server
apt-get install nfs-kernel-server
# Client
apt-get install nfs-common
```


## EXPORTS(5)
exports - NFS server export table
### Sample - /etc/exports
```diff
+ /PATH/TO/EXPORT/PATH     192.168.0.0/24(rw,async,no_root_squash)
```




### General Options
```man
rw     Allow both read and write requests on this NFS volume. The default is to disallow any request which changes the filesystem.   This  can  also  be  made
	explicit by using the ro option.

async  This option allows the NFS server to violate the NFS protocol and reply to requests before any changes made by that request have been committed to sta‐
	ble storage (e.g. disc drive).

	Using this option usually improves performance, but at the cost that an unclean server restart (i.e. a crash) can cause data to be lost or corrupted.

sync   Reply to requests only after the changes have been committed to stable storage (see async above).

	In releases of nfs-utils up to and including 1.0.0, the async option was the default.  In all releases after 1.0.0, sync is the default, and async must
	be explicitly requested if needed.  To help make system administrators aware of this change, exportfs will issue a warning if neither sync nor async is
	specified.
```
### User ID Mapping
```man
nfsd bases its access control to files on the server machine on the uid and gid provided in each NFS RPC request. The normal behavior a user would  expect  is
that  she  can  access her files on the server just as she would on a normal file system. This requires that the same uids and gids are used on the client and
the server machine. This is not always true, nor is it always desirable.

Very often, it is not desirable that the root user on a client machine is also treated as root when accessing files on the NFS server. To this end, uid  0  is
normally  mapped  to a different id: the so-called anonymous or nobody uid. This mode of operation (called `root squashing') is the default, and can be turned
off with no_root_squash.

By default, exportfs chooses a uid and gid of 65534 for squashed access. These values can also be overridden by the anonuid and anongid options.  Finally, you
can map all user requests to the anonymous uid by specifying the all_squash option.

Here's the complete list of mapping options:

root_squash
	Map  requests from uid/gid 0 to the anonymous uid/gid. Note that this does not apply to any other uids or gids that might be equally sensitive, such as
	user bin or group staff.

no_root_squash
	Turn off root squashing. This option is mainly useful for diskless clients.

all_squash
	Map all uids and gids to the anonymous user. Useful for NFS-exported public FTP directories, news  spool  directories,  etc.  The  opposite  option  is
	no_all_squash, which is the default setting.

anonuid and anongid
	These  options  explicitly  set the uid and gid of the anonymous account.  This option is primarily useful for PC/NFS clients, where you might want all
	requests appear to be from one user. As an example, consider the export entry for /home/joe in the example section below, which maps  all  requests  to
	uid 150 (which is supposedly that of user joe).
```

## Others
firewall
```bash
# Ubuntu
ufw allow 2049
```
