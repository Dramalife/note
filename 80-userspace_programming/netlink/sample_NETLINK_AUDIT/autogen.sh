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
# TODO;
#
# Init : 2019.11.02;
# Update :
#



# lib depend
ln -s /home/dramalife/temp2/audit-userspace/prefix/lib/libaudit.so ./libaudit.so

# lib source for ctags*
ln -s /home/dramalife/temp2/audit-userspace/lib/ ./libaudit-source
