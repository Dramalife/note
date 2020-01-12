#! /bin/bash
#
# note "samba,firewall(ufw)" related file
# Copyright (C) 2019 Dramalife <dramalife@live.com>
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# bash --version
# GNU bash, version 4.4.19(1)-release (arm-unknown-linux-gnueabihf)
# Copyright (C) 2016 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# 
# This is free software; you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# ;
#
# Init : 2020.01.12
#	Ref : https://www.mokeyjay.com/archives/2514?replytocom=11960;
# Update :
#


# Show status
ufw status
# Add rule
ufw allow 445
# Reload
ufw reload
