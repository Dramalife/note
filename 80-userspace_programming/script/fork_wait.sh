#! /bin/bash


num_times=8
num_threads=2
array_childs=""
array_fail=""
array_cmds=("sleep 2" "sleep 3" "sleep 1" "XXXX" "sleep 2")
cnt_fail=0
readonly ARYKEY=";AY;"

wait_childs(){
  local tmp_en_next=0;

  for i in ${array_childs[@]} ; do
    if [ "${i}" = "${ARYKEY}" ] ; then tmp_en_next=1; continue; fi
    if [ 1 -eq $tmp_en_next ] ; then
      tmp_en_next=0;
      local tmp_pid=${i}
      echo "    wait $tmp_pid..."
      if ! wait $tmp_pid ; then
        # TODO: Add cmd; 
	#       Replace array with map or json?
        array_fail=(${array_fail[@]} "$tmp_pid")
        cnt_fail=$[$cnt_fail + 1]
        echo "      wait $tmp_pid failed!"
      else
        echo "      wait $tmp_pid succ!"
      fi
    fi
  done

  local tmp_cnt=0
  unset array_childs;
}
print_result(){
  echo "Fail cnt: $cnt_fail"
  echo "Fail PIDs: ${array_fail[@]}"
}

test_func(){
  local tmp_cnt=0
  local tmp_cnt_cmds=${#array_cmds[@]}

  while [ $tmp_cnt -lt $tmp_cnt_cmds ]
  do
    local tmp_cmd=${array_cmds[${tmp_cnt}]}
    $tmp_cmd &
    local tmp_pid=$!
    local tmp_item=("$ARYKEY" "$tmp_pid" "$tmp_cmd")
    echo "Exec: ${tmp_item[@]}"
    array_childs=("${array_childs[@]}" "${tmp_item[@]}")
    tmp_cnt=$[$tmp_cnt + 1]
    if [ 0 -eq `expr $tmp_cnt % $num_threads` ] ; then 
      wait_childs;
    fi
  done
  wait_childs;
  print_result;
}

test_func;
