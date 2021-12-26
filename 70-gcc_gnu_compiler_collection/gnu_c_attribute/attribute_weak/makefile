all: only_weak.out with_strong.out

only_weak.out: main.o
	$(CC) -o only_weak.out \
	main.o

with_strong.out: main.o strong.o
	$(CC) -o with_strong.out \
	main.o \
	strong.o

clean:
	rm -rvf *.out *.o
