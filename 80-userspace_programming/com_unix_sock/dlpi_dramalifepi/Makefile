#
#  note project dlpi related file
#  Copyright (C) 2019 Dramalife@live.com
#
#  This file is part of [note](https://github.com/Dramalife/note.git)
#
#  note is distributed in the hope that it will be useful, but
#  WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
#   Init	2019.08.11 COPY FROM /note/80-userspace_programming/com_unix_sock.
<<<<<<< HEAD
#   Update 2019.08.14 add the "-f" option of the "rm" command.
# Update 2019.08.16 add "make backtrace" option for debug.
=======
<<<<<<< HEAD
#   Update 
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3

CLIENT=client
SERVER=server
APP3=client_backtrace

BIN_END=.out
BIN_O=.o
PRE_COMP=.i
DIS_ASSB=.ass

SRC=$(wildcard ./*.c)

all: $(CLIENT) $(SERVER)
client: $(CLIENT)$(BIN_O)
server: $(SERVER)$(BIN_O)

backtrace:
	gcc -c ../../../lib_dramalife/backtrace_lib/backtrace_funcs.c -o ./backtrace.o
	gcc -c client.c -Wall
	gcc -E $(CLIENT).c -o $(CLIENT)$(PRE_COMP)
	gcc server.c -o $(SERVER)$(BIN_END) -Wall
	gcc client.o backtrace.o -o $(APP3)$(BIN_END)
	objdump -d $(APP3)$(BIN_END) > $(APP3)$(DIS_ASSB)
.PHONY : backtrace

clean:
<<<<<<< HEAD
	rm -rvf ./*$(BIN_O) ./*$(BIN_END) ./*$(DIS_ASSB) ./*$(PRE_COMP)
	rm -vf server
	rm -vf client
=======
	rm *.o
	rm server
	rm client
=======
#   Update 2019.08.14 add the "-f" option of the "rm" command.
# Update 2019.08.16 add "make backtrace" option for debug.
# Update 2019.08.17 add dlpi_common.o, TODO : Enhance the scalability of this file..
# Update

CLIENT=client
SERVER=server
APP3=client_backtrace

BIN_END=.out
BIN_O=.o
PRE_COMP=.i
DIS_ASSB=.ass

SRC=$(wildcard ./*.c)

all: $(CLIENT) $(SERVER)
$(CLIENT): $(CLIENT)$(BIN_O) dlpi_common.c
$(SERVER): $(SERVER)$(BIN_O) dlpi_common.c

backtrace:
	gcc -c ../../../lib_dramalife/backtrace_lib/backtrace_funcs.c -o ./backtrace.o
	gcc -c $(SRC) -Wall
	gcc server.o dlpi_common.o -o $(SERVER)$(BIN_END)
	gcc client.o backtrace.o dlpi_common.o -o $(APP3)$(BIN_END)
	gcc -E $(CLIENT).c -o $(CLIENT)$(PRE_COMP)
	objdump -d $(APP3)$(BIN_END) > $(APP3)$(DIS_ASSB)
.PHONY : backtrace

clean:
	rm -rvf ./*$(BIN_O) ./*$(BIN_END) ./*$(DIS_ASSB) ./*$(PRE_COMP)
	rm -vf server
	rm -vf client
>>>>>>> fc351b9041d413fdf3135455c7690e71b7338277
>>>>>>> 1c135359f8bc690da25f7e65a51337ea35e56fd3
.PHONY: clean

