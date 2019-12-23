all_with_mutex:
	gcc thread_incr.c -lpthread -DTHREAD_SYNC_DL_CONTROL=1

all_without_mutex:
	gcc thread_incr.c -lpthread -DTHREAD_SYNC_DL_CONTROL=0
clean:
	rm -rvf *.out
