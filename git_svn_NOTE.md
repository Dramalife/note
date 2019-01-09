### GIT
no|command|explanation
--|--|--
0|git status -uno|简要形式显示状态
add|git add 文件/文件夹名称|添加文件（夹）
add|git rm -r --cached '文件夹名'|删除文件夹
1|git **commit** hello.c -m"说明"|提交到本地仓库
2|git **push** origin master:wangjianyu_master|提交到远程仓库
3|git checkout -- hello.c|恢复到最后一次改动，未add到暂存的状态[restore]
4|git reset HEAD -- hello.c|取消文件暂存[unstage]
5|‘/’|github新建文件夹 or 移动文件


### SVN
|no|command|explanation|
|--|--|--|
|0|svn update|更新|
||svn commit -m"备注" hello1.c hello2.c|上传|
|1|svn log hello.c -r r666 -v|-r：指定(与当前版本比较的)版本 -v:显示变化的文件列表|
|2|svn diff -r r1000:r999 hello.c|比较hello.c在r999与r1000版本之间的差异|
