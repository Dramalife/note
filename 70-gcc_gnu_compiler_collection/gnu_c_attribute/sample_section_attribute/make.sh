#! /bin/bash
#
# note gcc attribute-section related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#

SCRIPT=x86.lds
PROGNAME=a_demo.out

case $1 in

# make all
a|all)
gcc -c *.c
gcc -o${PROGNAME}  *.o -T ${SCRIPT}
;;

# make clean
c|clean)
rm -rvf *.o
rm -rvf *.out
;;

# read section headers
S|section-headers)
gcc -c *.c
readelf -S *.o ${PROGNAME}
;;

# help
*)
echo "em..."
;;

esac

