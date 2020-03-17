### 1 The principle of "sizeof" ???
(sizeof，是在编译的时候，查找符号表，判断类型，然后根据基础类型来取值的，如果是struct则是看类型声明符号表来判定，如果字符串则是通过常 量表来判断，具体可以参考编译原理的符号表管理章节)
```c
// sizeof - non-array
#define _sizeof(T)           ( (size_t)((T*)0 + 1))
// sizeof - array
#define array_sizeof(T)      ( (size_t)(&T+1)  - (size_t)(&T)  )
```
