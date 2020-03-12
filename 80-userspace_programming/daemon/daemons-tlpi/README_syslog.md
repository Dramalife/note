> REF : <\<THE LINUX PROGRAMMING INTERFACE>>  

NOTE : Please read on github or Linux environment for best format alignment.
(CH:注意：请在github或Linux环境上阅读以获得最佳格式对齐。)

## 1. syslog overview(CH:系统日志概览)

```
	kernel
	  | printk()
	  |
	  | syslog(2), /proc/kmsg
	  |
	klogd				usr_program			remote_host_prog
	  | syslog(3)			    |syslog(3)				| TCP/IP
	  |				    |					|
	  ``````````````````````|````````````					|
				| /dev/log or /var/run/log			| UDP(514)
				| (UNIX domain datagram socket)			|
				|						|
				````````````````````````|````````````````````````
							|
						     syslogd ------syslog.conf
							|
							|
				|```````````|```````````|```````````|```````````|
				|	    |		|	    |		|
			    terminal/	  FIFO	     Disk file	 remote	      login
			    console				 - host	      - user
```
- syslog(2)：系统调用
- syslog(3)：库函数
- usr_program：用户进程

## 2. syslog API

closelog, openlog, syslog, vsyslog - send messages to the system logger(这些API被用来将消息发送到系统记录器).	----SYSLOG(3)  
None of these functions return a value(这些函数都没有返回值).  

```c
#include <syslog.h>
```

### 2.1 openlog()
```c
void openlog(const char *ident, int option, int facility);
```

#### 2.1.1 DESCRIPTION(描述)
SYSLOG(3)  \
&emsp;   openlog()  \
       openlog() opens a connection to the system logger for a program.  \
  \
       The  string  pointed  to  by ***ident*** is prepended to every message, and is typically set to **the program name**.  If ident is NULL, the program name is used.  (POSIX.1-2008 does not specify the behavior when ident is  \
       NULL.)  
  \
       The ***option(log_options)*** argument specifies flags which control the operation of openlog() and subsequent calls to syslog().  The ***facility***(记录消息的应用程序的类型，参考2.1.3) argument establishes a default to be used if none is specified in subsequent calls  to  \
       syslog().  The values that may be specified for option and facility are described below.  \
  \
       The use of openlog() is **optional**; it will automatically be called by syslog() if necessary, in which case ident will default to NULL.  
  
#### 2.1.2 Values for option
&emsp;  The option argument to openlog() is a bit mask constructed by ORing together any of the following values: 
| Flag  | Description|
|:--|:--|
| LOG_CONS       | Write directly to the system console if there is an error while sending to the system logger.(CH：如果在发送到系统记录器时出错，则直接写到系统控制台(/dev/console)。) |
| LOG_NDELAY     | Open  the  connection  immediately  (normally,  the connection is opened when the first message is logged).  This may be useful, for example, if a subsequent chroot(2) would make the pathname used internally by the logging facility unreachable.(CH:立即打开到syslogd的连接。默认是LOG_ODELAY，这种情况下只有记录第一条日志消息的时候，才会打开连接。举例：chroot()与tftpd daemon。(具体原因：TODO。)) |
| LOG_NOWAIT     | Don't wait for child processes that may have been created while logging the message.  (The GNU C library does not create a child process, so this option has no effect on Linux.)  (CH:...此选项对Linux无效。) |
| LOG_ODELAY     | The converse of LOG_NDELAY; opening of the connection is delayed until syslog() is called.  (This is the default, and need not be specified.)(CH：与LOG_NDELAY相反； 连接的打开被延迟，直到调用syslog()为止。(这是默认设置，无需指定。)) |
| LOG_PERROR     | (Not in POSIX.1-2001 or POSIX.1-2008.)  Also log the message to stderr.(CH:还将消息记录到stderr。注意：通常daemon会关闭标准错误或将其重定向到/dev/null，这样LOG_PERROR就没有用了。) |
| LOG_PID        | Include the caller's PID with each message. |

