#! /bin/bash
#
# note "rootfs-backup" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# bash --version
# GNU bash, version 4.4.12(1)-release (arm-unknown-linux-gnueabihf)
# Copyright (C) 2016 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# 
# This is free software; you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# ;
#
# Init : 2019.09.07;
# Update :
#


echo "TODO : umount samba, or add it to exclude-path first !"

if [ ${#} -gt 0 ]; then
BK_OUTPUT_FILE=${1}
else
BK_OUTPUT_FILE=/$(date +%Y%m%d%H).tgz
fi

nohup tar zcvfp ${BK_OUTPUT_FILE} \
/* \
--exclude=/proc \
--exclude=/lost+found \
--exclude=${BK_OUTPUT_FILE} \
--exclude=/mnt \
--exclude=/sys \
--exclude=/sharedfolders \
--exclude=/srv \
&

