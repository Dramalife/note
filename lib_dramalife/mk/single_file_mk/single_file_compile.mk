# update : 2019.05.13
# update : 2019.05.20 add gcc -v

BIN_NAME=a_demo
BIN_END=.out
SRC=$(wildcard ./*.c)
LIB_C_DRAMALIFE=~/note/lib_dramalife/

all:
	rm -rvf ./*$(BIN_END)
	gcc -o $(BIN_NAME)$(BIN_END) $(SRC) -I $(LIB_C_DRAMALIFE) -v

	# "make: *** [all] Error 1" 
	./$(BIN_NAME)$(BIN_END)

clean:
	rm -rvf ./*$(BIN_END)
