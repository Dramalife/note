all: as usr tgs

as:
	gcc -o as.out kdc_as.c pub.c -I. -Wall -I../../../../lib_dramalife
tgs:
	gcc -o tgs.out kdc_tgs.c pub.c -I. -Wall -I../../../../lib_dramalife
usr:
	gcc -o usr.out usr.c pub.c -I. -Wall -I../../../../lib_dramalife
server:
	gcc -o server.out server.c pub.c -I. -Wall -I../../../../lib_dramalife

clean:
	rm -rvf ./*.out
