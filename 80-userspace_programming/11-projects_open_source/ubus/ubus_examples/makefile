PUB_FILES:=./demo_files/
DL_FILES:=./dl_files/



####
# Get headers from other repo
INC_LIBUBOX_GITEE=headers_libubox-2018-11-16-4382c76d
INC_UBUS_GITEE=headers_ubus-2017-02-18-34c6e818
URL_HEADERS_GITEE=https://gitee.com/Dramalife/binary_compiled_gitee.git
.prepare_git:
	../../../../lib_dramalife/exec_files/git_sparse_clone.sh $(INC_LIBUBOX_GITEE) $(URL_HEADERS_GITEE)
	../../../../lib_dramalife/exec_files/git_sparse_clone.sh $(INC_UBUS_GITEE) $(URL_HEADERS_GITEE)

INCLUDE_DIR:=-I $(INC_LIBUBOX_GITEE)/$(INC_LIBUBOX_GITEE) -I $(INC_UBUS_GITEE)/$(INC_UBUS_GITEE) -I$(PUB_FILES)
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
	make -C . .server_with_dl_generic \
		OUT_NAME=server_dl \
		DL_DEFINED_MACROS="-DUBUS_SAMPLE_ADD_DRAMALIFE_OBJECT"
server_with_dl_object_event:
	make -C . .server_with_dl_generic \
		OUT_NAME=server_dl_event \
		DL_DEFINED_MACROS="-DUBUS_SAMPLE_ADD_DRAMALIFE_OBJECT -DUBUS_SAMPLE_ADD_DRAMALIFE_SEND_EVENT"

.server_with_dl_generic: .prepare
	gcc -o $(OUT_NAME).out \
	$(PUB_FILES)/server.c \
	$(PUB_FILES)/count.c \
	$(DL_FILES)dl_ubus_add_object_int_string.c \
	$(DL_FILES)dl_ubus_add_object_array.c \
	$(INCLUDE_DIR) $(LIBS) \
	-I$(DL_FILES) \
	$(DL_DEFINED_MACROS)

.prepare:
	make -C . .prepare_git
#	ln -sf ../../../../../lib_dramalife/extern_headers/include_libubox/ $(PUB_FILES)
#	ln -sf ../../../../../lib_dramalife/extern_headers/include_ubus/ $(PUB_FILES)



clean:
	rm -rvf ./*.out
	rm -f $(PUB_FILES)/include_libubox
	rm -f $(PUB_FILES)/include_ubus
	rm -rf $(INC_LIBUBOX_GITEE)
	rm -rf $(INC_UBUS_GITEE)
