> note "**LIB_SHARED**" related file
> Copyright (C) 2019 Dramalife@live.com
>
> This file is part of [**note**](https://github.com/Dramalife/note.git)
>
> note is distributed in the hope that it will be useful, but 
> WITHOUT ANY WARRANTY; without even the implied warranty of 
> MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
>
> **Init** : 2019.08.23; 
> **Update** : 2019.11.08, Add "2.2 - Find lib while executing"; 
> **Update** : 2019.11.10, Rename : "mv steps_use_personal_lib.md create_lib_runtime_compile.md";   **Update**  
>



# 0. Options of GCC & LD

## 0.1 options of gcc & ld for executable
- -I dir:		Add the directory dir to the list of directories to be searched for header files.(man 1 gcc)
- -Ldir:		Add directory dir to the list of directories to be searched for -l.(man 1 gcc)
- -l library:	Search the library named library when linking.(man 1 gcc)
- -Wl,option:	Pass option as an option to the linker.(man 1 gcc)
- -rpath=dir:	Add a directory to the runtime library search path.(man 1 ld)

## 0.2 options of gcc & ld for library
- -fPIC:	 
	 If supported for the target machine, emit position-independent code, suitable for dynamic linking and
	 avoiding any limit on the size of the global offset table.  This option makes a difference on the m68k,
	 PowerPC and SPARC.

	 Position-independent code requires special support, and therefore works only on certain machines.

	 When this flag is set, the macros "__pic__" and "__PIC__" are defined to 2.(man 1 gcc)
- -shared:
	 Produce a shared object which can then be linked with other objects to form an executable.  Not all
	 systems support this option.  For predictable results, you must also specify the same set of options used
	 for compilation (-fpic, -fPIC, or model suboptions) when you specify this linker option.[1]


## 0.3 Difference between "ld" and "ld.so(ld-linux.so\*)"

|	|stage		|
|--|--|
|ld	|comilation	|
|ld.so	|runtime	|



# 1. Using lib when compiling(linking)
1. vi Makefile;
2. Replace "YOUR_LIB" and "../YOUR_LIB_PATH" with your library and path :
```diff
-gcc -o $(BIN_NAME)$(BIN_END) $(SRC)
+gcc -o $(BIN_NAME)$(BIN_END) $(SRC) -lYOUR_LIB -L../YOUR_LIB_PATH
```

# 2. FINDING

## 2.1 Finding lib - compilation
- METHOD 4.1 : [ COMPILING ] [ RECOMMENDED ] Dramalife RECOMMENDED for debugging ;)
Add "**-L**$(PATH_YOUR_LIB_IN)" to your "gcc options" that after "-l" option .

- METHOD 4.2 : [ COMPILING ] 
```bash
export LIBRARY_PATH=.:../lib_shared
```

## 2.2 Finding lib - runtime
- METHOD 1 : [ EXECUTING ]  Add a directory to the runtime library search path(default: /lib, /usr/lib ...).
export **LD_LIBRARY_PATH**=.:../lib_shared

- METHOD 5 : [ EXECUTING ] [ RECOMMENDED ] Pass runtime library search path to the linker.(will write "search path" to ELF)
[gcc] -Wl,option : Pass option as an option to the linker.
	[ld]  -rpath	 : Add a directory to the runtime library search path.
Add "**-Wl,-rpath**=$(PATH_YOUR_LIB_IN)" to gcc options;

- METHOD 2.1 : [EXECUTING] ldconfig - configure dynamic linker run-time bindings
**ldconfig** ../lib_shared

- METHOD 2.2 : [EXECUTING] ldconfig_config
Add "YOUR_LIB_PATH" to **/etc/ld.so.conf** AND run ldconfig;

- METHOD 3 : [ EXECUTING ] [ COMPILING ]
Copy YOUR_LIB.so to "**/lib**","/usr/lib" ...


# 3. HEADERS

```bash
./app.c: In function ‘main’:
./app.c:105:18: error: ‘signal_handler’ undeclared (first use in this function)
signal(SIGSEGV, signal_handler); 
^
./app.c:105:18: note: each undeclared identifier is reported only once for each function it appears in
make: *** [all] Error 1
```
- First Checkout "LIB_HAVE_HEADER_FILE" defined at "app.c";

- METHOD 1
Add "**extern int signal_handler(...);**" to source code(*.c) manually :|

- METHOD 2
Create a **header** file(*.h) related to YOUR_LIB.so, which regular library files are like ;)



# 4. ERRORs - compile
> [CH]**背景**：			新添加动态链接库，并编译依赖这个库的应用程序。
> [EN]**Background**: Add shared library and compile applications depending on it.

## 4.1 "undefined reference to"
- [CH]未定义的引用：找不到函数**定义**(实现)（见 2.1 FINDING - compilation）
- [EN]**undefined** reference to; (see 2.1 FINDING - compilation)
```
Makefile : {gcc -o $(BIN_NAME)$(BIN_END) $(SRC) -v}
```
```bash
app.c:(.text+0x99): undefined reference to `signal_handler'
collect2: error: ld returned 1 exit status
make: *** [all] Error 1
```

## 4.2 "error: ‘signal_handler’ undeclared"
- [CH]未**声明**：		缺少函数声明（向c源文件中添加“ extern int functions(argc，...)”，或include包含函数声明的头文件。)
- [EN]**undeclared**:		Missing declaration of function（Adding "extern int functions(argc, ...)" to c source file, or including header file that including declaration of the function.
```bash
./app.c:113:18: error: ‘signal_handler’ undeclared (first use in this function)
```

## 4.3 "cannot find -lbacktrace_funcs"

- [CH]“ ld”（链接）进程无法在“ / lib”，“ / usr / lib”或其他默认路径下找到该lib，你应该使用gcc的“ -L”选项来告诉它该lib的路径。 （或将此lib的路径添加到其默认搜索路径）。(见 2.1 FINDING - compilation)

- [EN]The "ld"(linker) process can neither find the lib at "/lib" , "/usr/lib" nor at other default path, your should use "-L" option of gcc to tell it the path of the lib. (or add path of the lib to its default searching path). (see 2.1 FINDING - compilation)

```diff
- gcc -o $(BIN_NAME)$(BIN_END) $(SRC) -lbacktrace_funcs -v
+ gcc -o $(BIN_NAME)$(BIN_END) $(SRC) -lbacktrace_funcs -L../lib_gg -v
```
```bash
/usr/bin/ld.bfd.real: cannot find -lbacktrace_funcs
collect2: error: ld returned 1 exit status
make: *** [all] Error 1
```


# 5. ERRORs - runtime(executing)

## 5.1 No such file or directory(executing)
- Add gcc options below:
-Wl,-rpath=../PATH/OF/YOUR/LIB
```bash
$ ldd a_demo.out
	linux-vdso.so.1 (0x00007ffda3295000)
	libbacktrace_funcs.so => not found
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007ff1ec7fc000)
	/lib64/ld-linux-x86-64.so.2 (0x00007ff1ecdef000)
$ ./a_demo.out
./a_demo.out: error while loading shared libraries: libbacktrace_funcs.so: cannot open shared object file: No such file or directory
```
