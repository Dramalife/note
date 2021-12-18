#! /bin/bash

# Sample
# ------
# baohua@5b2vdev:~/note/tmp $ ./main_demo.sh -a
# a
# baohua@5b2vdev:~/note/tmp $ ./main_demo.sh -z
# z
# baohua@5b2vdev:~/note/tmp $ ./main_demo.sh -a -z
# a
# z
# baohua@5b2vdev:~/note/tmp $ ./main_demo.sh -az
# *



# if start
if [ ${#} -eq 0 ]
then
echo "var num:${#}"
else

while [ ${#} -gt 0 ]
do
case $1 in
-a)
echo "a"
shift # ponit to next arg
;;

-z)
echo "z"
shift
;;

*)
echo "ARG_*: $1"
shift
;;

esac


done
fi
# if end
