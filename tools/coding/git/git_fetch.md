git fetch �޷���ȡԶ�̷�֧

```diff
# vi ./.git/config
[remote "origin"]
url = https://github.com/xxx/project.git
-fetch = +refs/heads/master:refs/remotes/origin/master
+fetch = +refs/heads/*:refs/remotes/origin/*
```
