## [linux下的僵尸进程处理SIGCHLD信号](https://www.cnblogs.com/wuchanming/p/4020463.html)

### 什么是僵尸进程？

首先内核会释放终止进程(调用了exit系统调用)所使用的所有存储区，关闭所有打开的文件等，但内核为每一个终止子进程保存了一定量的信息。
这些信息至少包括进程ID，进程的终止状态，以及该进程使用的CPU时间，所以当终止子进程的父进程调用wait或waitpid时就可以得到这些信息。
而僵尸进程就是指：一个进程执行了exit系统调用退出，而其父进程并没有为它收尸(调用wait或waitpid来获得它的结束状态)的进程。
任何一个子进程(init除外)在exit后并非马上就消失，而是留下一个称外僵尸进程的数据结构，等待父进程处理。这是每个子进程都必需经历的阶段。
另外子进程退出的时候会向其父进程发送一个SIGCHLD信号。

### 僵尸进程的目的？

设置僵死状态的目的是维护子进程的信息，以便父进程在以后某个时候获取。
这些信息至少包括进程ID，进程的终止状态，以及该进程使用的CPU时间，所以当终止子进程的父进程调用wait或waitpid时就可以得到这些信息。
如果一个进程终止，而该进程有子进程处于僵尸状态，那么它的所有僵尸子进程的父进程ID将被重置为1（init进程）。
继承这些子进程的init进程将清理它们（也就是说init进程将wait它们，从而去除它们的僵尸状态）。

### 如何避免僵尸进程？

1. 通过signal(SIGCHLD, SIG_IGN)通知内核对子进程的结束不关心，**由内核回收**。\
如果不想让父进程挂起，可以在父进程中加入一条语句：signal(SIGCHLD,SIG_IGN);表示父进程忽略SIGCHLD信号，该信号是子进程退出的时候向父进程发送的。\
2. 父进程调用wait/waitpid等函数等待子进程结束，如果尚无子进程退出wait会导致父进程**阻塞**。waitpid可以通过传递WNOHANG使父进程不阻塞立即返回。\
3. 如果父进程很忙可以用signal注册信号处理函数，在信号处理函数调用wait/waitpid等待子进程退出。\
4. 通过两次调用fork。父进程首先调用fork创建一个子进程然后waitpid等待子进程退出，子进程再fork一个孙进程后退出。
这样子进程退出后会被父进程等待回收，而对于孙子进程其父进程已经退出所以孙进程成为一个孤儿进程，孤儿进程由init进程接管，孙进程结束后，init会等待回收。\
\
第一种方法忽略SIGCHLD信号，这常用于并发服务器的**性能**的一个技巧因为并发服务器常常fork很多子进程，子进程终结之后需要服务器进程去wait清理资源。
如果将此信号的处理方式设为忽略，可让内核把僵尸子进程转交给init进程去处理，省去了大量僵尸进程占用系统资源。

### 僵尸进程处理办法
#### 1 wait()函数
```
#include <sys/types.h> 
#include <sys/wait.h>

pid_t wait(int *status);
```
进程一旦调用了wait，就立即阻塞自己，由wait自动分析是否当前进程的某个子进程已经退出，如果让它找到了这样一个已经变成僵尸的子进程，wait就会收集这个子进程的信息，并把它彻底销毁后返回；如果没有找到这样一个子进程，wait就会一直阻塞在这里，直到有一个出现为止。 
参数status用来保存被收集进程退出时的一些状态，它是一个指向int类型的指针。但如果我们对这个子进程是如何死掉的毫不在意，只想把这个僵尸进程消灭掉，（事实上绝大多数情况下，我们都会这样想），我们就可以设定这个参数为NULL，就象下面这样：
```
  pid = wait(NULL);
```
如果成功，wait会返回被收集的子进程的进程ID，如果调用进程没有子进程，调用就会失败，此时wait返回-1，同时errno被置为ECHILD。\
1. wait系统调用会使父进程暂停执行，直到它的一个子进程结束为止。\
2. 返回的是子进程的PID，它通常是结束的子进程\
3. 状态信息允许父进程判定子进程的退出状态，即从子进程的main函数返回的值或子进程中exit语句的退出码。\
4. 如果status不是一个空指针，状态信息将被写入它指向的位置\
可以上述的一些宏判断子进程的退出情况：
sys/wait.h


#### 2 waitpid()函数
```
#include <sys/types.h> 
#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *status, int options);
```
参数:

