all_with_mutex:
	gcc prod_condvar.c -lpthread -DTHREAD_SYNC_DL_CONTROL=1

all_without_mutex:
	gcc prod_condvar.c -lpthread -DTHREAD_SYNC_DL_CONTROL=0
clean:
	rm -rvf *.out
