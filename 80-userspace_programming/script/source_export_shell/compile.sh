#! /bin/bash
#
# note "source & export" related file
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
# Init : 2019.09.13;
# Update :
#


source ./pub.mk

VAR_SH=var_in_sh
export EX_SH=export_in_sh


echo ""
echo ""
echo "print from shell.........."
echo "VAR____IN_SOURCE:"${VAR_SC}
echo "EXPORT_IN_SOURCE:"${EX_SC}
echo "VAR____IN_SHELL :"${VAR_SH}
echo "EXPORT_IN_SHELL :"${EX_SH}
echo "print end................."
echo ""
echo ""


cd ./app
make
