#! /bin/bash
#
# note "shell bash compile" related file
# Copyright (C) 2019 Dramalife@live.com
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# bash --version
## GNU bash, version 4.4.20(1)-release (x86_64-pc-linux-gnu)
## Copyright (C) 2016 Free Software Foundation, Inc.
## License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
## 
## This is free software; you are free to change and redistribute it.
## There is NO WARRANTY, to the extent permitted by law.
# ;
#
# Init : 2021/12/26 ;
#   add source.

##
## Compile and link all source files separately!
##

# Terminal Color
source ${HOME}/note/lib_dramalife/terminal_lib/dlterm_5002.sh

SRC_TYPES="*.cc *.cpp *.c"
ADD_FLAGS="-fsanitize=address -fno-omit-frame-pointer -g"
FILE_FAIL_LIST="./.temp_compile_fail_list"

# All source
srcs=$(ls ${SRC_TYPES} 2>/dev/null)

# Threads
thread=$(cat /proc/cpuinfo| grep "processor"| wc -l)

# Compile Func
do_compile(){
  if [[ "$1" =~ .*cpp$|.*cc$ ]] ; then
    compiler=g++; suffix=".cpp"
  elif [[ "$1" = *c ]] ; then
    compiler=gcc; suffix=".c"
  else
    echo "err!"
    exit 2;
  fi
  # ${1/%${suffix}/.out}
  cmd="${compiler} -o ${1}.out $1 ${ADD_FLAGS} >/dev/null 2>&1"
  echo "    $1:::$cmd"
  if ${compiler} -o ${1}.out $1 ${ADD_FLAGS} >/dev/null 2>&1; then
    echo -e $DLTERM_WHITE"  Succ($1)!"$DLTERM_NONE
  else
    echo "$1" >> $FILE_FAIL_LIST
    echo -e $DLTERM_LRED"  Failed($1)!"$DLTERM_NONE
  fi
}


#
# Start
#

[[ -e $FILE_FAIL_LIST ]] && rm -v $FILE_FAIL_LIST;

if [ $thread -gt 0 -a $thread -lt 64 ] ; then
  echo "Thread:$thread"
else
  echo "Error:Thread:$thread, set default 1..."
  thread=1
fi

echo -e $DLTERM_WHITE"All source:"$DLTERM_NONE" ($srcs)\n"

# Do compile
index=0
for i in $srcs ; do
  index=$[$index+1]
  echo -e $DLTERM_WHITE"\nCompile-($index):"$DLTERM_NONE""
  do_compile $i &
  if [ $[$index % $thread] -eq 0 ] ; then
    echo "  wait...";
    wait;
  fi
done

[[ -e $FILE_FAIL_LIST ]] && echo "Fail list: ($(cat $FILE_FAIL_LIST))" && rm -v $FILE_FAIL_LIST;

echo "ALL DONE!"
