/*
 * note "NULL" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
 * Copyright (C) 2017 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * ;
 * 
 * $ uname -a
 * Linux iZ2zeeq1jai7e6qn7xqrnuZ 4.15.0-96-generic #97-Ubuntu SMP Wed Apr 1 03:25:46 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Fri Jan 22 17:26:11 CST 2021
 *  * ;
 * Update : Fri Jan 22 17:26:11 CST 2021
 *  
 * Update
 *
 */



/*
 * SOURCE URL : https://blog.csdn.net/y15713080686/article/details/107520296
 */
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

#include <string.h>

#define DL_HTTP_GET_NEXT_LEN(range)	( ( (range.file_size - 1)/*to index*/ - range.r_end)>range.len_buff) \
	?range.len_buff \
	:( (range.file_size - 1)/*to index*/ - range.r_end)

#define DL_SIZE_MIN(x,y)        ((x)>(y)?(y):(x))

#define DL_INDEX2SIZE(x)	((x)+1)
#define DL_SIZE2INDEX(x)	((x)-1)


/* Header of HTTP response */
struct stdl_http_header
{
	uint32_t content_length;
	int status;
};

/* Download file using http range */
struct stdl_http_get_by_range
{
	/****
	 * Remote 
	 */
	char *domain;
	char *path;

	/* update by dl_http_get_file_length() */
	uint32_t file_size;



	/****
	 * File Download Range (temp data) (index data)
	 *
	 * update in user logic,
	 * used by dl_http_get_file_by_range() 
	 */
	uint32_t r_start;
	uint32_t r_end;



	/****
	 * Buff & Length
	 *
	 * storage data downloaded via http
	 */
	char *buff;
	uint32_t len_buff;
};


int ReadHttpStatus(int sock)
{
	char c;
	char buff[1024]="",*ptr=buff+1;
	int bytes_received, status;

	printf("Begin Response ..\n");
	bytes_received = recv(sock, ptr, 1, 0);
	while(bytes_received)
	{
		if(bytes_received==-1)
		{
			perror("ReadHttpStatus");
			exit(1);
		}

		if((ptr[-1]=='\r') && (*ptr=='\n' )) break;
		ptr++;
		bytes_received = recv(sock, ptr, 1, 0);
	}
	*ptr=0;
	ptr=buff+1;

	sscanf(ptr,"%*s %d ", &status);

	printf("%s\n",ptr);
	printf("status=%d\n",status);
	printf("End Response ..\n");
	return (bytes_received>0)?status:0;

}

