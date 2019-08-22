git fetch 无法获取远程分支

```diff
# vi ./.git/config
[remote "origin"]
url = https://github.com/xxx/project.git
-fetch = +refs/heads/master:refs/remotes/origin/master
+fetch = +refs/heads/*:refs/remotes/origin/*
```
