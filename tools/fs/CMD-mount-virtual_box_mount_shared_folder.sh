#! /bin/bash
#
# note "mount virtualbox" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# bash --version
# GNU bash, version 4.3.11(1)-release (i686-pc-linux-gnu)
# Copyright (C) 2013 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# 
# This is free software; you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# ;
#
# $ mount --version
# mount from util-linux 2.20.1 (with libblkid and selinux support)
# ;
#
# Init : ?;
# Update : 2019.04.08;
# Update : 2019.09.18, Add some descriptions ;
#


# DESCRIPTION
# This script may help you to share floder(files) between host pc and virtual pc ;


# USE
# ARGIN -$1 : Filesystem type / name;
# ARGIN -$2 : Local folder as mount point;


# Create local folder :
mkdir ./${2} -m 777 2>/dev/null

# Mount :
sudo mount -t vboxsf ${1} ./${2}

