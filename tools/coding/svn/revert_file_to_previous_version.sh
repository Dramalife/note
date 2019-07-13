#! /bin/bash
#
# note tools svn related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Init	: 2019.07.13 14:45
#

# Sample :
# svn merge -r 1002:1001 apps/filea.c
svn merge -r ${REVISION_NOW}:${REVISION_PREV} ${1}

svn commit -m"${2}"

