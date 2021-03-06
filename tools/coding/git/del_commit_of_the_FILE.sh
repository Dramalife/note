#! /bin/bash
#
# note git related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

echo "Auto backup file ..."
cp -v $1 /tmp
cp -v $1 .
echo "Auto backup complete, backup yourself !"
read
read
git filter-branch --index-filter "git rm -r --cached --ignore-unmatch  $1" HEAD

