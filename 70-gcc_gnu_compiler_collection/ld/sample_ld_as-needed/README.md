### 1. Targets of the makefile(make的目标)
```bash
$ make
all                           app_compile_err_lrt           app_ok                        dynlib_ok
app_compile_err_asneeded      app_compile_err_order_dynlib  clean                         test_old_app__new_dynlib
```

### 2. Simple explantion of targets(对make的目标的说明)
#### all
Compile app and lib normally(正常编译app和lib)
#### app_compile_err_lrt
Missing links to necessary libraries at compile time(编译时缺少对必要库的链接)  
The "-lrt" option was not specified when compiling the app.  
NOTE:The dynlib used at this time did not specify the "-lrt" option at compile time
#### app_ok
Compile the app normally(正常编译app)                        
#### dynlib_ok
Compile the lib normally(正常编译lib)
#### app_compile_err_asneeded
Wrong link option(错误的链接参数)      
#### app_compile_err_order_dynlib  
Wrong dynamic library order错误的动态库顺序)
#### clean   
Clear all files generated automatically at compile time(清除所有编译时自动生成的文件)                      
#### test_old_app__new_dynlib
The newer app and lib both use the variable var_a defined in the app, and the older app does not define var_a(比较新的app和lib中都使用了在app中定义的变量var_a，比较旧的app中没有定义var_a)

