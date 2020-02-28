>REF : <\<THE LINUX PROGRAMMING INTERFACE>>  

NOTE : Please read on github or Linux environment for best format alignment.
(CH:注意：请在github或Linux环境上阅读以获得最佳格式对齐。)

### 1. syslog overview(CH:系统日志概览)
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

### 2. syslog API
closelog, openlog, syslog, vsyslog - send messages to the system logger.	----SYSLOG(3)
#### 2.1 openlog()
#### 2.2 syslog()
#### 2.3 closelog()
#### 2.4 vsyslog() [GNU libc]

### 3. /etc/syslog.conf