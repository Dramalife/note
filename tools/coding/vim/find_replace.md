> \# note "vim" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.08.21;  
\# Update : 2019.08.28   
\# Update   
\#  
  

|ch|en |cmd |Explanation |
|--|--|--|--|
|删除奇数行		|Del odd lines	 			 |:%normal jkdd	 |  |
|删除偶数行		|Del even lines	 			 |:%normal jdd	 |  |
|删除包含abc的行 	|Del lines that included "abc" 	 	 |:% g/abc/d	 |  |
|删除不包含abc的行 	|Del lines that not included "abc"	 |:% g!/abc/d	 |  |
|删除行尾空格 		|Del spaces at the end of the line	 |:%s/\s\+$//g 	 |"%s":all text;  "\s":space;  "\+":one or more;  "$":end of line; |
|行尾添加空格 		|Add spaces at the end of the line	 |:%s/$/  /g |  |
| 			|Del spaces at the beginning of the line 	 |:%s/^\s\*//g 	 |"^","\s","\*(just star)"  |
|删除空行 |Del blank lines |:g/^$/d |  |
| | | |  |
