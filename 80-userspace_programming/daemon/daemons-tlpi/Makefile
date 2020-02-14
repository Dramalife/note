test:
	@echo "MAKING TEST..."
	gcc -o test_become_daemon.out become_daemon.c test_become_daemon.c -DEXIT_SUCCESS=0 -DgetInt=strtol
signal:
	@echo "MAKING SIGNAL..."
	gcc -o daemon_SIGHUP.out become_daemon.c daemon_SIGHUP.c -DDL_REPLACE_TLPI_HDR_H=1 -DEXIT_SUCCESS=0 -DEXIT_FAILURE=1
clean_all:
	@echo "MAKING CLEAN..."
	rm -rvf ./*.o ./*.out
