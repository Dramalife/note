//Source URL : https://blog.csdn.net/daiyudong2020/article/details/51695502


#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

/*
   struct inotify_event {
   int      wd;       // Watch descriptor 
   uint32_t mask;     // Mask of events 
   uint32_t cookie;   // Unique cookie associating related  events (for rename(2))
   uint32_t len;      // Size of name field 
   char     name[];   // Optional null-terminated name 
   };
 */

char path[128];
char cmd[256];

void outp(void)
{
	sprintf(cmd,"lsof %s >> /tmp/1.log",path);
	//sprintf(cmd,"lsof %s | grep bash >> /tmp/1.log",path);
	system(cmd);
	printf("CMD:[%s] \n",cmd);
}

int watch_inotify_events(int fd)
{
	char event_buf[512];
	int ret;
	int event_pos = 0;
	int event_size = 0;
	struct inotify_event *event;

	/*读事件是否发生，没有发生就会阻塞*/
	ret = read(fd, event_buf, sizeof(event_buf));
	outp();

	/*如果read的返回值，小于inotify_event大小出现错误*/
	if(ret < (int)sizeof(struct inotify_event))
	{
		printf("counld not get event!\n");
		return -1;
	}

	/*因为read的返回值存在一个或者多个inotify_event对象，需要一个一个取出来处理*/
	while( ret >= (int)sizeof(struct inotify_event) )
	{
		outp();
		event = (struct inotify_event*)(event_buf + event_pos);
		if(event->len)
		{
			if(event->mask & IN_CREATE)
			{
				printf("create file: %s\n",event->name);
			}
			else
			{
				printf("delete file: %s\n",event->name);
			}
		}

		/*event_size就是一个事件的真正大小*/
		event_size = sizeof(struct inotify_event) + event->len;
		ret -= event_size;
		event_pos += event_size;
	}

	return 0;
}

int main(int argc, char** argv)
{
	int InotifyFd;
	int ret;

	memset(cmd,0,sizeof(cmd));

	if (argc != 2)
	{
		printf("Usage: %s <dir>\n", argv[0]);
		return -1;
	}

	/*inotify初始化*/
	InotifyFd = inotify_init();
	if( InotifyFd == -1)
	{
		printf("inotify_init error!\n");
		return -1;
	}

	/*添加watch对象*/
	ret = inotify_add_watch(InotifyFd, argv[1], IN_CREATE |  IN_DELETE);
	strcpy(path,argv[1]);

	/*处理事件*/
	while(1)
		watch_inotify_events(InotifyFd);

	/*删除inotify的watch对象*/
	if ( inotify_rm_watch(InotifyFd, ret) == -1) 
	{
		printf("notify_rm_watch error!\n");
		return -1;
	}

	/*关闭inotify描述符*/
	close(InotifyFd);

	return 0;
}

