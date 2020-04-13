all:client server
client:
	gcc client.c -lpthread -I../../../lib_dramalife -o client.out
server:.prepare
	gcc server.c -ldramalife -lpthread -ldl -I../../../lib_dramalife -L. -Wl,-rpath=. -o server.out
.prepare:
	make -C ../../../lib_dramalife/ all
	ln -sf ../../../lib_dramalife/libdramalife.so .
clean:
	rm -rvf ./*.out ./*.so
	-mv -f ./*.db /tmp
