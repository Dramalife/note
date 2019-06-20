```bash
# note coding-vim related file
# Copyright (C) 2019 Dramalife
# 
# This file is part of [note](https://github.com/Dramalife/note.git)
# 
# note is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

### Hot Keys
|No|Symbol|Item|Details|Complement|
|--|--|--|--|--|
|0|1008|ctrl + n|auto complete||
|1|0060|ctrl + ]|jump to definition,depends on "ctags"||
|2|0061|ctrl + o|||
|3|0062|ctrl + i|||
| |0063|ctrl + f/b|向下/上滚动一屏||
| |0064|ctrl + e/y|... ...一行||
| |0065|ctrl + d/u|... ...半屏||
| |0071|w|ahead a word||
| |0072|b|backward a word||
|4|2000|:1,$s/old/new/g | replace "old" with "new",,:%s/old/new/g全局范围(%)||
| |0000|:%s/old/new/g|replace||
| |0000|:%s/keyword/&/g|计数：在全文，"keyword"的数量，"&"表示前边的字符串||
| |0000|:123,456 y/d|复制/删除123到456行||
|5|2001|ctrl + v , I , (input) , esc*2|block insert||
|6|0080|*|find current forward||
| |0081|#|||
|7|0083|/|find word||
| |0084|?|find||
| |0085|:match diffadd /WORD/|set color of WORD| |
| |0000|/word\c|\c大小写不敏感，\C大小写敏感||
| |0000|set ignorecase |设置默认进行大小写不敏感查找;||
| |0000|set smartcase  |如果有一个大写字母，则切换到大小写敏感查找| |
| |0085|/\<WORD\>|full match find "WORD"||
|8|0800|set cursorline/nocursorline|在当前行添加下划线||
| | | | | |
|9|9001|:split file.c|split edit window| |
| |9001|:vsplit file.c|split edit window| |
| |9001|ctrl + w + w | exchange form edit windows| "split"|
| | | | | |
| | |:%s/^[0-9]\{1,\}//g 	|删除行首数字,注意"\^"一定要有 | |
| | |:%s/^\s*//g 		|删除行首空格 | |
| | |:%s/^\n//g 		|删除所有空行，^：行首，\n：行尾换行 | |
| | |:% d 			|删除所有 | |
| | | | | |
| | | | | |
| | | | | |
| | | | | |


### Problems
|No|Description|Reason|Solve|
|--|--|--|--|
|0|“^M”|windows 与 linux换行符不同| :1,$s/^M//g , “^M”输入：ctrl+v,ctrl+M|
