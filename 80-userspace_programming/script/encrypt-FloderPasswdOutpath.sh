#!/bin/bash
<<<<<<< HEAD
#By Dramalife@live.com
#DATE:2018/11/24

=======
#
# note en/de-crypt related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Init DATE:2018/11/24
# Version : 2019_0816_2321_OLD

########## USE ##########
>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
#$0:
#$1:src floder-path/current-path-file ,des file-name
#$2:passwd
#$3:des path


#colors
NONE="\e[0m"
BLACK="\e[0;30m"
L_BLACK="\e[1;30m"
RED="\e[0;31m"
L_RED="\e[1;31m"
GREEN="\e[0;32m"
L_GREEN="\e[1;32m"
BROWN="\e[0;33m"
YELLOW="\e[1;33m"
BLUE="\e[0;34m"
L_BLUE="\e[1;34m"
PURPLE="\e[0;35m"
L_PURPLE="\e[1;35m"
CYAN="\e[0;36m"
L_CYAN="\e[1;36m"
GRAY="\e[0;37m"
WHITE="\e[1;37m"
BOLD="\e[1m"
UNDERLINE="\e[4m"
BLINK="\e[5m"
REVERSE="\e[7m"
HIDE="\e[8m"
CLEAR="\e[2J"
CLRLINE="\r\e[K"
color_cyan="\e[0;36m\c"
color_none="\e[0m\c"

pwdstr="[COMMAND]:tat -zcf - ./"$1" | openssl des3 -salt -k "$2" | dd of="$3$1".des3"
pwdstrlen=0
let "pwdstrlen=${#pwdstr}+2"

setcolor()
{
	echo -e $1"\c"
}

printstars_one()
{
	setcolor $BLINK
	echo -e "*\c"
	setcolor $NONE
}

printstars_line()
{	#pint one line '*'
	tmpstrlen=$pwdstrlen
	setcolor $BLINK
	#echo -e $color_cyan
	while [ $tmpstrlen != 0 ]
	do
		echo -e "*\c"
		let tmpstrlen--
	done
	#echo -e $color_none
	setcolor $NONE
}

whoami()
{	#printInStarBlock "USER:"$UID",,,,0 means root"
	result=""
	if [ $UID -eq 0 ]
	then
		result="root"
	else
		result="normal"
	fi
	printInStarBlock "USER:"$result $YELLOW
}

printInStarBlock()
{
	xxlen=${#1}
	yylen=$pwdstrlen
	bblen=0
	let "bblen=yylen - xxlen -2"
	arg2len=${#2}
	printstars_one

	if [ -n "$2" ];		#if arg2 exist
	then
		setcolor $2	#set color to $arg2
	else
		arg2len=8
	fi

	echo -e $1"\c"		#print text
	
	setcolor $NONE		#reset color to $NONE

	if [ $xxlen -lt $yylen ]	#print '*' to filling print-line
	then
		while [ $bblen != 0 ]
		do
			echo -e " \c"
			let bblen--
		done
	fi
	printstars_one
	echo ""
}

print_help()
{
	cat <<EOF
	help ..
	--version
	--1
	--2
EOF
}

<<<<<<< HEAD


=======
>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
##start show
echo -ne "\r"
printstars_line
echo ""
printInStarBlock "#!"$SHELL $BLUE
printInStarBlock $0 $GREEN
whoami
printInStarBlock "$pwdstr"
printInStarBlock `date +%Y%m%d%H%M%S`
#printInStarBlock $pwdstrlen
printstars_line
echo ""
tar -zcf - ./$1 | openssl des3 -salt -k $2 | dd of=$3$1.des3

<<<<<<< HEAD



#NOTE  ,,,, `-lt' means `>='

#FILE END
=======
#FILE END

>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
