#
# note tools git related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Ref Url : http://blog.csdn.net/xuyaqun/article/details/49275477
#
# Init	: 2019.07.14 16:37
# Update: 
#	Init : 2019.07.24 COPY from
#		../lib_dramalife/internal_used/sparse_clone_symbol.sh
#		Specific Modified.
#	Update:
#	
# 

#FLODR=${1}
#CONT1=${2}
#CONT2=${3}
FLODR=tcpdump_libpcap
CONT1=tcpdump-4.9.2
CONT2=libpcap-1.9.0

## step 0
touch ./.gitignore
sed -i "/${CONT1}/d" ./.gitignore
sed -i "/${CONT2}/d" ./.gitignore
echo "${CONT1}" >> ./.gitignore
echo "${CONT2}" >> ./.gitignore

## step 1
mkdir ${FLODR}
cd ${FLODR}
git init

## step 2
git remote add -f origin https://github.com/Dramalife/tools_note.git

## step 3
git config core.sparsecheckout true
echo "${CONT1}" >> .git/info/sparse-checkout
echo "${CONT2}" >> .git/info/sparse-checkout

## step 4
git pull origin master  

