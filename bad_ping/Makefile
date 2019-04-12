SRC=bad_ping_multithread
TAR=ping_mthread.out

$(TAR): $(SRC).o
	gcc -o $@ $< -lpthread
#TODO
	echo -e "\e[0;31mTODO : status output by format ...output/cursorxx.c\e[0m"
clean:
	rm -f $(TAR) *.o
