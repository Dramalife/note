CC=gcc

PROG_NAME = zpi.out

all:
	-git clone https://gitee.com/Dramalife/librs232-luajit.git --depth=1
	$(CC) -c librs232-luajit/librs232.c
	$(CC) -c ./*.c \
		    -I ./librs232\-luajit/ \
		    -lpthread
	$(CC) -o $(PROG_NAME) ./*.o \
	-lpthread

clean:
	rm -rvf ./*.o ./*.out
	
