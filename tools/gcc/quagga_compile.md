### libtool
```bash
# libtool: Version mismatch error. This is libtool 2.4.2 , but the
# libtool: definition of this LT_INIT comes from libtool 2.4.6.
# libtool: You should recreate aclocal.m4 with macros from libtool 2.4.2 
# libtool: and run autoconf again
#  
# 运行命令
# autoreconf --force --install
# ./configure
# make
#  
# 如果没有生效
# make maintainer-clean 清理干净后，在运行上面的命令
# 原文：https://blog.csdn.net/github_29989383/article/details/51886234 
```
