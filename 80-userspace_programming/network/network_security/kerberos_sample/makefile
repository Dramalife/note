all: kdc_service client_pass client_error

kdc_service:
	gcc -o kdc_service.out kdc_as.c pub.c -I. -Wall -I../../../../lib_dramalife
client_pass:
	gcc -o client_pass.out usr.c pub.c -I. -Wall -I../../../../lib_dramalife
client_error:
	gcc -o client_error.out usr.c pub.c -I. -Wall -I../../../../lib_dramalife -DTEST_ERROR

clean:
	rm -rvf ./*.out

# Not used below
as:
	gcc -o as.out kdc_as.c pub.c -I. -Wall -I../../../../lib_dramalife
tgs:
	gcc -o tgs.out kdc_tgs.c pub.c -I. -Wall -I../../../../lib_dramalife
usr:
	gcc -o usr.out usr.c pub.c -I. -Wall -I../../../../lib_dramalife
usr-error:
	gcc -o usr.out usr.c pub.c -I. -Wall -I../../../../lib_dramalife -DTEST_ERROR
server:
	gcc -o server.out server.c pub.c -I. -Wall -I../../../../lib_dramalife
