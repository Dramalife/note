
# getrlimit(2)
	getrlimit, setrlimit, prlimit - get/set resource limits
	int getrlimit(int resource, struct rlimit *rlim);
	int setrlimit(int resource, const struct rlimit *rlim);
	int prlimit(pid_t pid, int resource, const struct rlimit *new_limit,
			struct rlimit *old_limit);

# pthread_attr_init(3)
	pthread_attr_init, pthread_attr_destroy - initialize and destroy thread attributes object
	int pthread_attr_init(pthread_attr_t *attr);
	int pthread_attr_destroy(pthread_attr_t *attr);

# pthread_create(3)
	pthread_create - create a new thread
	int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	                          void *(*start_routine) (void *), void *arg);

# pthread_cancel(3)
	pthread_cancel - send a cancellation request to a thread
	int pthread_cancel(pthread_t thread);

# pthread_detach(3)
	pthread_detach - detach a thread
	int pthread_detach(pthread_t thread);

# pthread_equal(3)
	pthread_equal - compare thread IDs
	int pthread_equal(pthread_t t1, pthread_t t2);

# pthread_exit(3)
	pthread_exit - terminate calling thread
	void pthread_exit(void *retval);

# pthread_getattr_np(3)
	pthread_getattr_np - get attributes of created thread
	int pthread_getattr_np(pthread_t thread, pthread_attr_t *attr);

# pthread_join(3)
	pthread_join - join with a terminated thread
	int pthread_join(pthread_t thread, void **retval);

# pthread_self(3)
	pthread_self - obtain ID of the calling thread
	pthread_t pthread_self(void);

# pthread_setattr_default_np(3)

# pthreads(7)

# pthread_sigmask(3)
	pthread_sigmask - examine and change mask of blocked signals
	int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);

