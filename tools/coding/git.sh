#! /bin/sh

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

