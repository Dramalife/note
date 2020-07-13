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
# Init : 2019.11.19, COPY FORM : (this repo)/autogen_manual_page.sh ;
# Update : 2019.11.20, 
#		Using new shell lib "note/../dramalife_terminal_color.sh";
#		Change variable name : PATH_ABS => RELATIVE_PATH_TO_LIB_DRAMALIFE;
# Update :
#


# USAGE - TODO
# 1. Change directory to des, create symbollink linking to this file;
# 2. Create list file, for example "man.list";
# 3. Exec, for creating manual page file - run "./SYMBOL_NAME man.list";
#	   for cleaning manual auto created -  "./SYMBOL_NAME";
#
#################################
#	Sample - headers.list	#
#################################
#/usr/lib/gcc/x86_64-linux-gnu/7/include
#/usr/local/include
#/usr/lib/gcc/x86_64-linux-gnu/7/include-fixed
#/usr/include/x86_64-linux-gnu
#/usr/include
#################################
#
#
#################################
#	Sample - config.in	#
#################################
RELATIVE_PATH_TO_LIB_DRAMALIFE=~/note/lib_dramalife/
TARGET_PATH=./folder_headers
TARGET_DNAME=dl_headers
##DATA_FILE_PWD=${RELATIVE_PATH_TO_LIB_DRAMALIFE}/data_pub/headers_gcc_userspace.ubuntuserver18.list
DATA_FILE_PWD=${RELATIVE_PATH_TO_LIB_DRAMALIFE}/data_pub/$(uname -r).list
#################################


# Program to generate manual page.
GEN_PROGRAM="ln -s"

# Suffix name of each auto-generated file.
TARGET_DNAME=headers
# Path of auto-generated file
#TARGET_PATH=

# Relative path to directory "lib_dramalife"
#RELATIVE_PATH_TO_LIB_DRAMALIFE=../../lib_dramalife
RELATIVE_PATH_TO_LIB_DRAMALIFE=~/note/lib_dramalife

# Including files
CONFIG_FILE=./config.in
if [ -e ${CONFIG_FILE} ]
then
	source ${CONFIG_FILE}
else
	echo -e ${CLRED}"WARNING:"${CNONE}"!!..."
fi

source ${RELATIVE_PATH_TO_LIB_DRAMALIFE}/terminal_lib/dramalife_terminal_color.sh

# PATH OF LIST FILE (headers_xxx.list)
DATA_FILE_PWD=${RELATIVE_PATH_TO_LIB_DRAMALIFE}/data_pub/headers_gcc_userspace.ubuntuserver18.list


fun_mk_folder()
{
	target_funmkfolder=${1}
	if [ -z ${target_funmkfolder} ]
	then
		target_funmkfolder=./
		echo "[Init folder] use default. "
	else
		if [ ${target_funmkfolder} != "./" ]
		then
			mkdir ${target_funmkfolder}
			echo "[Init folder] create folder (${target_funmkfolder})."
		fi
		echo "[Init folder] init finished, using (${target_funmkfolder})."
	fi
}

fun_mk_symbollink()
{
	target_funmksymbollink=${1}
	if [ -z ${target_funmksymbollink} ]
	then
		echo "[Init folder] err **. "
	else
		if [ ${target_funmksymbollink} != "./" ]
		then
			mkdir ${target_funmksymbollink}
			echo "[Init folder] create folder (${target_funmksymbollink})."
		fi
		echo "[Init folder] init finished, using (${target_funmksymbollink})."
	fi
}

clean_autogen_files()
{
	echo -e "Press anykey to "${CLRED}"delete"${CNONE}" ALL FILES name end with \"*.${TARGET_DNAME}\":"
	read var_unuse30
	rm -rvf ${TARGET_PATH}/*.${TARGET_DNAME}
	rmdir ${TARGET_PATH}
	echo -e ${BOLD}"Clean *.${TARGET_DNAME} done."${CNONE}
}

generate_files()
{
	echo -e "Press anykey to "${CLGREEN}"generated"${CNONE}" file(s) automatically:"
	read var_unuse30
	
	fun_mk_folder ${TARGET_PATH}
	#ln -s ${DATA_FILE_PWD} .
	
	while read name
	do
	#${string//substring/replacement}
	echo "${GEN_PROGRAM} ${name} ./${TARGET_PATH}/${name//\//_}.${TARGET_DNAME}"
	${GEN_PROGRAM} ${name} ./${TARGET_PATH}/${name//\//_}.${TARGET_DNAME}
	done < ${DATA_FILE_PWD}
	
	echo -e ${BOLD}"Create *.${TARGET_DNAME} DONE."${CNONE}
}

print_help()
{
	echo -e ${BOLD}"HELP:"${CNONE}
	echo "${THIS_PROCESS_NAME}"" generate	: generate files."
	echo "${THIS_PROCESS_NAME}"" clean	: clean files."
}


#######################################
#		START		      #
#######################################
THIS_PROCESS_NAME=${0}
# CASE : NO ARG IN - CLEAN ALL
if [ ${#} -eq 0 ]
then
	print_help
# CASE : HAVE ARG IN - CREATE 
else

	while [ ${#} -gt 0 ]
	do
		case ${1} in

		generate)
		generate_files
		shift
		;;

		clean)
		clean_autogen_files
		shift
		;;

		*)
		print_help
		shift
		;;

		esac
	done

	
fi
################ *END* ################
