#! /bin/bash
#without binary files, without .svn paths;
grep $1 $2 -rn --binary-files=without-match --exclude-dir=\.svn --color=auto
