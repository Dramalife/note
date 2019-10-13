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
# Update :
#


source ../../lib_dramalife/terminal_color_bash.sh

# CASE : NO ARG IN - CLEAN ALL
if [ ${#} -eq 0 ]
then
echo -e "Press anykey to "${CLRED}"delete"${CNONE}" auto-generated file(s):"
read var_unuse30
rm -rvf ./*.man
echo -e ${BOLD}"Clean *.man done."${CNONE}

# CASE : HAVE ARG IN - CREATE 
else
echo -e "Press anykey to "${CLGREEN}"generated"${CNONE}" file(s) automatically:"
read var_unuse30
while read name
do
#${string//substring/replacement}
man ${name} > ${name// /_}.man 2>/dev/null
echo "create ${name}.man" 
done < $1
echo -e ${BOLD}"Create *.man done."${CNONE}

fi
