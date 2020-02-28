**1. Source**(来源)

<\<The Linux Programming Interface>> - Chapter 37



**2. Related**(相关内容)

setsid()

umask()

chdir()

singleton running(file lock)



**3. Creating a Daemon**(创建守护进程)

1. Execute a fork (), after which the parent process exits and the child process continues execution. (The result is that the daemon becomes a child of the init process.) This step is done for two reasons:

   (CH:执行一个fork()，之后父进程退出，子进程继续执行。（结果是daemon成为了init进程的子进程。）之所以要做这一步是因为下面两个原因：)

   - Assuming that the daemon is started from the command line, the termination of the parent process will be detected by the shell. After the shell is discovered, the shell will display another shell prompt and let the child process continue to run in the background.(CH:假设daemon是从命令行启动的，父进程的终止会被shell发现，shell在发现之后会显示出另一个shell提示符并让子进程继续在后台运行。)
   - The child process is guaranteed not to be the first process group process, because it inherits the process group ID from the parent process and has its own unique process ID, and this process ID is different from the inherited process group ID. This will allow you to successfully perform the next step.(CH:子进程被确保不会成为一个进程组首进程，因为它从父进程哪里继承了进程组ID并且拥有了自己的唯一的进程ID，而这个进程ID与继承而来的进程组ID是不同的，这样才能够成功执行下面一个步骤。)

2. The child process calls setsid () to start a new session and release all the associations between it and the controlling terminal.(CH:子进程调用setsid()开启一个新会话并释放它与控制终端之间的所有关联关系。)

3. If the daemon has never opened a terminal device, then there is no need to worry about the daemon re-requesting a controlling terminal. If a terminal device may be opened by the daemon, measures must be taken to ensure that the device does not become the controlling terminal. This can be achieved in the following two ways.(CH:如果daemon从来没有打开过终端设备，那么就无需担心daemon会重新请求一个控制终端了。如果daemon后面可能会打开一个终端设备，那么必须要采取措施来确保这个设备不会成为控制终端。这可以通过下面两种方式实现。)

   - Specify the O_NOCTTY flag in all open () calls that may apply to a terminal device.(CH:在所有可能应用到一个终端设备上的open()调用中指定O_NOCTTY标记。)
   - Or more simply, execute the second fork () after the setsid () call, and then let the parent process exit again and let the grandson process continue execution. This ensures that the child process does not become the session leader, so according to the rules for obtaining terminals in System V (Linux also follows this rule), the process will never re-request a controlling terminal.(CH:或者更简单地说，在setsid()调用之后执行第二个fork()，然后再次让父进程退出并让孙子进程继续执行。这样就确保了子进程不会成为会话组长，因此根据System V中获取终端的规则(Linux也遵循了这个规则)，进程永远不会重新请求一个控制终端。)

4. Clear the umask of the process to ensure that the daemon has the required permissions when creating files and directories.(CH:清除进程的umask以确保当daemon创建文件和目录时拥有所需的权限。)

5. chdir(); May cause file system to fail to unmount;

6. fd; May cause file system to fail to unmount;

7. dup2(/dev/null)

   libc

   

**4. Reinitialize a daemon**(重新初始化一个守护进程)

**4.1 Sample**(示例)

SIGHUP(control termianl closed)



**5. Termination of the daemon**(守护进程的终止)

When the system shuts down, (1) the process executes application-specific scripts, or (2) uses its own signal processing functions to perform cleanup.(CH:当系统关闭，（1）进程执行特定于应用程序的脚本，或者（2）使用自身的信号处理函数，来执行清理工作。)

**5.1 Scripts**(脚本)

**5.2 Signal**(信号)

The init process sends a SIGKILL signal 5 seconds after sending the SIGTERM signal.(CH:init进程在发完SIGTERM信号的5秒之后会发送SIGKILL信号。)









