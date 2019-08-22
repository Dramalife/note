[source url](https://www.cnblogs.com/gifisan/p/5919279.html)

github merge指定commit  

比如说有两个branch，分别是master和m1，我们在m1上修改的bug怎么merge到master上呢，  

怎么merge我不知道，但是有另外一个命令可以做到，比如m1做commit，sha-1为abc，  

在master目录下执行 git cherry-pick abc ，即可把abc这个commit “merge” 到master  
