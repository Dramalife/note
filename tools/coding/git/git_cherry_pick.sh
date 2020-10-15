#! /bin/bash
#
# note "git cherry-pick" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Init : 2019.08.22,
#		Source "note/lib_dramalife/terminal_color_bash.sh";
#		Add color;
#		Append file name(auto generated) to gitignore;
# Update : 2020.10.15
#		Change terminal color lib to "lib_dramalife.sh";
# Update
#
# DEPENDS : note/lib_dramalife/lib_dramalife.sh
#

ROOT_NOTE=~/note/
#source ${ROOT_NOTE}lib_dramalife/terminal_color_bash.sh
export LIB_DRAMALIFE_PWD=${ROOT_NOTE}/lib_dramalife/
export LIB_DRAMALIFE_TERMINAL_COLOR_VERSION=5001
source ${LIB_DRAMALIFE_PWD}/lib_dramalife.sh

ARG_FILENAME=git_cherry_pick.man

# Add auto generated file to "note/.gitignore".
#sed -i "/${ARG_FILENAME}/d" ${ROOT_NOTE}.gitignore
#echo "${ARG_FILENAME}" >> ${ROOT_NOTE}.gitignore

# This way to ingore auto generated file not worked :(
#echo "${ARG_FILENAME}" >> ./.gitignore

# MOVED TO "NOTE/tools/manual_pager"
#man git cherry-pick > ${ARG_FILENAME}

# OR
#git cherry-pick --help > ${ARG_FILENAME}

# Regular use
echo	"# Regular use"
echo -e "git checkout ${CGREEN}[YOUR_DES_BRANCH]${CNONE}"
echo -e "git cherry-pick ${CGREEN}[commit]${CNONE}"
echo -e "                    ${WHITE}^----commit in other branch${CNONE} \n"
echo -e "See ${CGREEN}./${ARG_FILENAME}${CNONE} for more !"

