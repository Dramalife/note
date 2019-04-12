SRC=bad_ping_multithread
TAR=ping_mthread

$(TAR): $(SRC).o
	gcc -o $@ $< -lpthread
clean:
	rm $(TAR) *.o
