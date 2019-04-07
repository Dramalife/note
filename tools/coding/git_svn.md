## GIT
工作区\(Unstaged Changes\)
暂存区\(Staged Changes\)
本地仓库
远程仓库

**update**
git fetch
git pull
**modified**
$edit	  	(use "git add <file>..." to update what will be committed)
		(use "git checkout -- <file>..." to discard **changes** in working directory)
$staged	  	git commit
		(use "git reset HEAD <file>..." to unstage)
$commit		git push


no|command|explanation
--|--|--
0|git status -uno|简要形式显示状态
add|git **add** 文件/文件夹名称|添加文件（夹）到 **暂存区**
add|git rm -r --cached '文件夹名'|删除文件夹
1|git **commit** hello.c -m"说明"|提交到 **本地仓库** \/保存一个快照
2|git **push** origin master:wangjianyu_master|提交到 **远程仓库**
3|git checkout -- hello.c|恢复到最后一次改动，未add到暂存的状态[restore]
4|git reset HEAD -- hello.c|取消文件暂存[unstage]
5|‘/’|github路径中输入'/'新建文件夹 or 移动文件
|6|tip|当conflict，如果文件内包含“>>>>>>>>>>”，导致fix conflict失败|

### conflict-GIT 删掉冲突注释，重新提交
- tip:在push不了时，pull之前。在本地创建一个新的分支并commit到local，以保证本地有commit记录，万一出什么问题，可以找回代码，以免代码丢失。
- <<<<<<< HEAD 到 ======= 中间的内容是local提交的。
======= 到 >>>>>>> commit-id 是远程仓库中的内容
1) 解决冲突（删掉注释）；
2) git status:查看当前状态，处于MERGING状态
3) git add file.c; git commit; git push;

### git 撤回
#### git checkout -- readme.txt
让这个 **工作区** 的文件回到最近一次git commit或git add时（ **暂存区** ）的状态。\
命令中的--很重要，没有--，就变成了“切换到另一个分支”的命令

### git 版本指针：git reset
||||
|--|--|--|
|0|git log|可选参数：\-\-pretty=oneline|
|1|$\(commit id\)|SHA1计算出来的HEX数字|
|2|HEAD|当前版本，HEAD^上一个版本;HEAD~100：往上100个版本|
|3|git **reset** --hard HEAD^/$\(commit id\)|指针：回退一个版本/回退后回到当前|
|4|git reflog|记录每一次命令；比如回退后没有最新的版本号，|

## SVN
|no|command|explanation|
|--|--|--|
|0|svn update|更新|
||svn commit -m"备注" hello1.c hello2.c|上传|
|1|svn log hello.c -r r666 -v|-r：指定(与当前版本比较的)版本 -v:显示变化的文件列表|
|2|svn diff -r r1000:r999 hello.c|比较hello.c在r999与r1000版本之间的差异|
|3|svn status -q|--quiet|

### svn local backup-备份本地临时版本-\[*, cat, pipe, tar,\]
```bash
svn status -q >> status. svn
cat status. svn| xargs tar czvf  backup.tar.gz
#其中status.svn是要打包的文件列表
#edit status.svn first
```

