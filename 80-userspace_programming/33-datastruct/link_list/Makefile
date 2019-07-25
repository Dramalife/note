# update : 2019.05.13
# update : 2019.05.20 add gcc -v

BIN_NAME=a_demo
BIN_END=.out
SRC=$(wildcard ./*.c)

all:
	rm -rvf ./*$(BIN_END)
	gcc -c $(SRC)
	gcc -c ../../../lib_dramalife/gcc_related_lib/*.c
	gcc -c ../../../lib_dramalife/link_list_lib/*.c
	gcc -o $(BIN_NAME)$(BIN_END) *.o -v
#	cpp -dM /dev/null
# "make: *** [all] Error 1" 
#	./$(BIN_NAME)$(BIN_END)

clean:
	rm -rvf ./*.o
	rm -rvf ./*$(BIN_END)

