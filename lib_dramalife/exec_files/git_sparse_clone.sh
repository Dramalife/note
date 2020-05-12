###
# note "git" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Init : 2020.05.12
# 	COPY FROM note/tools/coding/git/sparse_clone.sh
# Update : 2020.05.12
#
#



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
# Update: 2019.07.24 14:00 Rmove "touch tool_name"
# Update: 
# 

## step 0
sed -i "/${1}/d" ./.gitignore
echo "${1}" >> ./.gitignore

## step 1
mkdir $1
cd $1
git init

## step 2
git remote add -f origin ${2}

## step 3
git config core.sparsecheckout true
echo "${1}" >> .git/info/sparse-checkout

## step 4
git pull origin master  

