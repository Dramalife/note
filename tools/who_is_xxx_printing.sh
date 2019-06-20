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
#

echo "Input tty device(PATH)"
read tty
# List open files
lsof ${tty}

echo "Select one(PID) to trace"
read one
# -f : follow forks,
strace -f -p ${one}

