#! /bin/bash

clear

echo "-------"
echo "-------"
echo "-------"

read arg1

# switch start
case "${arg1}" in

"E" | "e")
echo "1e"
;;

"F" | "f")
echo "1f"
;;

*)
echo "default"
;;

esac
# switch end


