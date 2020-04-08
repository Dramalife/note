> SRC : lede-17.01/openwrt/build_dir/target-x86_64_glibc-2.24/ubus-2017-02-18-34c6e818/examples
> Init : 2020.04.07
> 	COPY FROM lede-17.01/.../ubus-2017-02-18-34c6e818/examples;
> Update : 2020.04.07
> 	Add new makefile, remove "cmake" files;
> Update : 2020.04.08
>	sort out current directory;
>	Add sample - obj-type-int;
>	Add sample - obj-type-string;
>	Add sample - obj-type-array;


### 1 Prepare
#### 1.1 Dependence
```bash
ls /bin/ubus  		
ls /bin/ubusd 		
ls /lib/libblobmsg_json.so
ls /lib/libjson-c.so      
ls /lib/libjson-c.so.2    
ls /lib/libjson-c.so.2.0.2
ls /lib/libjson_script.so 
ls /lib/libubox.so        
ls /lib/libubus.so	
```

#### 1.2 Files
- demo_files
source & headers copy from ubus;
- dl_files
source & headers added by dramalife;
- log
terminal log files;
- makefile
makefile;
- README.md
This file;

- Source file:
|File |Type |Compile MACRO|
|--|--|--|
|dl_ubus_add_object_int_string.c |Integer,String| -DUBUS_SAMPLE_ADD_DRAMALIFE_OBJECT|



### 2 Run
#### 2.1 Compile Demo
```bash
make all
```

#### 2.2 Exec
##### 2.2.1 Demo(server & client) only
```bash
# kill 1st
sudo kill -9 $(pidof server.out)
# exec
sudo ./server.out &
sudo ./client.out
```

##### 2.2.2 Demo(server) & ubusd & ubus
```bash
sudo ubusd &
sudo ./server.out &
sudo ubus list -v
#'test' @2008c898
#	"hello":{"id":"Integer","msg":"String"}
#	"watch":{"id":"Integer","counter":"Integer"}
#	"count":{"to":"Integer","string":"String"}
```

### 3 Clean All
```bash
make clean
sudo kill -9 $(pidof server.out)
sudo kill -9 $(pidof ubusd)
```
