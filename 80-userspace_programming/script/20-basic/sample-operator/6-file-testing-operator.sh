#!/bin/bash
# author:²ËÄñ½Ì³Ì
# url:www.runoob.com

file="/var/www/runoob/test.sh"

echo -e "\nNOTE:
| Operator| Description | Sample                    |
|---------|-------------|-------------------------- |
| -b file | block?	| [ -b $file ] return false.|
| -c file | char?	| [ -c $file ] return false.|
| -d file | directory?	| [ -d $file ] return false.|
| -f file | neither directory nor device
	    		| [ -f $file ] return true .|
| -g file | SGID?	| [ -g $file ] return false.|
| -k file | Sticky Bit?	| [ -k $file ] return false.|
| -p file | pipe?	| [ -p $file ] return false.|
| -u file | SUID?	| [ -u $file ] return false.|
| -r file | read?	| [ -r $file ] return true .|
| -w file | write?	| [ -w $file ] return true .|
| -x file | exec?	| [ -x $file ] return true .|
| -s file | size>0?	| [ -s $file ] return true .|
| -e file | existing?	| [ -e $file ] return true .|
"

if [ -r $file ]
then
echo "The file is readable"
else
echo "The file is un-readable"
fi

if [ -w $file ]
then
echo "The file is writable"
else
echo "The file is un-writable"
fi

if [ -x $file ]
then
echo "The file is executable"
else
echo "The file is un-executable"
fi

if [ -f $file ]
then
echo "The file is a NORMAL file"
else
echo "The file is a SPECIAL file"
fi

if [ -d $file ]
then
echo "The file is a DIRECTORY"
else
echo "The file is not a DIRECTORY"
fi

if [ -s $file ]
then
echo "File content is not blank"
else
echo "File content is blank"
fi

if [ -e $file ]
then
echo "File exists"
else
echo "File is not existing"
fi
