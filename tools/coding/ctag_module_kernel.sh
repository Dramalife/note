#! /bin/bash
#
# note tools-coding-ctags related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

echo "input module path"
read module
echo "input kernel path"
read kernel

ln -s ${kernel} ${module}/kernel_link
cd ${module}
ctags -R

