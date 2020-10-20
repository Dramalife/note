#! /bin/bash
#
# note "lib_dramalife" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# $ bash --version
# GNU bash, version 4.4.20(1)-release (x86_64-pc-linux-gnu)
# Copyright (C) 2016 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# 
# This is free software; you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# ;
#
# Init : 2019.11.14;
# Update : 2020.01.12
#	Fixed problem that path error when including this library.
# Update :
#


#########################################################
# 		Tips for VIM only			#
#########################################################
# :match DiffText /LIB_DRAMALIFE_PWD/

#########################################################
# 			Note				#
#########################################################
# The variable "LIB_DRAMALIFE_PWD" 
# used to determined path from user to this library 
# is managed by user.

#########################################################
#		Usage (Shell)				#
#########################################################
#export LIB_DRAMALIFE_PWD=../../lib_dramalife/
#export LIB_DRAMALIFE_TERMINAL_COLOR_VERSION=5001
#export LIB_DRAMALIFE_TERMINAL_COLOR_VERSION=5002
#source ${LIB_DRAMALIFE_PWD}/lib_dramalife.sh


if [ ! ${LIB_DRAMALIFE_PWD} ]
then
	LIB_DRAMALIFE_PWD=~/note/
fi

if [ ! ${LIB_DRAMALIFE_TERMINAL_COLOR_VERSION} ]
then
	LIB_DRAMALIFE_TERMINAL_COLOR_VERSION=0
fi

if [ ${LIB_DRAMALIFE_TERMINAL_COLOR_VERSION} = 5001 ]
then
source ${LIB_DRAMALIFE_PWD}/terminal_lib/dlterm_5001.sh
fi

if [ ${LIB_DRAMALIFE_TERMINAL_COLOR_VERSION} = 5002 ]
then
source ${LIB_DRAMALIFE_PWD}/terminal_lib/dlterm_5002.sh
fi

