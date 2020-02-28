### 1. Change Log
|Date|Events|
|--|--|
|2020.02.13		|Init this floder;	|
|2020.02.13 	|COPY FROM tlpi/daemon; <br>Del file : t_syslog.c; <br>Replace file : Makefile;  <br>Add file : README.md(This file);  |
|2020.02.17			|Add file : t_syslog.c(copy from tlpi/daemon/t_syslog.c);  <br>symbol linked by (../syslog/syslog-tlpi); <br>Formatting; |

  

### 2. Files
|File|Description|
|--|--|
|README.md		| [daemon] This file|
|become_daemon.c		| [daemon] lib file|
|become_daemon.h		| [daemon] header file|
|daemon_SIGHUP.c		| [daemon] program main file|
|test_become_daemon.c	| [daemon] program main file|
|t_syslog.c		| [syslog] program main file|

   

### 3. Referenced
|No|Ref|
|--|--|
| 1|symbol linked by [syslog-tlpi](/80-userspace_programming//syslog/syslog-tlpi)	|



### 4. DAEMON
|||
|--|--|
|SRC	| <\<THE LINUX PROGRAMMING INTERFACE>>	chapter 37	|
|KEY_WORDS	|signal <br>tty <br>fd <br>memory <br><br>configuration <br>log <br><br>daemon()[glibc]	 |

see [README_daemon.md](/80-userspace_programming/daemon/daemons-tlpi//80-userspace_programming/daemon/daemons-tlpi)  



### 5. SYSLOG
|||
|--|--|
|SRC 	|<\<THE LINUX PROGRAMMING INTERFACE>>	chapter 37.5	|
|KEY_WORDS	|openlog() <br>syslog() <br>closelog()	|

