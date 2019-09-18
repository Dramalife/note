
APP_NAME=a_demo
SOURCE1=main
SOURCE2=function

PROGRAM_NAME=$(APP_NAME).out


all:
	gcc -c $(SOURCE1).c $(SOURCE2).c
	objdump -x $(SOURCE1).o > $(SOURCE1).head
	objdump -x $(SOURCE2).o > $(SOURCE2).head
	objdump -dx $(SOURCE1).o > $(SOURCE1).head.ass
	objdump -dx $(SOURCE2).o > $(SOURCE2).head.ass
	gcc *.o -o $(PROGRAM_NAME)
	objdump -dj .text $(PROGRAM_NAME) > $(PROGRAM_NAME).ass

clean:
	rm -rvf ./*.o ./*.ass ./*.head ./*.out
.PHONY : clean
