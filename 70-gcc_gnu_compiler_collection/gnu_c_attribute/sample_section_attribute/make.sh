#! /bin/bash

SCRIPT=x86.lds
PROGNAME=a_demo.out

case $1 in
a|all)
gcc -c *.c
gcc -o${PROGNAME}  *.o -T ${SCRIPT}
;;

c|clean)
rm -rvf *.o
rm -rvf *.out
;;

esac

