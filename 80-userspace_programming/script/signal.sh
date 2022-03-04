#! /bin/bash


do_clean(){
  echo "cleaning..."
}

# Ctrl + C
trap "echo \"recv signal! killall!\"; killall sleep; do_clean; exit 2;" SIGINT

sleep 500 &
sleep 500 &
sleep 500 &

wait;
