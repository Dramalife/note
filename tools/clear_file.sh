#! /bin/bash
#
# note tools-fileop related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

find ./ -size -20k -exec rm {} \;
find ./ -name *.js -exec rm {} \;
find ./ -name *.css -exec rm {} \;
find ./ -name *.png -exec rm {} \;
find ./ -name *.htm -exec rm {} \;

