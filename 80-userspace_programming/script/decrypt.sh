#!/bin/bash
#
# note en/de-crypt related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Init DATE:2018/11/24
# Version : 2019_0816_2321_OLD

#$0:arg0:sourceN
#$1:arg1:password

#tar -zcf - ./$0/* | openssl des3 -salt -k $1 | dd of=$0.des3
dd if=$1 | openssl des3 -d -k $2 | tar zxf -

