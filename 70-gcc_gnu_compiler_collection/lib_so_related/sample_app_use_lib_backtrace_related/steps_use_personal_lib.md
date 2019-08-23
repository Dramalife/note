> \# note "**LIB_SHARED**" related file
\# Copyright (C) 2019 Dramalife@live.com
\# 
\# This file is part of [note](https://github.com/Dramalife/note.git)
\# 
\# note is distributed in the hope that it will be useful, but
\# WITHOUT ANY WARRANTY; without even the implied warranty of
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
\#
\# Init : 2019.08.23;
\# Update 
\#

#### 1. USE LIB

```bash
# /tmp/ccJO7arr.o: In function `main':
# app.c:(.text+0x99): undefined reference to `signal_handler'
# collect2: error: ld returned 1 exit status
# make: *** [all] Error 1
```

```diff
# vi Makefile
-gcc -o $(BIN_NAME)$(BIN_END) $(SRC)
+gcc -o $(BIN_NAME)$(BIN_END) $(SRC) -lbacktrace_funcs -L../lib_shared
# -L : Tell gcc the location of YOUR_LIB, if needed(not in default search path, like /lib);
```

#### 2. FIND LIB

```bash
# Error occurs:
#./a_demo.out: error while loading shared libraries: libbacktrace_funcs.so: cannot open shared object file: No such file or directory

# METHOD 1 : Run:   *RECOMMENDED*
export LD_LIBRARY_PATH=.:../lib_shared

# METHOD 2.1 : ldconfig 
ldconfig ../lib_shared
# METHOD 2.2 : ldconfig_config
# Add "YOUR_LIB_PATH" to /etc/ld.so.conf AND run ldconfig;

# METHOD 3 : 
# Copy YOUR_LIB.so to "/lib","/usr/lib" ...

```

#### 3. HEADERS

```bash
#    ./app.c: In function ‘main’:
#    ./app.c:105:18: error: ‘signal_handler’ undeclared (first use in this function)
#    signal(SIGSEGV, signal_handler); 
#    ^
#    ./app.c:105:18: note: each undeclared identifier is reported only once for each function it appears in
#    make: *** [all] Error 1

# First checkout "LIB_HAVE_HEADER_FILE" defined at "app.c";

# METHOD 1
# Add "extern TYPE signal_handler(...);" to YOUR_APP.c manually :|

# METHOD 2
# Create a header file related to YOUR_LIB.so, which regular library files are like ;)

```

