BIN_NAME=a_demo
BIN_END=.out
SRC=$(wildcard ./*.c)
LIB_C_DRAMALIFE=~/note/lib_dramalife/

all:
	rm -rvf ./*$(BIN_END)
	gcc -o $(BIN_NAME)$(BIN_END) $(SRC) -I $(LIB_C_DRAMALIFE)	

	#####
	./$(BIN_NAME)$(BIN_END)

clean:
	rm -rvf ./*$(BIN_END)
