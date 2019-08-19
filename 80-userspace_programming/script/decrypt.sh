#!/bin/bash
<<<<<<< HEAD
=======
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
>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277

#$0:arg0:sourceN
#$1:arg1:password

<<<<<<< HEAD

#tar -zcf - ./$0/* | openssl des3 -salt -k $1 | dd of=$0.des3
dd if=$1 | openssl des3 -d -k $2 | tar zxf -




#tar -zcf - ./EML-AL00/* | openssl des3 -salt -k $PASSWD | dd of=$FILENAME.des3
#dd if=$FILENAME.des3 | openssl des3 -d -k $PASSWD | tar zxf -
#nohup tar -zcf - ./36-12.0-direct/* | openssl des3 -salt -k moxing | dd of=36-12.0-direct.des3 > ./36.log 2>&1 &
=======
#tar -zcf - ./$0/* | openssl des3 -salt -k $1 | dd of=$0.des3
dd if=$1 | openssl des3 -d -k $2 | tar zxf -

>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
