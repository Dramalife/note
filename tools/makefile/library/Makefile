main: libadddec.a main.c
	$(CC) -Wl,--verbose -Wl,-Map=a.map main.c libadddec.a -Xlinker -L. -I. -lpthread -o main
libadddec.a: add.o dec.o
	ar rs libadddec.a add.o dec.o
clean:
	rm *.o
	rm *.a
	rm main
