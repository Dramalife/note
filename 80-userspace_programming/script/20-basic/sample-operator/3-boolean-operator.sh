#!/bin/bash
# author:²ËÄñ½Ì³Ì
# url:www.runoob.com

a=10
b=20

echo "NOTE:
# !  : not
# -o : or
# -a : and
"

echo -e "\na=${a},b=${b}"
if [ $a != $b ]
then
echo "$a != $b : a is not equal to b"
else
echo "$a == $b: a is equal to b"
fi

echo -e "\n# a<100 AND b>15"
if [ $a -lt 100 -a $b -gt 15 ]
then
echo "$a is little than 100 AND $b is greater than 15 : return true"
else
echo "$a is little than 100 AND $b is greater than 15 : return false"
fi

echo -e "\n# a<100 OR b>100"
if [ $a -lt 100 -o $b -gt 100 ]
then
echo "$a is little than 100 OR $b is greater than 100 : return true"
else
echo "$a is little than 100 OR $b is greater than 100 : return false"
fi

echo -e "\n# a<5 OR a>100"
if [ $a -lt 5 -o $b -gt 100 ]
then
echo "$a is little than 5 OR $b is greater than 100 : return true"
else
echo "$a is little than 5 OR $b is greater than 100 : return false"
fi
