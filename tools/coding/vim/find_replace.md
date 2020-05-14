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
|ɾ��������		|Del odd lines	 			 |:%normal jkdd	 |  |
|ɾ��ż����		|Del even lines	 			 |:%normal jdd	 |  |
|ɾ������abc���� 	|Del lines that included "abc" 	 	 |:% g/abc/d	 |  |
|ɾ��������abc���� 	|Del lines that not included "abc"	 |:% g!/abc/d	 |  |
|ɾ����β�ո� 		|Del spaces at the end of the line	 |:%s/\s\+$//g 	 |"%s":all text;  "\s":space;  "\+":one or more;  "$":end of line; |
|��β��ӿո� 		|Add spaces at the end of the line	 |:%s/$/  /g |  |
| 			|Del spaces at the beginning of the line 	 |:%s/^\s\*//g 	 |"^","\s","\*(just star)"  |
|ɾ������ |Del blank lines |:g/^$/d |  |
| | | |  |
