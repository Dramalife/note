#! /bin/bash
#
# note "ip" related file
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
# Init : 2019.10.23;
# Update : 2020.10.15; Change terminal color lib to "lib_dramalife.sh";
# Update :
#



# LIB FOR COLOUR
#source ../../../lib_dramalife/terminal_color_bash.sh
export LIB_DRAMALIFE_PWD=~/note/lib_dramalife/
export LIB_DRAMALIFE_TERMINAL_COLOR_VERSION=5001
source ${LIB_DRAMALIFE_PWD}/lib_dramalife.sh


# ARG1 - DEV NAME NOW
NAMENOW=${1}
# ARG2 - NEW DEV NAME
NEWNAME=${2}


# STATUS SHOW
echo -e ${CLGREEN}"Link now: \r"${CNONE}
ip link show

# WARNING SHOW
echo -e ${WHITE}"Command below will run :"${CNONE}
#TODO : Keep same with "# PROCESS" manually !
echo 	"\"sudo ip link set dev ${NAMENOW} name ${NEWNAME} \""
echo -e ${WHITE}"Press anykey to continue:"${CNONE}

# CONFIRM
read

# PROCESS
sudo ip link set dev ${NAMENOW} name ${NEWNAME}

# RESULT SHOW
if [ $? -ne 0 ]; then
echo -e ${CLRED}"Failed !"${CNONE}
else
echo -e ${CLGREEN}"Succeed !"${CNONE}
fi
# EOF
