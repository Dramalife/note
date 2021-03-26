# Backtrace ok
all_bt: clean lib_bt app_bt pdd
lib_bt:
	gcc -fPIC -shared -o libdlhook.so dlhook.c -D_DLBT_DEBUG_ENABLED_=1 -ldl  -rdynamic -funwind-tables -ffunction-sections

# Compile sample app
app_bt:
	gcc -o for_gdb.out for_gdb.c -rdynamic -funwind-tables -ffunction-sections -Wall

# Exec sample app
run:
	-make -C . run_myapp APP_PATH=./for_gdb.out

# Exec your app named "$(APP_PATH)"
run_myapp:
	LD_PRELOAD=./libdlhook.so $(APP_PATH)
# Compile your app
compile_myapp:
	gcc -o $(FNAME).out $(FNAME).c -rdynamic -funwind-tables -ffunction-sections

# Compile Program Detect Daemon
pdd:
	gcc -o pdd.out pdd.c -g -rdynamic -funwind-tables -ffunction-sections -Wall



#all: clean lib app
#lib:
#	gcc -fPIC -shared -o libdlhook.so dlhook.c -D_DLBT_DEBUG_ENABLED_=1
#app:
#	gcc -o for_gdb.out for_gdb.c
#zpp:
#	gcc -o for_gdb.out for_gdb.c -ldlhook -L. -Wl,-rpath=.


clean:
	rm -rvf ./*.so ./*.out
