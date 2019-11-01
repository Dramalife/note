#! /bin/bash
#
# note "audit - audit-userspace" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# bash --version
# GNU bash, version 4.4.20(1)-release (x86_64-pc-linux-gnu)
# Copyright (C) 2016 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# 
# This is free software; you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# ;
#
# Init : 2019.11.01;
# Update :
#


# auditd - The Linux Audit daemon
# auditctl - a utility to assist controlling the kernel's audit system
# ausearch - a tool to query audit daemon logs

git clone https://github.com/linux-audit/audit-userspace.git --depth=1 --branch=v2.8.2
