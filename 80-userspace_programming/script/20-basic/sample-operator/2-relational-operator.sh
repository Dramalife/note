#!/bin/bash
# author:²ËÄñ½Ì³Ì
# url:www.runoob.com

a=10
b=20

echo "NOTE:
# -eq : equal            | ==
# -ne : not equal        | !=
# -gt : greater than     | >
# -lt : little than      | <
# -ge : greater OR equal | >=
# -le : little OR equal  | <=
"

if [ $a -eq $b ]
then
echo "$a -eq $b : a is equal to b"
else
echo "$a -eq $b: a is not equal to b"
fi

if [ $a -ne $b ]
then
echo "$a -ne $b: a is not equal to b"
else
echo "$a -ne $b : a is equal to b"
fi

if [ $a -gt $b ]
then
echo "$a -gt $b: a is greater than b"
else
echo "$a -gt $b: a is not greater than b"
fi

if [ $a -lt $b ]
then
echo "$a -lt $b: a is little than b"
else
echo "$a -lt $b: a is not little than b"
fi

if [ $a -ge $b ]
then
echo "$a -ge $b: a is greater or equal than b"
else
echo "$a -ge $b: a is neither greater nor equal(little) than b"
fi

if [ $a -le $b ]
then
echo "$a -le $b: a is little or equal than b"
else
echo "$a -le $b: a is neither little nor equal(greater) than  b"
fi
