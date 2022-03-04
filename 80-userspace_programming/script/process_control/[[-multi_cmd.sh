#! /bin/bash

[[ -e 1.sh ]] && {
  echo "1"; 
  echo "sh";
} || {
  echo "x"; 
  echo "c";
}


[[ -e 1.sh || -e 2.sh ]] && { echo "1 or 2 exist"; } || { echo "neither 1 nor 2 exist"; } 

