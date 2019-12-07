DESCRIPTION - description of function pipe()
----------
man 2 pipe
pipe() creates a pipe, a unidirectional data channel that can be used for interprocess communication.  The array pipefd is used to return
two file descriptors referring to the ends of the pipe.  pipefd[0] refers to the read end of the pipe.  pipefd[1] refers to the write end
of  the  pipe.   Data written to the write end of the pipe is buffered by the kernel until it is read from the read end of the pipe.  For
further details, see pipe(7).


BUFF SIZE - buffer size of pipe
----------
/* Pipe buff size, <limits.h> 
 *   When data written by multi-processes, 
 * each time should not exceed PIPE_BUF bytes, 
 * else kernel will divide the data into few parts, 
 * which causing data crossover.
 *   It doesn`t matter when only one process 
 * writes data.
 */


USING LIMITS - pipe can be only used with "related processes"
----------
IPC between the process and its son or grand..son .


CLOSING UNUSED FD - why closing unused fd?
----------
* REF : THE LINUX PROGRAMMING INTERFACE, page733.
* Close unused write fd in reading process
If not, will not see EOF.
* Close unused read fd in writing process
We need signal SIGPIPE or EPIPE ;-)

