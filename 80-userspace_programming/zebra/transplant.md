
```c
int netlink_talk( struct nlmsghdr *n, struct nlsock *nl)
{
	//... ...
	struct iovec iov ={};

	/* ch:�ڴ�ƴ�ӵķ�ʽ����ֲ��msghdr�ṹ�岻һ�µ�kernel�汾�²��ᱨ�����ᵼ�����ݴ��� 
	   en:*/
	struct msghdr msg = {  ,  , &iov , , , , };
	//... ...
}
```
