#! /bin/bash
#
# note trace related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
# Dramalife@live.com
# 2019.05.24

source ~/.note_wjy_lib_sh/*

echo "input device path,ex:\"/dev/console\""
read p_dev
cmd="lsof | grep \"${p_dev}\""

echo -e ${CLRED}"CMD"${CNONE}":[ ${cmd} ]"
# exec ${cmd}
lsof | grep ${p_dev}

