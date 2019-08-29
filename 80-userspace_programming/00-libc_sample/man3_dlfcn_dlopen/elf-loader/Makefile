#
# note "elf-loader" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# $ bash --version
# GNU bash, version 4.3.11(1)-release (i686-pc-linux-gnu)
# Copyright (C) 2013 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# 
# This is free software; you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# 
#
# Related : /70-gcc_gnu_compiler_collection/tips/gcc_placement_of_the_-l_option.md
#
#
# Init : 2019.08.29, COPY FROM : https://github.com/21cnbao/training  ;
# Update :
#


all: loader elf
loader: loader.c
	#gcc -m32 -g -Wall -ldl -o loader loader.c #error
	gcc -m32 -g -Wall -o loader loader.c -ldl #ok
elf: elf.c
	gcc -m32 -pie -fPIE -o elf elf.c
clean:
	rm -rvf loader elf


######## Environment ########


# $ uname -a
# Linux ubuntu 4.0.0-040000-generic #201504121935 SMP Sun Apr 12 23:58:08 UTC 2015 i686 i686 i686 GNU/Linux


#$ make --version
#GNU Make 3.81
#Copyright (C) 2006  Free Software Foundation, Inc.
#This is free software; see the source for copying conditions.
#There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A
#PARTICULAR PURPOSE.
#
#This program built for i686-pc-linux-gnu


# $ gcc --version
# gcc-4.8.real (Ubuntu 4.8.5-4ubuntu8~14.04.2) 4.8.5
# Copyright (C) 2015 Free Software Foundation, Inc.
# This is free software; see the source for copying conditions.  There is NO
# warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


# $ git diff .
# diff --git a/toolchain/elf-loader/Makefile b/toolchain/elf-loader/Makefile
# index 214aa29..a2875c8 100644
# --- a/toolchain/elf-loader/Makefile
# +++ b/toolchain/elf-loader/Makefile
# @@ -1,5 +1,8 @@
# all: loader elf
# loader: loader.c
# -       gcc -m32 -g -Wall -ldl -o loader loader.c
# +       #gcc -m32 -g -Wall -ldl -o loader loader.c #error
# +       gcc -m32 -g -Wall -o loader loader.c -ldl #ok
# elf: elf.c
# gcc -m32 -pie -fPIE -o elf elf.c
# +clean:
# +       rm -rvf loader elf

