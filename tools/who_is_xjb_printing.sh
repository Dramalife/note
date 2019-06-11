#! /bin/bash

echo "Input tty device(PATH)"
read tty
# List open files
lsof ${tty}

echo "Select one(PID) to trace"
read one
# -f : follow forks,
strace -f -p ${one}

