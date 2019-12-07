#! /bin/bash
#
# note "shell pipe" related file
# Copyright (C) 2019 Dramalife <dramalife@live.com>
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
# Init : 2019.12.07;
#	Ref : THE LINUX PROGRAMMING INTERFACE ;
# Update :
#



# Source print related library
source ../../../lib_dramalife/print_lib/dramalife_terminal_color.sh

# Show and Exec the command
CMD='ls | wc -l'
echo -e "${L_CYAN}Command :${CNONE} ${CMD} \n${L_CYAN}result:${CNONE}"
eval ${CMD}
