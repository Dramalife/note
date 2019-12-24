The Single UNIX (R) Specification, Version 2
Copyright (C) 1997 The Open Group

------

####  NAME

> pthread_cond_signal, pthread_cond_broadcast - signal or broadcast a condition

####  SYNOPSIS

> ```
> #include <pthread.h>
> 
> int pthread_cond_signal(pthread_cond_t *cond);
> int pthread_cond_broadcast(pthread_cond_t *cond);
> ```

####  DESCRIPTION

> These two functions are used to unblock threads blocked on a condition variable.
>
> The *pthread_cond_signal()* call unblocks at least one of the threads that are blocked on the specified condition variable *cond*(if any threads are blocked on *cond*).
>
> The *pthread_cond_broadcast()* call unblocks all threads currently blocked on the specified condition variable *cond*.
>
> If more than one thread is blocked on a condition variable, the scheduling policy determines the order in which threads are unblocked. When each thread unblocked as a result of a *pthread_cond_signal()* or *pthread_cond_broadcast()* returns from its call to *[pthread_cond_wait()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_wait.html)* or *[pthread_cond_timedwait()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_timedwait.html)*, the thread owns the mutex with which it called *[pthread_cond_wait()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_wait.html)*or *[pthread_cond_timedwait()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_timedwait.html)*. The thread(s) that are unblocked contend for the mutex according to the scheduling policy (if applicable), and as if each had called *[pthread_mutex_lock()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_mutex_lock.html)*.
>
> The *pthread_cond_signal()* or *pthread_cond_broadcast()* functions may be called by a thread whether or not it currently owns the mutex that threads calling *[pthread_cond_wait()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_wait.html)* or *[pthread_cond_timedwait()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_timedwait.html)* have associated with the condition variable during their waits; however, if predictable scheduling behaviour is required, then that mutex is locked by the thread calling*pthread_cond_signal()* or *pthread_cond_broadcast()*.
>
> The *pthread_cond_signal()* and *pthread_cond_broadcast()* functions have no effect if there are no threads currently blocked on*cond*.

####  RETURN VALUE

> If successful, the *pthread_cond_signal()* and *pthread_cond_broadcast()* functions return zero. Otherwise, an error number is returned to indicate the error.

####  ERRORS

> The *pthread_cond_signal()**pthread_cond_broadcast()*
>
> - [EINVAL]
>
>   The value *cond* does not refer to an initialised condition variable.
>
> These functions will not return an error code of [EINTR].

####  EXAMPLES

> None.

####  APPLICATION USAGE

> None.

####  FUTURE DIRECTIONS

> None.

####  SEE ALSO

> *[pthread_cond_init()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_init.html)*, *[pthread_cond_wait()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_wait.html)*, *[pthread_cond_timedwait()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_timedwait.html)*, *[](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread.h.html)*. 

#### DERIVATION

> Derived from the POSIX Threads Extension (1003.1c-1995)

------

UNIX (R) is a registered Trademark of The Open Group.
Copyright (C) 1997 The Open Group 
[ [Main Index](https://pubs.opengroup.org/onlinepubs/007908775/index.html) | [XSH](https://pubs.opengroup.org/onlinepubs/007908775/xshix.html) | [XCU](https://pubs.opengroup.org/onlinepubs/007908775/xcuix.html) | [XBD](https://pubs.opengroup.org/onlinepubs/007908775/xbdix.html) | [XCURSES](https://pubs.opengroup.org/onlinepubs/007908775/cursesix.html) | [XNS](https://pubs.opengroup.org/onlinepubs/007908775/xnsix.html) ]

------