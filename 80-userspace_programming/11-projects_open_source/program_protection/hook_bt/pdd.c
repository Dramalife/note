/*
 * Dramalife@live.com
 * Init : 2020.05.01
 */



#include "dlhook.h"


#define PDD_ANALYSIS_JUST_PRINT	0
#define PDD_RECORDS_SHOW_LEGENCY	0

#define PDD_DEBUG_LEVEL		0xff
#define PDD_DEBUG_FUNC		0X1

struct msg_record
{
	int cnt;
#define REC_MAX_ITEM_NUM	16
#define SIZE_ITEM_MAX		64
	char rec[REC_MAX_ITEM_NUM][SIZE_ITEM_MAX];
};
struct msg_record rec_cur={0};
struct msg_record rec_old={0};
#define REC_MAX_DATA_IMPORT	16
struct msg_record rec_stand[REC_MAX_DATA_IMPORT] = {0};

void ins_item2record(struct msg_record *rec, char *buff)
{
	//printf("%s,%d [%s]\n",__func__,__LINE__,buff);
	strcpy(rec->rec[rec->cnt], buff);
	rec->cnt++;
	if( rec->cnt >= REC_MAX_ITEM_NUM - 1)
		rec->cnt = 0;
}
void copy_records(struct msg_record *des, struct msg_record *src)
{
	memcpy(des, src, sizeof(struct msg_record));
}
void init_records(struct msg_record *rec)
{
	memset(rec, 0, sizeof(struct msg_record));
}
int is_same(struct msg_record *rec1, struct msg_record *rec2)
{
	int index = 0;
	if(rec1->cnt != rec2->cnt)
		return -1;
	for(index = 0; index < rec1->cnt; index++)
	{
		if(strlen(rec1->rec[index]) != strlen(rec2->rec[index]))
			return -2;
		if( 0 != strncmp(rec1->rec[index], rec2->rec[index], strlen(rec1->rec[index]))  )
			return -3;
	}
	return 0;
}
int is_include(struct msg_record *rec1, struct msg_record *rec2)
{
	int index = 0;
	int innnn = 1;
	int cnt_min = (rec1->cnt > rec2->cnt)?rec2->cnt:rec1->cnt;//min
	//printf("cnt=%d, \n",cnt_min);
	for(index = 0; index < cnt_min; index++,innnn++)
	{
		if(strlen(rec1->rec[rec1->cnt - innnn]) != strlen(rec2->rec[rec2->cnt - innnn]))
			return -2;
		//												//////////
		if( 0 != strncmp(rec1->rec[rec1->cnt - innnn], rec2->rec[rec2->cnt - innnn], strlen(rec1->rec[rec1->cnt - innnn]))  )
			return -3;
	}

	return 0;
}
int is_legal(struct msg_record *rec)
{
	int index = 0;
	for(index = 0; index < REC_MAX_DATA_IMPORT; index++)
	{
		if(rec_stand[index].cnt != 0)
		{
			if(0 == is_include(&rec_stand[index], rec))
			{
				return 0;
			}
		}
	}
	return -2;
}
void show_records(struct msg_record *rec)
{
	int index = 0;

	if(NULL == rec)
		return;

#if PDD_RECORDS_SHOW_LEGENCY
	printf("**********%s,%d**********\n",__func__,__LINE__);
	for(index = 0; index < rec->cnt; index++)
	{
		printf("[%3d] (%s)\n", index, rec->rec[index]);
	}
#elif 1
	printf("[%s,%d] : ",__func__,__LINE__);
	for(index = 0; index < rec->cnt; index++)
	{
		printf("(%s)%s",rec->rec[index],(index == rec->cnt-1)?"":"<=");
	}
	printf("\n");
#endif
}


/*
 * Analysis function execution flow
 * ARG - rec : The record to be analyzed
 */
void do_ayalysis(struct msg_record *rec)
{
	if( 0 == is_legal(rec) )
	{
	printf("legal\n");
	}
	else
	{
	printf("illegal\n");
	}
	return show_records(rec);
}

/*
 * Parsing records
 * ARG - old : Previous complete function stack record
 * ARG - cur : The latest complete record of the function stack
 */
int comp_records(struct msg_record *old, struct msg_record *cur)
{
	int ret = 0;
#define STAGE_INIT	0
#define STAGE_DES	0x8
#define STAGE_SAME_DES	0x4
	static int stage = STAGE_INIT | STAGE_SAME_DES;
	//printf("cnt(old=%d,cur=%d),rec-top(old:%s,cur:%s)\n",old->cnt, cur->cnt,old->rec[old->cnt-1],cur->rec[cur->cnt-1]);
	//printf("cnt(old=%d,cur=%d),rec-but(old:%s,cur:%s)\n",old->cnt, cur->cnt,old->rec[0],cur->rec[0]);
	if( old->cnt == 0/*1st data*/)
	{
		copy_records(old, cur);
		init_records(cur);
	}
	else if(old->cnt < cur->cnt)
	{
		if(0 == is_include(old, cur))//current not finished
		{
			copy_records(old, cur);
			init_records(cur);
			stage |= STAGE_SAME_DES;
		}
		else//new record
		{
			if(stage & STAGE_DES)
			{
				copy_records(old, cur);
				init_records(cur);
				stage &= ~STAGE_DES;
			}
			else
			{
				do_ayalysis(old);// fix
				copy_records(old, cur);
				init_records(cur);
			}
		}
	}
	else if( old->cnt == cur->cnt /*repeated OR different*/)
	{
		if(0 == is_same(old, cur))//same
		{
			copy_records(old, cur);
			init_records(cur);
			// TODO : main -> main -> ... ??
		}
		else//different
		{
			if(stage & STAGE_DES)
			{
				copy_records(old, cur);
				init_records(cur);
				stage &= ~STAGE_DES;
			}
			else
			{
				do_ayalysis(old);
				copy_records(old, cur);
				init_records(cur);
			}
		}
	}
	else/*old>cur TODO*/
	{
		if(0 == is_include(old, cur))
		{
			//printf("SAME-DES(0x%02x)\n",stage);
			if(stage & STAGE_SAME_DES)
			{
				stage &= ~STAGE_SAME_DES;
				do_ayalysis(old);
				copy_records(old, cur);
				init_records(cur);
			}
			else
			{
				copy_records(old, cur);
				init_records(cur);
				stage |= STAGE_DES;
			}
		}
		else
		{
			do_ayalysis(old);
			copy_records(old, cur);
			init_records(cur);
		}
		//init_records(old);
		//copy_records(old, cur);
	}

	return ret;
}
void proc_recode(char *buff)
{
	//printf("buff[%s]\n", buff);
	if(NULL != strstr(buff, MSG_START_STR))
	{
		init_records(&rec_cur);
	}
	else if(NULL != strstr(buff, MSG_END_STR))
	{
		comp_records(&rec_old, &rec_cur);
		//show_records( &rec_cur);
	}
	else
	{
		ins_item2record(&rec_cur, buff);
	}
}

