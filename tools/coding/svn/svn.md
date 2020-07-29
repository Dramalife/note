```
# note coding-svn related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
Init : 
Update : 2020.03.16
```

## 0 SVN common commands
|no|command|explanation|
|--|--|--|
|0|svn update|更新|
||svn commit -m"备注" hello1.c hello2.c|上传|
|1|svn log hello.c -r r666 -v|-r：指定(与当前版本比较的)版本 -v:显示变化的文件列表|
|2|svn diff -r r1000:r999 hello.c|比较hello.c在r999与r1000版本之间的差异|
|3|svn status -q|--quiet,print nothing, or **only summary** information,thanks ZhangWuxiao|
| |svn status -u |--show-updates, display update information,including new files, |
|4|svn add $file| |
| |svn revert --recursive $file| |
| | | |

## 1 Init
### 1.1 checkout (co): Check out a working copy from a repository.
```bash
# Checkout trunk
svn checkout https://x.x.x.x/svn/projectx/trunk/
# Checkout branch
svn checkout https://x.x.x.x/svn/projectx/branches/branch_1/ 
```

## 2 Update
### 2.1 status (stat, st): Print the status of working copy files and directories.
```bash
# -q [--quiet]             : don't print unversioned items
# -u [--show-updates]      : display update information
# WARNING : The directory and subdirectories of the executed command !!!
svn status -q
```

### 2.2 log: Show the log messages for a set of revision(s) and/or path(s).
```bash
# usage: 1. log [PATH][@REV]
#        2. log URL[@REV] [PATH...]
# -r [--revision] ARG      : ARG (some commands also take ARG1:ARG2 range)
# 			   A revision argument can be one of:
# 				NUMBER       revision number
# 				'{' DATE '}' revision at start of the date
# 				'HEAD'       latest in repository
# 				'BASE'       base rev of item's working copy
# 				'COMMITTED'  last commit at or before BASE
# 				'PREV'       revision just before COMMITTED
# -c [--change] ARG        : the change made in revision ARG
# -q [--quiet]             : do not print the log message
# -v [--verbose]           : also print all affected paths
svn log ./hello.c -r r666 -v
```

### 2.3 diff (di): Display local changes or differences between two revisions or paths.
```bash
# -r [--revision] ARG      : ARG (some commands also take ARG1:ARG2 range)
# 			   A revision argument can be one of:
# 				NUMBER       revision number
# 				'{' DATE '}' revision at start of the date
# 				'HEAD'       latest in repository
# 				'BASE'       base rev of item's working copy
# 				'COMMITTED'  last commit at or before BASE
# 				'PREV'       revision just before COMMITTED
svn diff -r r1000:r999 hello.c
```

### 2.4 commit (ci): Send changes from your working copy to the repository.
```bash
svn update
svn commit -m"" file.c file2.c
```

## 3 Add
### 3.1 add: Put files and directories under version control, scheduling
```bash
svn add ./file.c
```

## 4 Revert
### 4.1 revert: Restore pristine working copy state (undo local changes).
```bash
# usage: revert PATH...
# This subcommand does not revert already committed changes.
#
# Revert un-committed changes
svn revert -R .
```
### 4.2 revert commit
TODO

## 4 Diff
### 4.1 svn diff 
```
-i, --ignore-case
ignore case differences in file contents

-E, --ignore-tab-expansion
ignore changes due to tab expansion

-Z, --ignore-trailing-space
ignore white space at line end

-b, --ignore-space-change
ignore changes in the amount of white space

-w, --ignore-all-space
ignore all white space
```
sample
```bash
svn diff -x -w
```
