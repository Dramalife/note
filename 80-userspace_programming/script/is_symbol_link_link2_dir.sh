#! /bin/bash
#
# note "shell script" related file
# Copyright (C) 2019 Dramalife <dramalife@live.com>
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# $ gcc --version
# gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
# Copyright (C) 2017 Free Software Foundation, Inc.
# This is free software; see the source for copying conditions.  There is NO
# warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# ;
# 
# $ uname -a
# Linux iZ2zeeq1jai7e6qn7xqrnuZ 4.15.0-96-generic #97-Ubuntu SMP Wed Apr 1 03:25:46 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
# ;
#
#
# Ref : 
# 	/80-userspace_programming/20-basic/sample-operator/3-boolean-operator.sh
# 	/80-userspace_programming/20-basic/sample-operator/6-file-testing-operator.sh
#



file=$1

if [ -L $file -a -d $file ] ; then
	echo "$file is a symbol link linking to directory!"
elif [ ! -L $file -a -d $file ] ; then
	echo "$file is a directory, not symbol link!"
else
	echo "$file is neither a directory nor symbol link!"
fi
