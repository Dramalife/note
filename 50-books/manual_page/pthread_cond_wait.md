The Single UNIX (R) Specification, Version 2
Copyright (C) 1997 The Open Group

------

####  NAME

> pthread_cond_wait, pthread_cond_timedwait - wait on a condition

####  SYNOPSIS

> ```
> #include <pthread.h>
> 
> int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
> int pthread_cond_timedwait(pthread_cond_t *cond, 
>     pthread_mutex_t *mutex, const struct timespec *abstime);
> ```

####  DESCRIPTION

> The *pthread_cond_wait()* and *pthread_cond_timedwait()* functions are used to block on a condition variable. They are called with *mutex* locked by the calling thread or undefined behaviour will result. 
>
> These functions atomically release *mutex* and cause the calling thread to block on the condition variable *cond*; atomically here means "atomically with respect to access by another thread to the mutex and then the condition variable". That is, if another thread is able to acquire the mutex after the about-to-block thread has released it, then a subsequent call to*[pthread_cond_signal()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_signal.html)* or *[pthread_cond_broadcast()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_broadcast.html)* in that thread behaves as if it were issued after the about-to-block thread has blocked.
>
> Upon successful return, the mutex has been locked and is owned by the calling thread.
>
> When using condition variables there is always a boolean predicate involving shared variables associated with each condition wait that is true if the thread should proceed. Spurious wakeups from the *pthread_cond_wait()* or *pthread_cond_timedwait()*functions may occur. Since the return from *pthread_cond_wait()* or *pthread_cond_timedwait()* does not imply anything about the value of this predicate, the predicate should be re-evaluated upon such return.
>
> The effect of using more than one mutex for concurrent *pthread_cond_wait()* or *pthread_cond_timedwait()* operations on the same condition variable is undefined; that is, a condition variable becomes bound to a unique mutex when a thread waits on the condition variable, and this (dynamic) binding ends when the wait returns.
>
> A condition wait (whether timed or not) is a cancellation point. When the cancelability enable state of a thread is set to PTHREAD_CANCEL_DEFERRED, a side effect of acting upon a cancellation request while in a condition wait is that the mutex is (in effect) re-acquired before calling the first cancellation cleanup handler. The effect is as if the thread were unblocked, allowed to execute up to the point of returning from the call to *pthread_cond_wait()* or *pthread_cond_timedwait()*, but at that point notices the cancellation request and instead of returning to the caller of *pthread_cond_wait()* or*pthread_cond_timedwait()*, starts the thread cancellation activities, which includes calling cancellation cleanup handlers.
>
> A thread that has been unblocked because it has been canceled while blocked in a call to *pthread_cond_wait()* or*pthread_cond_timedwait()* does not consume any condition signal that may be directed concurrently at the condition variable if there are other threads blocked on the condition variable.
>
> The *pthread_cond_timedwait()* function is the same as *pthread_cond_wait()* except that an error is returned if the absolute time specified by *abstime* passes (that is, system time equals or exceeds *abstime*) before the condition *cond* is signaled or broadcasted, or if the absolute time specified by *abstime* has already been passed at the time of the call. When such time-outs occur, *pthread_cond_timedwait()* will nonetheless release and reacquire the mutex referenced by *mutex*. The function*pthread_cond_timedwait()* is also a cancellation point.
>
> If a signal is delivered to a thread waiting for a condition variable, upon return from the signal handler the thread resumes waiting for the condition variable as if it was not interrupted, or it returns zero due to spurious wakeup.

####  RETURN VALUE

> Except in the case of [ETIMEDOUT], all these error checks act as if they were performed immediately at the beginning of processing for the function and cause an error return, in effect, prior to modifying the state of the mutex specified by *mutex*or the condition variable specified by *cond*. 
>
> Upon successful completion, a value of zero is returned. Otherwise, an error number is returned to indicate the error.

####  ERRORS

> The *pthread_cond_timedwait()*
>
> - [ETIMEDOUT]
>
>   The time specified by *abstime* to *pthread_cond_timedwait()* has passed.
>
> The *pthread_cond_wait()* and *pthread_cond_timedwait()* functions may fail if:
>
> - [EINVAL]
>
>   The value specified by *cond*, *mutex*, or *abstime* is invalid.
>
> - [EINVAL]
>
>   Different mutexes were supplied for concurrent *pthread_cond_wait()* or *pthread_cond_timedwait()* operations on the same condition variable.
>
> - [EINVAL]
>
>   The mutex was not owned by the current thread at the time of the call.
>
> These functions will not return an error code of [EINTR].

####  EXAMPLES

> None.

####  APPLICATION USAGE

> None.

####  FUTURE DIRECTIONS

> None.

####  SEE ALSO

> *[pthread_cond_signal()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_signal.html)*, *[pthread_cond_broadcast()](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread_cond_broadcast.html)*, *[](https://pubs.opengroup.org/onlinepubs/007908775/xsh/pthread.h.html)*.

#### DERIVATION

> Derived from the POSIX Threads Extension (1003.1c-1995)

------

UNIX (R) is a registered Trademark of The Open Group.
Copyright (C) 1997 The Open Group 
[ [Main Index](https://pubs.opengroup.org/onlinepubs/007908775/index.html) | [XSH](https://pubs.opengroup.org/onlinepubs/007908775/xshix.html) | [XCU](https://pubs.opengroup.org/onlinepubs/007908775/xcuix.html) | [XBD](https://pubs.opengroup.org/onlinepubs/007908775/xbdix.html) | [XCURSES](https://pubs.opengroup.org/onlinepubs/007908775/cursesix.html) | [XNS](https://pubs.opengroup.org/onlinepubs/007908775/xnsix.html) ]

------