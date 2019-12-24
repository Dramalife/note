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

	/* Block for reading */
	ret = read(fd, event_buf, sizeof(event_buf));
	outp();

	/* Read inotify_event */
	if(ret < (int)sizeof(struct inotify_event))
	{
		printf("counld not get event!\n");
		return -1;
	}

	/* Read inotify_event in a loop */
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

		/* event_size is true size of event */
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

	/* Init inotify */
	InotifyFd = inotify_init();
	if( InotifyFd == -1)
	{
		printf("inotify_init error!\n");
		return -1;
	}

	/* Add watching objects */
	ret = inotify_add_watch(InotifyFd, argv[1], IN_CREATE |  IN_DELETE);
	strcpy(path,argv[1]);

	/* Handle events */
	while(1)
		watch_inotify_events(InotifyFd);

	/* Del watching object */
	if ( inotify_rm_watch(InotifyFd, ret) == -1) 
	{
		printf("notify_rm_watch error!\n");
		return -1;
	}

	/* close fd of inotify */
	close(InotifyFd);

	return 0;
}

