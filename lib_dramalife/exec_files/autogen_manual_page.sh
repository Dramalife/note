#! /bin/bash
#
# note "manual page" related file
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
# Init : 2019.09.18;
# Update : 2019.11.14, as lib-tool;
# Update : 2020.10.15, Use new terminal color lib - "lib_dramalife.sh";
# Update :
#


# USAGE - TODO
# 1. Change directory to des, create symbollink linking to this file;
# 2. Create list file, for example "man.list";
# 3. Exec, for creating manual page file - run "./SYMBOL_NAME man.list";
#	   for cleaning manual auto created -  "./SYMBOL_NAME";
#
#################################
#	Sample - man.list	#
#################################
#proc
#git cherry-pick
#7 signal
#################################
#
#
#################################
#	Sample - config.in	#
#################################
#PATH_ABS=../../../lib_dramalife/
#TARGET_PATH=./manf
#################################


# Program to generate manual page.
GEN_PROGRAM=man

# Suffix name of each auto-generated file.
TARGET_DNAME=man
# Path of man file
TARGET_PATH=

# Relative path to directory "lib_dramalife"
PATH_ABS=../../lib_dramalife

# Including files
source ./config.in

#source ${PATH_ABS}/terminal_color_bash.sh
export LIB_DRAMALIFE_PWD=../../lib_dramalife/
export LIB_DRAMALIFE_TERMINAL_COLOR_VERSION=5001
source ${LIB_DRAMALIFE_PWD}/lib_dramalife.sh


# CASE : NO ARG IN - CLEAN ALL
if [ ${#} -eq 0 ]
then
echo -e "Press anykey to "${CLRED}"delete"${CNONE}" ALL FILES name end with \"*.${TARGET_DNAME}\":"
read var_unuse30
rm -rvf ${TARGET_PATH}/*.${TARGET_DNAME}
echo -e ${BOLD}"Clean *.${TARGET_DNAME} done."${CNONE}

# CASE : HAVE ARG IN - CREATE 
else
echo -e "Press anykey to "${CLGREEN}"generated"${CNONE}" file(s) automatically:"
read var_unuse30

if [ -z ${TARGET_PATH} ]
then
TARGET_PATH=./
echo "[Init folder] use default. "
else
if [ ${TARGET_PATH} != "./" ]
then
mkdir ${TARGET_PATH}
echo "[Init folder] create folder (${TARGET_PATH})."
fi
echo "[Init folder] init finished, using (${TARGET_PATH})."
fi

while read name
do
#${string//substring/replacement}
${GEN_PROGRAM} ${name} > ${TARGET_PATH}/${name// /_}.${TARGET_DNAME} 2>/dev/null
echo "${GEN_PROGRAM} ${name} > ${name// /_}.${TARGET_DNAME}" 
done < $1

echo -e ${BOLD}"Create *.${TARGET_DNAME} DONE."${CNONE}

fi
