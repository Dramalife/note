> \# note "systemd-resolved" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.09.26;  
\# Update   
\#  
  


### Way 1. Using commanl line

```bash
root@server:/home/dramalife/note/90-operating_system/systemd/systemd-resolved# systemctl disable systemd-resolved.service
Removed /etc/systemd/system/dbus-org.freedesktop.resolve1.service.
Removed /etc/systemd/system/multi-user.target.wants/systemd-resolved.service.

root@server:/home/dramalife/note/90-operating_system/systemd/systemd-resolved# systemctl enable systemd-resolved.service
Created symlink /etc/systemd/system/dbus-org.freedesktop.resolve1.service → /lib/systemd/system/systemd-resolved.service.
Created symlink /etc/systemd/system/multi-user.target.wants/systemd-resolved.service → /lib/systemd/system/systemd-resolved.service.

root@server:/home/dramalife/note/90-operating_system/systemd/systemd-resolved# systemctl --version
systemd 237
+PAM +AUDIT +SELINUX +IMA +APPARMOR +SMACK +SYSVINIT +UTMP +LIBCRYPTSETUP +GCRYPT +GNUTLS +ACL +XZ +LZ4 +SECCOMP +BLKID +ELFUTILS +KMOD -IDN2 +IDN -PCRE2 default-hierarchy=hybrid
```

### Way 2. Modifying files directly

```bash
# Disable
rm /etc/systemd/system/dbus-org.freedesktop.resolve1.service.
rm /etc/systemd/system/multi-user.target.wants/systemd-resolved.service.
# Enable 
ln -s /etc/systemd/system/dbus-org.freedesktop.resolve1.service   /lib/systemd/system/systemd-resolved.service.
ln -s /etc/systemd/system/multi-user.target.wants/systemd-resolved.service   /lib/systemd/system/systemd-resolved.service.
```

