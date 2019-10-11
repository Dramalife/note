#! /bin/bash
#
# note "rtc - hwclock" related file
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
# Init : 2019.10.10;
# Update :
#



# For more
# man 8 hwclock

# Read the Hardware Clock and print its time to standard output in the ISO 8601 format.		(-r, --show, --get)
hwclock --show

# Set the System Clock from the Hardware Clock.							(-s, --hctosys)
# hwclock --hctosys

# Set the Hardware Clock from the System Clock, and update the  timestamps  in  /etc/adjtime.	(-w, --systohc)
# hwclock --systohc

# Exapmpe 1:
# hwclock -wf /dev/rtc0

