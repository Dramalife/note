all: as usr tgs

as:
	gcc -o as.out kdc_as.c pub.c -I. -Wall
tgs:
	gcc -o tgs.out kdc_tgs.c pub.c -I. -Wall
usr:
	gcc -o usr.out usr.c pub.c -I. -Wall
server:
	gcc -o server.out server.c pub.c -I. -Wall

clean:
	rm -rvf ./*.out
