#! /bin/bash
#without binary files, without .svn paths;
grep $1 $2 -rn --binary-files=without-match --exclude-dir=\.svn --color=auto



#	使用
#	------
#	|no	|func		|sh		|
#	|-------|---------------|---------------|
#	|0	|grep定向到文件	|```grep "content" . -rin > ../1.txt```|
#	|1	|搜索子目录	|grep -r|
#	|2	|忽略子目录	|grep -d skip|
#	|3	|ignore CASE	|grep -i|
#	|4	|只匹配整个单词,而非字符串的一部分|grep -w "xxx" files|
#	|5	|排除		|  grep -v "x1\ \|x2\ \|x3"|
#	|6	|排除文件 	| grep "cell_config" . -rn \| grep -v "svn\ \|Binary" >> ../1.txt|
#	| 	| exclude	| grep "123"./apps --exclude-dir={.svn,.git} -rn|
#	| 	| include	| grep "123"./apps --include-dir={src,include} -rn|
#	|7	|列出包含搜索内容的文件|grep -l|	|
#	| 	| 		|		|
#	
#	常用方式
#	------
#	# grep "printf" ./src ./include -rn | grep -v "svn\|Binary\|tags"
#	//在src和include中查找printf，且在结果中排除掉包含svn、Binary和tags的行
#	# grep "printf" ./src ./include -rnl | grep -v "svn"
#	//在src和include中查找包含printf的文件，且排除掉名称包含svn的文件夹
#
