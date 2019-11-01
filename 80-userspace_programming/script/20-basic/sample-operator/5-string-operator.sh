#!/bin/bash
# author:²ËÄñ½Ì³Ì
# url:www.runoob.com

a="abc"
b="efg"

echo -e "\nNOTE:
=  : equal
!= : not equal
-z : str-len ZERO
-n : str-len NOT ZERO
$  : null?
"

if [ $a = $b ]
then
echo "$a = $b : a is equal to b"
else
echo "$a = $b: a is not equal to b"
fi

if [ $a != $b ]
then
echo "$a != $b : a is not equal to b"
else
echo "$a != $b: a is equal to b"
fi

if [ -z $a ]
then
echo "-z $a : string length is 0"
else
echo "-z $a : string length is not 0"
fi

if [ -n "$a" ]
then
echo "-n $a : string length is not 0"
else
echo "-n $a : string length is 0"
fi

if [ $a ]
then
echo "$a : string is not null"
else
echo "$a : string is null"
fi