void show_help(char *prog_name)
{
		printf(
				"Usage:\n"
				"%s [datafile]\n"
				,prog_name
		      );
}
void show_standard(void)
{
	int index_rec = 0;
	printf("###Legal process###\n");
	for(index_rec = 0; rec_stand[index_rec].cnt != 0; index_rec++)
	{
		show_records(&rec_stand[index_rec]);
	}
	printf("###################\n\n\n");
}
void import_file2struct(char* data_file_name)
{
	FILE *fp_in = NULL;
	fp_in = fopen(data_file_name, "r");// ReadOnly

	if(NULL == fp_in)
	{
		printf("Open file (%s) failed! reason(%s).\n", data_file_name, strerror(errno));
	}

	rewind(fp_in);

	int index_rec = 0;//record
	/* init global data */
	for(index_rec = 0; index_rec < REC_MAX_DATA_IMPORT; index_rec++)
	{
		memset(&rec_stand[index_rec], 0, sizeof(struct msg_record));
	}
	char buff[64];
	memset(buff, 0, sizeof(buff));
	for(index_rec = 0; EOF != fscanf(fp_in,"%s", buff); )
	{
		if(NULL != strstr(buff, DFILE_END_LINE))
		{
			index_rec++;
		}
		else
		{
			//printf("%s \n",buff);
			ins_item2record(&rec_stand[index_rec], buff);
		}
		memset(buff, 0, sizeof(buff));
	}
	fclose(fp_in);
}
int check_file_status(char *data_file_name)
{
	if(!data_file_name)
	{
		printf("Get name of data file failed! exit...\n");
		exit(3);
	}
	if( 0 != access(data_file_name, F_OK) )
	{
		printf("Data file (%s) does not exist! \n", data_file_name);
		exit(3);
	}
	return 0;
}
int import_data_file(int argc, char **argv)
{
	char *data_file_name = NULL;

	/* Check the number of parameters */
	if(argc != 1 && argc != 2)
	{
		show_help(argv[0]);
		exit(2);
	}

	/* get file name */
	switch(argc)
	{
		case 2:/* Data file specified */
			data_file_name = argv[1];
			break;
		case 1:/* Use default data file */
			data_file_name = "default.df";
			break;
		default:
			printf("Unknown type! exit..\n");
			exit(4);
			break;
	}

	/* exist check */
	check_file_status(data_file_name);

	/* Import data from file to memory */
	import_file2struct(data_file_name);

	/* Show Legal process */
	show_standard();

	return 0;
}

int main(int argc, char **argv)
{
	socklen_t addr_len;
	int com_fd;
	int ret;

	struct sockaddr_un clt_addr;
	struct sockaddr_un srv_addr;

	/* Import legal process list */
	import_data_file(argc, argv);

	/* Socket */
	com_fd=socket(PF_UNIX,SOCK_DGRAM,0);
	if(com_fd<0){
		perror("cannot create listening socket");
		return 1;
	}

	srv_addr.sun_family=AF_UNIX;
	strcpy(srv_addr.sun_path,UNIX_DOMAIN);
	unlink(UNIX_DOMAIN);

	ret=bind(com_fd,(struct sockaddr*)&srv_addr,sizeof(srv_addr.sun_family)+strlen(srv_addr.sun_path));
	if(ret==-1){
		perror("cannot bind server socket");
		close(com_fd);
		unlink(UNIX_DOMAIN);
		return 1;
	}
	printf("socket:(%s) \n", UNIX_DOMAIN);

	int num;
	char *buff = (char *)malloc(MSG_SIZE*sizeof(char));
	if(buff)
	{
		struct message_pdd *msg_ptr = (struct message_pdd *)buff;
		/* Main Loop */
		while(1)
		{
			memset(buff, 0, MSG_SIZE);
			if( (num=recvfrom(com_fd, buff, MSG_SIZE,0,(struct sockaddr*)&clt_addr,&addr_len)) )
			{
			}
			msg_ptr->data = buff + MSG_SIZE - MSG_DATA_SIZE;
#if PDD_ANALYSIS_JUST_PRINT/*just show*/
			printf("Client(%d),size(%d),buff(%s)\n",msg_ptr->pid, num, msg_ptr->data);	
#else
			proc_recode(msg_ptr->data);
#endif
		}

		free(buff);
	}
	close(com_fd);

	unlink(UNIX_DOMAIN);
	return 0;
}