#### 2.1.3 Values for facility
&emsp;  The facility argument is used to specify what type of program is logging the message.  This lets the configuration file specify that messages from different facilities will be handled differently.
| Vaule  | Description   | SUSv3 |
|:--|:--|:--|
|LOG_AUTH                       |security/authorization messages                                         |      |                                                                                                               
|LOG_AUTHPRIV                   |security/authorization messages (private)                               |      |   
|LOG_CRON                       |clock daemon (cron and at)                                              |      |   
|LOG_DAEMON                     |system daemons without separate facility value                          |      |   
|LOG_FTP                        |ftp daemon                                                              |      |   
|LOG_KERN                       |kernel messages (these can't be generated from user processes)          |      |   
|LOG_LOCAL0 through LOG_LOCAL7  |reserved for local use                                                  |      |   
|LOG_LPR                        |line printer subsystem                                                  |      |   
|LOG_MAIL                       |mail subsystem                                                          |      |   
|LOG_NEWS                       |USENET news subsystem                                                   |      |   
|LOG_SYSLOG                     |messages generated internally by syslogd(8)                             |      |   
|LOG_USER (default)             |generic user-level messages                                             |      |   
|LOG_UUCP                       |UUCP subsystem                                                          |      |   




### 2.2 syslog()  
```c
void syslog(int priority, const char *format, ...);
```
#### 2.2.1 DESCRIPTION
&emsp;  syslog() and vsyslog()  \
       syslog() generates a log message, which will be distributed by syslogd(8).  \
  \
       The  ***priority*** argument is formed by ORing together a **facility** value and a ***level***(消息的严重程度) value (described below).  If no facility value is ORed into priority, then the default value set by openlog() is used, or, if there  \
       was no preceding openlog() call, a default of LOG_USER is employed.  \
  \
       The remaining arguments are a ***format***, as in printf(3), and any arguments required by the format, except that the two-character sequence %m will be replaced by the error message string strerror(errno).  The  for‐  \
       mat string need not include a terminating newline character.  \
  \
       The function vsyslog() performs the same task as syslog() with the difference that it takes a set of arguments which have been obtained using the stdarg(3) variable argument list macros.  
#### 2.2.2 Values for level
&emsp;  This determines the importance of the message.  The levels are, in order of decreasing importance:
| Vaule  | Description    |
|:--|:--|
|LOG_EMERG      |system is unusable                     |                                                                                                                                                                       
|LOG_ALERT      |action must be taken immediately|
|LOG_CRIT       |critical conditions|
|LOG_ERR        |error conditions|
|LOG_WARNING    |warning conditions|
|LOG_NOTICE     |normal, but significant, condition|
|LOG_INFO       |informational message|
|LOG_DEBUG      |debug-level message                    |   
The function setlogmask(3) can be used to restrict logging to specified levels only.



### 2.3 closelog()

```c
void closelog(void);
```

### 2.4 vsyslog() [GNU libc]

```c
/*
Feature Test Macro Requirements for glibc (see feature_test_macros(7)):
Since glibc 2.19:
	_DEFAULT_SOURCE
Glibc 2.19 and earlier:
	_BSD_SOURCE
*/ 
void vsyslog(int priority, const char *format, va_list ap);
```

## 3 /etc/syslog.conf（syslogd配置）
### 3.1 rsyslogd
- CONF_FILE : /etc/rsyslog.d/50-default.conf
```diff
+ local6.*                        /tmp/wjy.log
```

### 3.2 syslogd(BusyBox v1.31.1)
- CONF_FILE : /etc/syslog.conf
```diff
+ local6.* /tmp/iec104.log
```


## 4 Sample(示例)
Source code
```c

```
Shell
```bash
root@Ubuntu18-BPI-R2:~/note/80-userspace_programming/syslog/syslog-tlpi # ./t_syslog.out -p -l a hahahaha
root@Ubuntu18-BPI-R2:~/note/80-userspace_programming/syslog/syslog-tlpi # ./t_syslog.out -p -l e hahahaha
root@Ubuntu18-BPI-R2:~/note/80-userspace_programming/syslog/syslog-tlpi # cat /var/log/syslog | grep "t_syslog.out"
Mar 11 13:51:19 Ubuntu18-BPI-R2 ./t_syslog.out[1182]: hahahaha
Mar 11 13:51:22 Ubuntu18-BPI-R2 ./t_syslog.out[1183]: hahahaha
```
|Date |Time |Hostname |Processname |PID |Usr Message |
|--|--|--|--|--|--|
|Mar 11 |13:51:22 |Ubuntu18-BPI-R2 |./t_syslog.out|[1183]|hahahaha |
|日期|时间|主机名|进程名|PID|用户消息|

## 5 Summary (facility , level & priority)
openlog(const char *ident, int option, int facility);
syslog(int priority, const char *format, ...);

facility;
level;
priority = facility | level;

facility = LOG_USER; level = LOG_DEBUG;
user.debug /tmp/user_debug.log

facility = LOG_LOCAL6; level = LOG_ERR;
local6.err /tmp/local6_err.log