status:如果不是空，会把状态信息写到它指向的位置，与wait一样

options：允许改变waitpid的行为，最有用的一个选项是WNOHANG,它的作用是防止waitpid把调用者的执行挂起
```
The value of options is an OR of zero or more  of  the  following  con- 
stants:

WNOHANG     return immediately if no child has exited.

WUNTRACED   also  return  if  a  child  has stopped (but not traced via 
            ptrace(2)).  Status for traced children which have  stopped 
            is provided even if this option is not specified.

WCONTINUED (since Linux 2.6.10) 
            also return if a stopped child has been resumed by delivery 
            of SIGCONT.
```
\
返回值：如果成功返回等待子进程的ID，失败返回-1

对于waitpid的p i d参数的解释与其值有关：

|a|b|
|--|--|
|pid == -1 |等待任一子进程。于是在这一功能方面waitpid与wait等效。|
|pid > 0   |等待其进程I D与p i d相等的子进程。|
|pid == 0  |等待其组I D等于调用进程的组I D的任一子进程。换句话说是与调用者进程同在一个组的进程。|
|pid < -1  |等待其组I D等于p i d的绝对值的任一子进程|

wait与waitpid区别：
在一个子进程终止前， wait 使其调用者阻塞，而waitpid 有一选择项，可使调用者不阻塞。\
waitpid并不等待第一个终止的子进程—它有若干个选择项，可以控制它所等待的特定进程。\
实际上wait函数是waitpid函数的一个特例。waitpid(-1, &status, 0);\
 

#### 示例：

如以下代码会创建100个子进程，但是父进程并未等待它们结束，所以在父进程退出前会有100个僵尸进程。
```
#include <stdio.h>  
#include <unistd.h>  
   
int main() {  
   
  int i;  
  pid_t pid;  
   
  for(i=0; i<100; i++) {  
    pid = fork();  
    if(pid == 0)  
      break;  
  }  
   
  if(pid>0) {  
    printf("press Enter to exit...");  
    getchar();  
  }  
   
  return 0;  
}
```
其中一个解决方法即是编写一个SIGCHLD信号处理程序来调用wait/waitpid来等待子进程返回。
```
#include <stdio.h>  
#include <unistd.h>  
#include <signal.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
   
void wait4children(int signo) {  
   
  int status;  
  wait(&status);  
   
}  
   
int main() {  
   
  int i;  
  pid_t pid;  
   
  signal(SIGCHLD, wait4children);  
   
  for(i=0; i<100; i++) {  
    pid = fork();  
    if(pid == 0)  
      break;  
  }  
   
  if(pid>0) {  
    printf("press Enter to exit...");  
    getchar();  
  }  
   
  return 0;  
}
```
但是通过运行程序发现还是会有僵尸进程，而且每次僵尸进程的数量都不定。
这是为什么呢？其实主要是因为Linux的信号机制是不排队的，
假如在某一时间段多个子进程退出后都会发出SIGCHLD信号，但父进程来不及一个一个地响应，所以最后父进程实际上只执行了一次信号处理函数。
但执行一次信号处理函数只等待一个子进程退出，所以最后会有一些子进程依然是僵尸进程。
虽然这样但是有一点是明了的，就是收到SIGCHLD必然有子进程退出，
而我们可以在信号处理函数里循环调用waitpid函数来等待所有的退出的子进程。
至于为什么不用wait，主要原因是在wait在清理完所有僵尸进程后再次等待会阻塞。
所以最佳方案如下：
```
#include <stdio.h>  
#include <unistd.h>  
#include <signal.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
   
void wait4children(int signo) {  
  int status;  
  while(waitpid(-1, &status, WNOHANG) > 0);  
}  
   
int main() {  
   
  int i;  
  pid_t pid;  
   
  signal(SIGCHLD, wait4children);  
   
  for(i=0; i<100; i++) {  
    pid = fork();  
    if(pid == 0)  
      break;  
  }  
   
  if(pid>0) {  
    printf("press Enter to exit...");  
    getchar();  
  }  
   
  return 0;  
}
```
这里使用waitpid而不是使用wait的原因在于：我们在一个循环内调用waitpid，以获取所有已终止子进程的状态。
我们必须指定WNOHANG选项，它告诉waitpid在有尚未终止的子进程在运行时不要阻塞。
我们不能在循环内调用wait，因为没有办法防止wait在正运行的子进程尚有未终止时阻塞。
