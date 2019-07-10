# update : 2019.05.13
# update : 2019.05.20 add gcc -v

BIN_NAME=a_demo
BIN_END=.out
SRC=$(wildcard ./*.c)

all:
	rm -rvf ./*$(BIN_END)
	gcc -o $(BIN_NAME)$(BIN_END) $(SRC) -v
#	cpp -dM /dev/null
# "make: *** [all] Error 1" 
#	./$(BIN_NAME)$(BIN_END)

clean:
	rm -rvf ./*.o
	rm -rvf ./*$(BIN_END)

