#! /bin/bash

source ~/.note_wjy_lib_sh/*

echo "input device path,ex:\"/dev/console\""
read p_dev
cmd="lsof | grep \"${p_dev}\""

echo -e ${CLRED}"CMD"${CNONE}":[ ${cmd} ]"
# exec ${cmd}
lsof | grep ${p_dev}
