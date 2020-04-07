SRC : lede-17.01/openwrt/build_dir/target-x86_64_glibc-2.24/ubus-2017-02-18-34c6e818/examples
Init : 2020.04.07
	COPY FROM lede-17.01/.../ubus-2017-02-18-34c6e818/examples;
Update : 2020.04.07
	Add new makefile, remove "cmake" files;

### Tips
```
# Compile
make all

# Exec
sudo ./server.out &
sudo ./client.out

# Kill
sudo kill -9 $(pidof server.out)

# Clean
make clean
```
