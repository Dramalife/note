#!/bin/bash
# author:²ËÄñ½Ì³Ì
# url:www.runoob.com

a=10
b=20

echo "NOTE:
&& : AND
|| : OR
"

echo -e "\nCMD-var-converted:
if [[ ${a} -lt 100 && ${b} -gt 100 ]]"
if [[ ${a} -lt 100 && ${b} -gt 100 ]]
then
echo "return true"
else
echo "return false"
fi

echo -e "\nCMD-var-converted:
if [[ ${a} -lt 100 || ${b} -gt 100 ]]"
if [[ ${a} -lt 100 || ${b} -gt 100 ]]
then
echo "return true"
else
echo "return false"
fi
