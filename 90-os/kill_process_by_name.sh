#! /bin/bash
#kill -9 $(ps -ef|grep 进程名关键字|gawk '$0 !~/grep/ {print $2}' |tr -s '\n' ' ')
kill -9 $(pidof $1)
