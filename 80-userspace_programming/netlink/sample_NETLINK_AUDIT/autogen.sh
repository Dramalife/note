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
# GNU bash, version 4.4.20(1)-release (x86_64-pc-linux-gnu)
# Copyright (C) 2016 Free Software Foundation, Inc.
# License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
# 
# This is free software; you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.
# ;
#
# TODO : Add symbol links to gitignore list! 
#
# Init : 2019.11.02;
# Update : 2019.11.08;
# Update :
#



source ../../lib_dramalife/terminal_color_bash.sh


AUDIT_SOURCE_ROOT=/home/dramalife/temp2/audit-userspace
AUDIT_PREFIX_ROOT=${AUDIT_SOURCE_ROOT}/prefix
LINK_NAME_SO=libaudit.so
LINK_NAME_SOURCE=libaudit-source


# CASE : NO ARG IN - CREATE SYMBOL LINK(s)
if [ ${#} -eq 0 ]
then
echo -e "Press anykey to "${CLGREEN}"CREATE"${CNONE}" auto-generated file(s):"
read var_unuse30
# lib depend
ln -s ${AUDIT_PREFIX_ROOT}/lib/${LINK_NAME_SO} ./${LINK_NAME_SO}
# lib source for ctags*
ln -s ${AUDIT_SOURCE_ROOT}/lib/ ./${LINK_NAME_SOURCE}
echo -e ${BOLD}"Create symbol done."${CNONE}

# CASE : HAVE ARG IN - CLEAN
else
echo -e "Press anykey to "${CLRED}"CLEAN"${CNONE}" file(s) automatically:"
read var_unuse30
rm -rvf ./${LINK_NAME_SO} ./${LINK_NAME_SOURCE}
echo -e ${BOLD}"Clean symbol done."${CNONE}

fi
