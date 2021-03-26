> Read the legal process from the template file;  
> Partial matching principle is used for process matching;

### TODO List
1. Provide more hooked functions;
2. Provide tools to calculate hit rate;


### 0 Prepare
```bash
# Hit rate calculation
./hit_rate.sh libdlhook.so for_gdb.out
```

### 1 Library
```bash
# Compile hooked lib
make lib_bt
```

### 2 Target Program
```bash
# Compile App
# Sample : xxxxx.c
make compile_myapp FNAME=xxxxx

# Exec App
# Sample : xxxxx.out
make run_myapp APP_PATH=./xxxxx.out
```

### 3 Server Program
```bash
# Compile & Exec Program Detect Daemon
# Sample legal process name : default.df
make pdd
./pdd default.df
```

### 4 Sample - my.c
```bash
make lib_bt
make compile_myapp FNAME=my
make pdd

# Terminal 1
./pdd.out my.df

# Terminal 2
make run_myapp APP_PATH=./my.out
```
