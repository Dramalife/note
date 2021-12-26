all: server.out client.out
server.out: server.o
	gcc -o server.out server.o
client.out: client.o
	gcc -o client.out client.o
clean:
	rm -rvf *.out *.o

format:
	~/note/lib_dramalife/exec_files/format_c_cpp.sh

tcpdump:
	sudo tcpdump tcp port 10008 -i lo
