#! /bin/bash
#
# note coding-vim related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.


#without binary files, without \.svn paths, color=auto
grep "${1}" ${2} -rn --binary-files=without-match --exclude-dir=\.svn --color=atuo

