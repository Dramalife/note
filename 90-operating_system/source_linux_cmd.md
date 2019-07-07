## [Linux Source命令及脚本的执行方式解析](http://www.51testing.com/html/38/225738-206878.html)  
当我修改了/etc/profile文件，我想让它立刻生效，而不用重新登录；这时就想到用source命令，如:source /etc/profile  
对source进行了学习，并且用它与sh 执行脚本进行了对比，现在总结一下。  
  
source命令：  
source命令也称为“点命令”，也就是一个点符号（.）,是bash的内部命令。  
功能：使Shell读入指定的Shell程序文件并依次执行文件中的所有语句  
source命令通常用于重新执行刚修改的初始化文件，使之立即生效，而不必注销并重新登录。  
用法：  
source filename 或 . filename  
source命令(从 C Shell 而来)是bash shell的内置命令;点命令(.)，就是个点符号(从Bourne Shell而来)是source的另一名称。  
  
source filename 与 sh filename 及./filename执行脚本的区别在那里呢？  
1.当shell脚本具有可执行权限时，用sh filename与./filename执行脚本是没有区别得。./filename是因为当前目录没有在PATH中，所有"."是用来表示当前目录的。  
2.sh filename 重新建立一个子shell，在子shell中执行脚本里面的语句，该子shell继承父shell的环境变量，但子shell新建的、改变的变量不会被带回父shell，除非使用export。  
3.source filename：这个命令其实只是简单地读取脚本里面的语句依次在当前shell里面执行，没有建立新的子shell。那么脚本里面所有新建、改变变量的语句都会保存在当前shell里面。  
  
  
举例说明：  
1.新建一个test.sh脚本，内容为:A=1  
2.然后使其可执行chmod +x test.sh  
3.运行sh test.sh后，echo $A，显示为空，因为A=1并未传回给当前shell  
4.运行./test.sh后，也是一样的效果  
5.运行source test.sh 或者 . test.sh，然后echo $A，则会显示1，说明A=1的变量在当前shell中  
