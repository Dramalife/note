### 0 NOTE
#### 0.1 List files
```
# ls
a_demo.out
config.mk
functions.c
functions.o
header.h
main.c
main.o
Makefile
README.md
source_pre.i
```
#### 0.2 Manual page - nm (part)
```manual
NM(1)
"C" 	The symbol is common.  Common symbols are uninitialized data.  When linking, multiple common symbols
	may appear with the same name.  If the symbol is defined anywhere, the common symbols are treated as
	undefined references.

"B"
"b"	The symbol is in the uninitialized data section (known as BSS).

"D"
"d" 	The symbol is in the initialized data section.
```
#### 0.3 Macros
```c
//header.h
/*
 * __INIT_THE_VAR__	: Initialize variable"gb" in this header file.(CH:)
 *	Define this macro(int gb = <x>;), GCC will report error:
 *	(CH:开启这个宏，头文件中会定义并初始化变量gb，此时GCC会报错)
 * 		GCC Error - multiple definition of `gb'
 *		(CH:重复定义变量gb)
 * __VAR_VAULE_ZERO__	: Initial vaule is 0.(CH:)
 *	Define this macro(int gb = 0;), GCC will place the var to BSS section, else DATA section.
 *	(CH:开启这个宏，头文件中会定义并初始化变量gb=0，GCC会把gb变量放到BSS段，初值不为0时放到DATA段)
 */
```

### 1. Compile
#### 1.1 DEFINE(o), INIT( ), ZERO( )
Define (but not initialize) variable in header(CFLAGS += "-U\_\_INIT_THE_VAR\_\_ -U\_\_VAR_VAULE_ZERO\_\_")
```bash
make all-normal-create-obj CFLAGS+="-U__INIT_THE_VAR__ -U__VAR_VAULE_ZERO__"
CLEANING...
rm -rvf ./*.out ./*.i ./*.o
removed './source_pre.i'
removed './functions.o'
removed './main.o'
rm -rvf /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/build
gcc -c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.c -o /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.o -U__INIT_THE_VAR__ -U__VAR_VAULE_ZERO__ 
gcc -c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.c -o /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.o -U__INIT_THE_VAR__ -U__VAR_VAULE_ZERO__ 
BUILDING...
gcc -E /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.c >> source_pre.i
FLAGS : -U__INIT_THE_VAR__ -U__VAR_VAULE_ZERO__ ;
SRCS: 
/home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.c
gcc -o a_demo.out /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.o /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.o -U__INIT_THE_VAR__ -U__VAR_VAULE_ZERO__ 
```

#### 1.2 DEFINE(o), INIT(o), ZERO( )
Define & initialize variable in header(CFLAGS +=" -D\_\_INIT_THE_VAR\_\_ -U\_\_VAR_VAULE_ZERO\_\_")
```bash
make all-normal-create-obj CFLAGS+="-D__INIT_THE_VAR__ -U__VAR_VAULE_ZERO__"
CLEANING...
rm -rvf ./*.out ./*.i ./*.o
removed './a_demo.out'
removed './source_pre.i'
removed './functions.o'
removed './main.o'
rm -rvf /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/build
gcc -c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.c -o /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.o -D__INIT_THE_VAR__ -U__VAR_VAULE_ZERO__ 
gcc -c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.c -o /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.o -D__INIT_THE_VAR__ -U__VAR_VAULE_ZERO__ 
BUILDING...
gcc -E /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.c >> source_pre.i
FLAGS : -D__INIT_THE_VAR__ -U__VAR_VAULE_ZERO__ ;
SRCS: 
/home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.c
gcc -o a_demo.out /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.o /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.o -D__INIT_THE_VAR__ -U__VAR_VAULE_ZERO__ 
/home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.o:(.data+0x0): multiple definition of `gb'
/home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.o:(.data+0x0): first defined here
collect2: error: ld returned 1 exit status
Makefile:167: recipe for target 'all-normal-create-obj' failed
make: *** [all-normal-create-obj] Error 1
```

#### 1.3 DEFINE(o), INIT(o), ZERO(o)
Define & initialize variable in header(CFLAGS +=" -D\_\_INIT_THE_VAR\_\_ -D\_\_VAR_VAULE_ZERO\_\_")
```bash
# make all-normal-create-obj CFLAGS+="-D__INIT_THE_VAR__ -D__VAR_VAULE_ZERO__"
CLEANING...
rm -rvf ./*.out ./*.i ./*.o
removed './source_pre.i'
removed './functions.o'
removed './main.o'
rm -rvf /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/build
gcc -c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.c -o /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.o -D__INIT_THE_VAR__ -D__VAR_VAULE_ZERO__ 
gcc -c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.c -o /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.o -D__INIT_THE_VAR__ -D__VAR_VAULE_ZERO__ 
BUILDING...
gcc -E /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.c >> source_pre.i
FLAGS : -D__INIT_THE_VAR__ -D__VAR_VAULE_ZERO__ ;
SRCS: 
/home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.c /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.c
gcc -o a_demo.out /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.o /home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.o -D__INIT_THE_VAR__ -D__VAR_VAULE_ZERO__ 
/home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/functions.o:(.bss+0x0): multiple definition of `gb'
/home/dramalife/note/70-gcc_gnu_compiler_collection/tips/Q_can_define_var_at_header/main.o:(.bss+0x0): first defined here
collect2: error: ld returned 1 exit status
Makefile:167: recipe for target 'all-normal-create-obj' failed
make: *** [all-normal-create-obj] Error 1
```

### 2 Symbols
#### 2.1 DEFINE(o), INIT( ), ZERO( )
List symbol - define (but not initialize) variable in header(CFLAGS +=" -U\_\_INIT_THE_VAR\_\_ -U\_\_VAR_VAULE_ZERO\_\_")
```bash
# nm main.o
000000000000000a r __func__.2252
                 U functionb
0000000000000004 C gb
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 T main
                 U printf
# nm function.o
0000000000000010 r __func__.2252
0000000000000000 T functionb
0000000000000004 C gb
                 U _GLOBAL_OFFSET_TABLE_
                 U printf
```

#### 2.2 DEFINE(o), INIT(o), ZERO( )
List symbol - define & initialize variable in header(CFLAGS +=" -D\_\_INIT_THE_VAR\_\_ -U\_\_VAR_VAULE_ZERO\_\_")
```bash
# nm main.o
000000000000000a r __func__.2252
                 U functionb
0000000000000000 D gb
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 T main
                 U printf
# nm function.o
0000000000000010 r __func__.2252
0000000000000000 T functionb
0000000000000000 D gb
                 U _GLOBAL_OFFSET_TABLE_
                 U printf
```

#### 2.3 DEFINE(o), INIT(o), ZERO(o)
List symbol - define & initialize variable in header(CFLAGS +=" -D\_\_INIT_THE_VAR\_\_ -D\_\_VAR_VAULE_ZERO\_\_")
```bash
# nm main.o
000000000000000a r __func__.2252
                 U functionb
0000000000000000 B gb
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 T main
                 U printf
# nm function.o
0000000000000010 r __func__.2252
0000000000000000 T functionb
0000000000000000 B gb
                 U _GLOBAL_OFFSET_TABLE_
                 U printf
```

---------------------------

### Summary
Define and/or init variable in header files referenced by multiple source files.
(CH:在 被多个源文件引用的 头文件 中 定义和初始化变量。)

|INIT |ZERO |Compile |Section of var|
|--|--|--|--|
|- |- |PASS	|COMMON	|
|v |- |ERR	|DATA	|
|v |v |ERR	|BSS	|
