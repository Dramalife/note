#! /bin/bash
#
# note "TODO" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# bash --version
# TODO;
#
# Init : TODO;
# Update :
#


if [ ${#} -eq 0 ]
then
rm -rvf ./*.man
echo "clean *.man done."
else

while read name
do
man ${name} > ${name}.man 2>/dev/null
echo "create ${name}.man" 
done < $1
echo "create *.man done."

fi