//the only filed that it parsed is 'Content-Length' 
int ParseHeader(int sock, 
		struct stdl_http_header *apheader
	       )
{
	char c;
	char buff[2048]="",*ptr=buff+4;
	int adebug = 0;
	int bytes_received;

	int *p_content_length = NULL;
	int *p_status = NULL;
	int content_length = 0;
	int status = 0;
	if( apheader ){
		p_content_length = &apheader->content_length;
		p_status = &apheader->status;
	}
	else{
		p_content_length 	= &content_length;
		p_status 		= &status 	;
	}

	*p_status = ReadHttpStatus(sock);

	bytes_received = recv(sock, ptr, 1, 0);

	if( adebug ){
		printf("Begin HEADER ..\n");
	}

	while(bytes_received)
	{
		if(bytes_received==-1)
		{
			perror("Parse Header");
			exit(1);
		}

		if(
				(ptr[-3]=='\r')  && (ptr[-2]=='\n' ) &&
				(ptr[-1]=='\r')  && (*ptr=='\n' )
		  ) break;
		ptr++;
		bytes_received = recv(sock, ptr, 1, 0);
	}

	//printf("@@@@ %s @@@@\n", buff+4);

	*ptr=0;
	ptr=buff+4;
	//printf("%s",ptr);

	if(bytes_received)
	{
		/* Content-Length */ 
		ptr=strstr(ptr,"Content-Length:");
		if(ptr){
			sscanf(ptr,"%*s %d", p_content_length);
		}
		else{
			*p_content_length = -1; //unknown size
		}

		if( adebug ){
			printf("status: %d\n", 		*p_status);
			printf("Content-Length: %d\n",	*p_content_length);
		}
	}
	if( adebug ){
		printf("End HEADER ..\n");
	}
	return  bytes_received ;

}
int dl_http_get_file_length(char *domain, char *path)
{
	char send_data[256] = {0};
	int sock;
	int ret_len = 0;
	struct hostent *he;
	struct sockaddr_in server_addr;


	he = gethostbyname(domain);
	if (he == NULL)
	{
		herror("gethostbyname");
		exit(1);
	}

	if ((sock = socket(AF_INET, SOCK_STREAM, 0))== -1)
	{
		perror("Socket");
		exit(1);
	}
	server_addr.sin_family = AF_INET;     
	server_addr.sin_port = htons(80);
	server_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(server_addr.sin_zero),8); 

	//printf("Connecting ...\n");
	if (connect(sock, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1)
	{
		perror("Connect");
		exit(1); 
	}

	snprintf(send_data, sizeof(send_data), "HEAD /%s HTTP/1.1\r\nHost: %s\r\n\r\n", path, domain);

	if(send(sock, send_data, strlen(send_data), 0)==-1){
		printf("Send error!\n");
	}
	//printf("send data:[%s]\n", send_data);

	struct stdl_http_header header = {0};
	ret_len = ParseHeader(sock, &header);

	close(sock);
	return header.content_length;
}
int dl_http_get_file_by_range( struct stdl_http_get_by_range *aprange )
{
	int sock, bytes_received;  
	char send_data[1024],/*recv_data[1024],*/ *p;
	struct sockaddr_in server_addr;
	struct hostent *he;

	struct stdl_http_header header = {0};

	/* Param */
	char *domain = aprange->domain;
	char *path = aprange->path;
	int astart = aprange->r_start;
	int aend = aprange->r_end;
	char *buff = aprange->buff;
	int len_buff = aprange->len_buff;


	if( len_buff < DL_INDEX2SIZE((aend - astart)) ){
		printf("buff too small!\n");
		return -1;
	}

	if( 
			astart >= aprange->file_size
			|| aend >= aprange->file_size
	  ){
		printf("Over range! (%d,%d)(%d)\n", astart, aend, aprange->file_size);
		return 1;
	}
	else{
		printf("Get range! (%d,%d)(%d)\n", astart, aend, aprange->file_size);
	}

	he = gethostbyname(domain);

	if (he == NULL)
	{
		herror("gethostbyname");
		exit(1);
	}

	if ((sock = socket(AF_INET, SOCK_STREAM, 0))== -1)
	{
		perror("Socket");
		exit(1);
	}
	server_addr.sin_family = AF_INET;     
	server_addr.sin_port = htons(80);
	server_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(server_addr.sin_zero),8); 

	printf("Connecting ...\n");
	if (connect(sock, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1)
	{
		perror("Connect");
		exit(1); 
	}

	printf("Sending data ...\n");

	snprintf(send_data, sizeof(send_data), "GET /%s HTTP/1.1\r\nHost: %s\r\nRange: bytes=%d-%d\r\n""\r\n", path, domain, astart, aend);

	//printf("#####\n\n%s\n\n####\n", send_data);

	if(send(sock, send_data, strlen(send_data), 0)==-1)
	{
		perror("send");
		exit(2); 
	}
	printf("Data sent.\n");  

	//fp=fopen("received_file","wb");
	//printf("Recieving data...\n\n");

	uint32_t offset = 0;
	uint32_t contentlengh;

	memset(buff, 0, len_buff);

	if(
			//	ReadHttpStatus(sock) && 
			(contentlengh=ParseHeader(sock, &header)))
	{
		printf("Saving data...\n\n");


		while(
				( bytes_received = recv(sock, buff + offset, len_buff - offset, 0) )
		     )
		{
			if(bytes_received==-1)
			{
				perror("recieve");
				exit(3);
			}
			printf("%d,%d\n", offset, bytes_received);
			offset += bytes_received;

			if( offset >= len_buff ){
				break;
			}

			if( offset >= contentlengh ){
				break;
			}
		}
	}
	close(sock);

	printf("READ LEN = %d\n", offset);

	if( header.status != 206 ){
		return -1;
	}

	return bytes_received;
}


int main(void)
{
	/* Sample File */
	char domain[] = "pic.netbian.com", path[]="uploads/allimg/190824/212516-15666531161ade.jpg";
	//char domain[] = "daily.foxitreader.cn", path[]="one18/u88.png";


	/* Get File Length */
	int file_len = dl_http_get_file_length(domain, path);
	printf("File len is %d\n", file_len);


	char buff_read[102400];
	struct stdl_http_get_by_range range = {domain, path, file_len,
		0, 0,
		buff_read, sizeof(buff_read)
	};



	int next_read_len = 0;
	FILE* fd=fopen("212516-15666531161ade.jpg","wb");

	range.r_start = 0;
	range.r_end = range.r_start + /* bytes each time */
		DL_SIZE2INDEX( DL_SIZE_MIN( range.len_buff, range.file_size ) );

	next_read_len = 
		DL_SIZE_MIN( range.len_buff, range.file_size );


	while( next_read_len ){

		dl_http_get_file_by_range(&range) ;

		fwrite(range.buff, 1, next_read_len, fd);

		next_read_len = DL_HTTP_GET_NEXT_LEN(range);


		range.r_start	+= next_read_len;
		range.r_end	+= next_read_len;
	}


	fclose(fd);


	printf("\n\nDone.\n\n");
	return 0;
}

