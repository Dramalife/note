Source : https://www.ibm.com/developerworks/cn/linux/l-inotify/


#### NOTE : 
```
```

### 2.TODO
2020.01.18

#### 2.1 GOAL
```
make "inotify-sample" into dramalife_inotify_lib
```
#### 2.2 Problem
```
select() was used;(process, thread or non-bolck needed)
ref : note/80-userspace_programming/io
	signal driven I/O suggested(replace select() with signal io);

```
```c
/*
* Dependence
* signal()
*/
//#define DL_LIB_INOTIFY_IO_TYPE_SIGNAL
//#define DL_LIB_INOTIFY_IO_TYPE_SELECT
#if (defined DL_LIB_INOTIFY_IO_TYPE_SIGNAL) && (defined DL_LIB_INOTIFY_IO_TYPE_SELECT)
#error	Signal I/O or MULTI I/O !!
#endif

```
#### 2.3 PLAN
```
inotify-sample : replace select() with signal I/O;


```
