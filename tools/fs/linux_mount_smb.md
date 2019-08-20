### 1 Smbclient
#### 1.1 Install
```shell
root@OrangePizero:~ # apt-get install smbclient
```
#### 1.2 Use
```bash
root@OrangePizero:~ # smbclient -L 192.168.0.102 -U dramalife
Enter dramalife's password:
Domain=[WORKGROUP] OS=[Windows 6.1] Server=[Samba 4.5.12-Debian]

	Sharename       Type      Comment
	---------       ----      -------
	cloud_disk      Disk      cloud_disk
	ug2t-root       Disk      root-path
	movies_open     Disk      Personal files,video.
	IPC$            IPC       IPC Service (NETAC-SERVER server)
	dramalife       Disk      Home directories
Domain=[WORKGROUP] OS=[Windows 6.1] Server=[Samba 4.5.12-Debian]

	Server               Comment
	---------            -------
	MYSERVER             Samba Server Version 4.2.14-Debian
	NETAC-SERVER         NETAC-SERVER server

	Workgroup            Master
	---------            -------
	WORKGROUP            MYSERVER

```
### 2 Mount
#### 2.1 Use
```bash
root@OrangePizero:~ # mount -t cifs //192.168.0.102/ug2t-root ./test/ -o user=***,passwd=***,sec=***
```
#### 2.2 Err : [mount error(13): Permission denied](https://blog.csdn.net/jingxia2008/article/details/50218933/)
密码 hash 格式不对，这样系统一直回报密码错误  
```bash
[602334.718574] CIFS VFS: cifs_mount failed w/return code = -13
```
sec=
          Security mode. Allowed values are:

          ¡¤   none - attempt to connection as a null user (no name)

          ¡¤   krb5 - Use Kerberos version 5 authentication

          ¡¤   krb5i - Use Kerberos authentication and forcibly enable packet signing

          ¡¤   ntlm - Use NTLM password hashing

          ¡¤   ntlmi - Use NTLM password hashing and force packet signing

          ¡¤   ntlmv2 - Use NTLMv2 password hashing

          ¡¤   ntlmv2i - Use NTLMv2 password hashing and force packet signing

          ¡¤   ntlmssp - Use NTLMv2 password hashing encapsulated in Raw NTLMSSP message..

          ¡¤   ntlmsspi - Use NTLMv2 password hashing encapsulated in Raw NTLMSSP message, and force
              packet signing

          The default in mainline kernel versions prior to v3.8 was sec=ntlm. In v3.8, the default
          was changed to sec=ntlmssp.

          If the server requires signing during protocol negotiation, then it may be enabled
          automatically. Packet signing may also be enabled automatically if it's enabled in
          /proc/fs/cifs/SecurityFlags.

#sample
#mount -t cifs //192.168.0.102/ug2t-root ./ug2t-rpi -o user=,passwd=,sec=ntlmssp



#$ mount --version
#mount from util-linux 2.29.2 (libmount 2.29.2: selinux, btrfs, assert, debug)
#$ sudo mount -t cifs //192.168.0.102/ug2t-root ./ug2t-root -o user=xxx,sec=ntlmssp


#### ERR
```bash
# root@NETAC-SERVER:~ # sudo mount -t cifs //192.168.0.104/root500 ./root500_disk/ -o user=,sec=ntlmssp
# mount: wrong fs type, bad option, bad superblock on //192.168.0.104/root500,
# missing codepage or helper program, or other error
# (for several filesystems (e.g. nfs, cifs) you might
#  need a /sbin/mount.<type> helper program)
# 
# In some cases useful info is found in syslog - try
# dmesg | tail or so.

apt-get install cifs-utils
```
