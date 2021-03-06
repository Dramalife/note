#! /bin/sh
#
# note coding-vim related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
#
#
#
# 1. Base Configuration
# --------
# --system : all user(local machine)
# --golbal : current user
# --local  : current path
# --list   : show current cfg
git config --list
git config --global user.name "Dramalife"
git config --global user.email dramalife@live.com

# 2. Create an empty Git repository or reinitialize an existing one
# --------
#git init

# 3. Clone a respository
# --------
# 3.1 remote copy
# 	git clone https://github.com/Dramalife/note.git
# 3.2 local copy .step1
# 	git clone ../note/ ./note/
# 	git remote set-url origin https://github.com/Dramalife/note.git

# 4. Status
# ______________________________________________________________________________________________________
# |Status				|operate			|de-operate			|
# |-------------------------------------|-------------------------------|-------------------------------|
# |					|EDIT FILE			|git checkout <file>		|
# |-------------------------------------|-------------------------------|-------------------------------|
# |Untracked files			|git add <file>		  	|git reset HEAD <file>	 	|
# |-------------------------------------|-------------------------------|-------------------------------|
# |Changes to be committed		|git commit -m"xx" <file>/-a  	|git revert HEAD		|
# |-------------------------------------|-------------------------------|-------------------------------|
# |					|git push		 	|				|
# |-------------------------------------|-------------------------------|-------------------------------|
# |					|				|
# ```````````````````````````````````````````````````````````````````````````````````````````````````````


# Changes not staged for commit:
#  	(use "git add <file>..." to update what will be committed)
#   	(use "git checkout -- <file>..." to discard changes in working directory)#####################git check file
#    	modified:   test2/test2.txt
# Your branch is ahead of 'origin/master' by 1 commit.(use "git push" to publish your local commits)


git status
# git status -uno #Show no untracked files
# git clean -d -n #Del untracked files(-n just show, -i really clean!!)
# git clean -i ./ #clean current path untracked files.


# Git Local-Version-Control
# git clone /sourcepath/note /destpath/
# cd /destpath/note
# $edit file
# git add # -u : update tracked files
# git commit
# git branch local_branch
# git push
# cd /sourcepath/note
# git merge local_branch master
# git push


# Git Local Branch Push
# git branch br_test_local_add	# Add branch at local disk
# git checkout br_test_local_add	# switch to the branch just added
# git push origin			# push the branch to remote
# git push --set-upstream origin br_test_local_add_20190526	# automatic push to remote
# ---Merge
# git checkou master
# git merge br_test_local_add	# this will create a push at master
# git push

