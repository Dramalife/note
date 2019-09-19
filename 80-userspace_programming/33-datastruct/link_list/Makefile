# update : 2019.05.13
# update : 2019.05.20 add gcc -v
# update : 2019.09 19 include libMakefile.mk for CFLAGS;

include ../../../lib_dramalife/libMakefile.mk

# If not set, default value is "-v"
CFLAGS ?= -v

BIN_NAME=a_demo
BIN_END=.out
SRC=$(wildcard ./*.c)

all:
	rm -rvf ./*$(BIN_END)
	gcc -c $(CFLAGS) $(SRC)
	gcc -c $(CFLAGS) ../../../lib_dramalife/gcc_related_lib/*.c
	gcc -c $(CFLAGS) ../../../lib_dramalife/link_list_lib/*.c
	gcc -o $(BIN_NAME)$(BIN_END) *.o

clean:
	rm -rvf ./*.o
	rm -rvf ./*$(BIN_END)

.PHONY: clean

