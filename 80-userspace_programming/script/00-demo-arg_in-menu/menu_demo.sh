#! /bin/bash

#### clear screen ####
#clear

#### show menu ####
echo "-------"
echo "-------"
echo "-------"

#### read input ####
read arg1

######## switch start ########
case "${arg1}" in
# a case
"E" | "e")
echo "1e"
;;
# a case
"F" | "f")
echo "1f"
;;
# default case
*)
echo "default"
;;
esac
######## switch end ########


