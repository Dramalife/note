#! /bin/bash
#
# note git(local clone) related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

# Clone repository already cloned to local disk.
git clone $1 #ex. ~/disk_ug2t/note

# Change to your clone, and set remote url.
cd $1
git remote set-url origin $2 #ex. https://github.com/git/git.git

