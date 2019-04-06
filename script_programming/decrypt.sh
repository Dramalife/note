#!/bin/bash

#$0:arg0:sourceN
#$1:arg1:password


#tar -zcf - ./$0/* | openssl des3 -salt -k $1 | dd of=$0.des3
dd if=$1.des3 | openssl des3 -d -k $2 | tar zxf -




#tar -zcf - ./EML-AL00/* | openssl des3 -salt -k $PASSWD | dd of=$FILENAME.des3
#dd if=$FILENAME.des3 | openssl des3 -d -k $PASSWD | tar zxf -
#nohup tar -zcf - ./36-12.0-direct/* | openssl des3 -salt -k moxing | dd of=36-12.0-direct.des3 > ./36.log 2>&1 &
