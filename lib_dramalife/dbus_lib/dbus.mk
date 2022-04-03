all: 
	make -C . server
	make -C . client
all_debug: 
	make -C . server env="$(env) $(env_mem)"
	make -C . client env="$(env) $(env_mem)"

env_mem=-fsanitize=address -fno-omit-frame-pointer 
env=-I /usr/include/dbus-1.0  \
	-I /usr/lib/aarch64-linux-gnu/dbus-1.0/include/  \
	-I /usr/lib/arm-linux-gnueabihf/dbus-1.0/include/  \
	-I /usr/lib/x86_64-linux-gnu/dbus-1.0/include/ \
	-I . \
	-lpthread \
	-D_DRAMALIFE_LIB_HAS_FUNC_MAIN_ \
	-ldbus-1

client:
	$(CC) -o client.out \
	client.c \
	./init.c \
	./method_call.c \
	./signal.c \
	$(env)

server:
	$(CC) -o server.out \
	server.c \
	./init.c \
	./method_call.c \
	./signal.c \
	$(env)

clean:
	rm -rvf ./*.out
