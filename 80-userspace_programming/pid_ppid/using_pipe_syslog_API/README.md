### 1 Using lib_dramalife/ipc_lib (_THIS_PROG_USING_LIB_DRAMALIFE)(CH:使用库文件-lib_dramalife)
#### 1.1 Compile lib files(Currently only provide files in obj format)(CH:编译库文件。注意：目前只支持提供obj格式（*.o）)
```bash
cd ~/note/lib_dramalife/ipc_lib
make separately-complile-to-objects
```

#### 1.2 Make all(CH:编译程序文件)
```bash
cd -
make all-with-lib-objs
```

#### 1.3 Make clean(CH:清理编译时自动生成的文件)
```bash
make clean-all-with-lib-objs 
```


### 2 Do not using lib_dramalife(CH:**不使用**库文件-lib_dramalife)
#### 2.1 Make all(CH:编译程序文件)
```bash
make all-normal CFLAGS+=-U_THIS_PROG_USING_LIB_DRAMALIFE
```
#### 2.2 Make clean(CH:清理编译时自动生成的文件)
```bash
make clean-all-normal
```

