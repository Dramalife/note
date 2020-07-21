

### 1 SRCs

#### 1.1 server.c

与client建立TCP连接后，接收一次消息，然后关闭连接，如此循环。

```c
listenfd = socket(AF_INET, SOCK_STREAM, 0);
bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
listen(listenfd, 10);
while(1)
{
	connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

	/* 接收client消息后，关闭连接，client再次发送会收到SIGPIPE信号（默认退出进程）； */
	recv(connfd, buff, MAXLINE, 0);
	close(connfd);   
}
close(listenfd);
```

#### 1.2 client.c

与server建立TCP连接后，发送一次消息，然后关闭链接，进程退出。

```c
sockfd = socket(AF_INET, SOCK_STREAM, 0);

/* 连接server，发送消息， 关闭连接 */
connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
send(sockfd, sendline, strlen(sendline), 0);
close(sockfd);
```

#### 1.3 keep_running_client.c

与server建立TCP连接后，循环发送消息；忽略SIGPIPE信号；

如果send、connect或者connect返回-1，关闭fd并goto至调用socket的位置重新建立socket。

```c
#define RESTART(fd,s) \
	do{ \
		if(fd != -1) \
		{ \
			close(fd); \
		} \
		goto start_sock; \
		sleep(s); \
	}while(0)

/* CASE ： server关闭连接后，如果此client再次send，会收到SIGPIPE信号； */
signal(SIGPIPE, SIG_IGN);

start_sock:

if( -1 == (sockfd = socket(AF_INET, SOCK_STREAM, 0)) )
	RESTART(sockfd, 2);

if( -1 == connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) )
	RESTART(sockfd, 2);

while(1)
{
	if( -1 == send(sockfd, sendline, strlen(sendline), 0) )
		RESTART(sockfd, 2);
}
close(sockfd);
```



### 2 Run

#### 2.1 Compilation all (server, client & keep_running_client)

```bash
make clean
make separately-complile-and-link
```

#### 2.2 Exec

##### 2.2.1 server & client

```bash
./build/server.out &
./build/client.out 127.0.0.1 6666 hello
```

##### 2.2.2 server & keep_running_client
```bash
./build/server.out &
./build/keep_running_client.out 127.0.0.1 6666 hi
```

