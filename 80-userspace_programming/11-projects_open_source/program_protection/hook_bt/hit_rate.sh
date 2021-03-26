#! /bin/bash

# Usage:
# ./XXXX.sh <LIB_NAME> <APP_NAME>
echo "########HOOK_LIB"
nm ${1} | grep " T "
echo "########TARGET_APP"
nm ${2} | grep "@@GLIBC_"
