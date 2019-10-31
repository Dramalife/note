> \# note "git" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Ref : man(1)git;  
\#  
\# Init : 2019.10.31;  
\# Update   
\#  
  


```
-b, --ignore-space-change
	Ignore changes in amount of whitespace. This ignores whitespace at line end, and considers all other sequences of one or more whitespace characters to be equivalent.
```

##### Sample "-b"

`dramalife@server:~/note/80-userspace_programming/33-datastruct/union $ git diff union.c`
```diff
diff --git a/80-userspace_programming/33-datastruct/union/union.c b/80-userspace_programming/33-datastruct/union/union.c
index 8534cf2..22ff64c 100644
--- a/80-userspace_programming/33-datastruct/union/union.c
+++ b/80-userspace_programming/33-datastruct/union/union.c
@@ -136,13 +136,13 @@ int main(void)
 int main_union(void)
 #endif
 {
-       printf("[%s,%d]START! \n",__func__,__LINE__);
-
-       size_union();
-       value_set_overwrite();
-       value_set();
-       endian_test();
-       return 0;
+    printf("[%s,%d]START! \n",__func__,__LINE__);
+    
+    size_union();
+    value_set_overwrite();
+    value_set();
+    endian_test();
+    return 0;
 }
     
 #if (DL_NOTE_UNION2_PART_BUILD == 3)
```

```
dramalife@server:~/note/80-userspace_programming/33-datastruct/union $ git diff union.c -b
fatal: option '-b' must come before non-option arguments
dramalife@server:~/note/80-userspace_programming/33-datastruct/union $ git diff -b union.c
dramalife@server:~/note/80-userspace_programming/33-datastruct/union $ 
```
