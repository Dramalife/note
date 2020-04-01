NOTE_PATH=$(HOME)
LIBDL_PATH:=$(NOTE_PATH)/note/lib_dramalife

CC=gcc
LIBS=-ldramalife
LIB_DIR=-I$(LIBDL_PATH)
INCLUDE_DIR=-L$(LIBDL_PATH)
LDFLAGS=-Wl,-rpath=$(LIBDL_PATH)

BIN_NAME=multicast_server.out

all:
	$(CC) -o $(BIN_NAME) multicast_server.c $(LIBS) $(LDFLAGS) $(LIB_DIR) $(INCLUDE_DIR)
clean:
	rm -vf $(BIN_NAME)
