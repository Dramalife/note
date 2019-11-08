#! /bin/bash
#
# note "audit" related file
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
# TODO : Add symbol links to gitignore list! 
#
# Init : 2019.11.02;
# Update : 2019.11.08;
# Update :
#



# lib depend
ln -s /home/dramalife/temp2/audit-userspace/prefix/lib/libaudit.so ./libaudit.so

# lib source for ctags*
ln -s /home/dramalife/temp2/audit-userspace/lib/ ./libaudit-source
