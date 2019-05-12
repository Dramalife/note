
```c
int netlink_talk( struct nlmsghdr *n, struct nlsock *nl)
{
	//... ...
	struct iovec iov ={};

	/* ch:内存拼接的方式，移植到msghdr结构体不一致的kernel版本下不会报错，但会导致数据错误 
	   en:*/
	struct msghdr msg = {  ,  , &iov , , , , };
	//... ...
}
```
