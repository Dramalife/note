default:all

all:lib app 

lib:
	gcc -c add.c -o add.o
	gcc -c sub.c -o sub.o
	ar -crv libmath.a add.o sub.o
app:
	gcc caculate.c -o caculate.out -L. -lmath
app_run:
	./caculate.out

clean:
	rm -rf ./*.o
	rm -rf ./*.a
	rm -rf ./*.out
