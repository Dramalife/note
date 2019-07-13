```bash
# note coding-svn related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## SVN
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
|5| | |
| | | |
| | | |


