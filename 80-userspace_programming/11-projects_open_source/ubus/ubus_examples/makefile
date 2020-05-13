PUB_FILES:=./demo_files/
DL_FILES:=./dl_files/

INCLUDE_DIR:=-I $(PUB_FILES)/include_libubox/ -I $(PUB_FILES)/include_ubus/ -I$(PUB_FILES)
LIBS:=-lubus -lubox


all:client server

client: .prepare
	gcc -o client.out \
	$(PUB_FILES)/client.c \
	$(PUB_FILES)/count.c \
	$(INCLUDE_DIR) $(LIBS)
server: .prepare
	gcc -o server.out \
	$(PUB_FILES)/server.c \
	$(PUB_FILES)/count.c \
	$(INCLUDE_DIR) $(LIBS)



server_with_dl_object:
	make -C . .server_with_dl_xxx \
		OUT_NAME=server_dl \
		DL_DEFINED_MACROS="-DUBUS_SAMPLE_ADD_DRAMALIFE_OBJECT"
server_with_dl_object_event:
	make -C . .server_with_dl_xxx \
		OUT_NAME=server_dl_event \
		DL_DEFINED_MACROS="-DUBUS_SAMPLE_ADD_DRAMALIFE_OBJECT -DUBUS_SAMPLE_ADD_DRAMALIFE_SEND_EVENT"

.server_with_dl_xxx: .prepare
	gcc -o $(OUT_NAME).out \
	$(PUB_FILES)/server.c \
	$(PUB_FILES)/count.c \
	$(DL_FILES)dl_ubus_add_object_int_string.c \
	$(DL_FILES)dl_ubus_add_object_array.c \
	$(INCLUDE_DIR) $(LIBS) \
	-I$(DL_FILES) \
	$(DL_DEFINED_MACROS)

.prepare:
	ln -sf ../../../../../lib_dramalife/extern_headers/include_libubox/ $(PUB_FILES)
	ln -sf ../../../../../lib_dramalife/extern_headers/include_ubus/ $(PUB_FILES)


clean:
	rm -rvf ./*.out
	rm -f $(PUB_FILES)/include_libubox
	rm -f $(PUB_FILES)/include_ubus
