BIN_NAME=a_demo
BIN_END=.out
SRC=$(wildcard ./*.c)

all:
	rm -rvf ./*$(BIN_END)
	gcc -o $(BIN_NAME)$(BIN_END) $(SRC)	
	./$(BIN_NAME)$(BIN_END)

clean:
	rm -rvf ./*$(BIN_END)
