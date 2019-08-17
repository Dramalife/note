#! /bin/bash
#
# note tracing related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Init : 2019.08.16,
# Ref Url : https://blog.csdn.net/benpaozaicaoyuan/article/details/90343719

git filter-branch --index-filter "git rm -r --cached --ignore-unmatch $1" HEAD

