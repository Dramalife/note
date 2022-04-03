#! /bin/bash
#
# note "format" related file
# Copyright (C) 2019 Dramalife <dramalife@live.com>
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# $ gcc --version
# gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
# Copyright (C) 2017 Free Software Foundation, Inc.
# This is free software; see the source for copying conditions.  There is NO
# warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# ;
# 
# $ uname -a
# Linux iZ2zeeq1jai7e6qn7xqrnuZ 4.15.0-96-generic #97-Ubuntu SMP Wed Apr 1 03:25:46 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
# ;
# 
# Init : Sun Dec 26 22:25:27 CST 2021
#  * ;
# Update : Sun Dec 26 22:25:27 CST 2021
#  
# Update
#


TIME=$(date +%Y%m%d_%H%M_%S)
TEMP="/tmp/format_libdramalife_$TIME"
ALL_SOURCE=""

error(){
  echo "Error: $@"
  exit 2
}

do_format(){
  targ_file=$1

  # backup
  echo "  Backup ($targ_file) to $TEMP"
  cp -f $targ_file $TEMP

  # do format
  clang-format -style="Chromium" -i $targ_file
}

# Start
if ! mkdir -p $TEMP ; then
  error "Mkdir($TEMP)!"
fi

# INSTALL
if ! clang-format --version ; then
  sudo apt install clang-format -y
fi

# DO FORMAT
echo "Current ver backup to ($TEMP)"

ALL_SOURCE="${ALL_SOURCE} $(find -P . -name "*.h")"
ALL_SOURCE="${ALL_SOURCE} $(find -P . -name "*.c")"
ALL_SOURCE="${ALL_SOURCE} $(find -P . -name "*.cc")"
ALL_SOURCE="${ALL_SOURCE} $(find -P . -name "*.cpp")"
#echo "$ALL_SOURCE"

for i in $ALL_SOURCE ; do
  do_format $i
done
