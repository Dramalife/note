#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>//inet_pton()



#define DELIMMMM	","
#define MAXLEVEL	5


#if 0//OK
char sample_list_tok[4][4][8] = 
{
	{"ipv4", "b4", "c4", "d4"},
	{"ipv6", "b6", "c6", "d6"},
	{"ipvx", "b6", "c6", "d6"},
	{"ipvx", "b6", "c6", "d6"},
};
#endif


#define XXX_MAX_STR_LEN	16
#define XXX_MAX_COL_LEN	6
#define XXX_END_KEY	"END"
char sample_list_tok[5][XXX_MAX_COL_LEN][XXX_MAX_STR_LEN] = 
{
	{"ipv4", "b4", "c4", "d4", "append", XXX_END_KEY},
	{"ipv6", "b6", "c6", "123456789ABCDEF", "append", XXX_END_KEY},
	{"ipvx", "b6", "c6", "d6", "append", XXX_END_KEY},
	{"ipvx", "b6", "c6", "d6", "append", XXX_END_KEY},
	{"ipv6", "subnet", "checksame", "x", "x", XXX_END_KEY},
};

#define L1_PA	0x01
#define L1_ER	0x02
#define L2_PA	0x04
#define L2_ER	0x08
#define L3_PA	0x10
#define L3_ER	0x20
#define L4_PA	0x40
#define L4_ER	0x80

#define HANDLER_NOT_MATCH_QUIT	0x80
#define HANDLER_NOT_MATCH_CNTI	0x40
#define HANDLER_MATCH		0x01
#define HANDLER_NOTMC		0x02

struct date_sample
{
	int ds_check;
	char *ds_buff;
	void *ds_date;
};
struct check_same_subnet
{
	/*const*/ char *cs_src;
	/*const*/ char *cs_des;
};


extern int tok_string( const char *msg, char **list_tok, int (*handler)(const char *, const char *, int, struct date_sample *), struct date_sample *h_data );

int handler_sample(const char *arg_msg, const char *arg_model, int cnt_stage, struct date_sample *arg_date)
{
	int ret = 0;
	struct check_same_subnet *cs8p = arg_date->ds_date;

	switch( cnt_stage )
	{

		case 1:
		case 2:
		case 3:
			ret |= strstr(arg_msg, arg_model)?HANDLER_MATCH:HANDLER_NOTMC;
			break;
		case 4:
			strcpy(cs8p->cs_src, arg_msg);
			printf("*****%s \n",arg_msg);
			break;
		case 5:
			strcpy(cs8p->cs_des, arg_msg);
			printf("*****%s \n",arg_msg);
			break;
		default:
			break;

	}

	if(ret & HANDLER_MATCH)
	{
		((struct date_sample *)arg_date)->ds_check++;
	}
	else
	{
		//ret |= HANDLER_NOT_MATCH_QUIT;
		ret |= HANDLER_NOT_MATCH_CNTI;
	}

	return ret;
}

int date_check_handler(const char *arg_src, const char *arg_des)
{
	printf("[%s,%d] \n",__func__,__LINE__);
	printf("[%s,%d] (%s)! \n",__func__,__LINE__, strstr(arg_src, arg_des)?"same":"diff");
}

int inet6_subnet_check_same(const char *src, const char *des)
{
	struct in_addr *b_src;
	struct in_addr *b_des;

	inet_pton(AF_INET6, src, b_src);
	inet_pton(AF_INET6, des, b_des);

	printf("[%s,%d] (%s)>(%16X),  (%s)>(%16X) \n",__func__,__LINE__,src, b_src->s_addr, des, b_des->s_addr);
}

int main(void)
{

	const char *msg = "ipv6,subnet,checksame,80::1,80::2";
	//const char *msg = "ipv6,subnet,checksame,80::1/64,80::2/64";

#if( XXX_MAX_COL_LEN != (MAXLEVEL + 1) )//abnormal check
	printf("[%s,%d] ERROR ! \n",__func__,__LINE__);
#endif

	//printf("%s \n",sample_list_tok[1][0] );

	//int check = 0;
	struct date_sample date;
	struct check_same_subnet css;
	struct check_same_subnet *csp;
	memset(&date, 0, sizeof(struct date_sample));
	if( NULL == (date.ds_buff = (char *)malloc(strlen(msg) * sizeof(char))) )
	{
		perror("[%s,%d] \n");
	}
	csp = (struct check_same_subnet *)(date.ds_date);
	csp = &css;

	csp->cs_src = (char *)malloc(100 * sizeof(char));
	memset(csp->cs_src, 0, 100);
	csp->cs_des = (char *)malloc(100 * sizeof(char));
	memset(csp->cs_des, 0, 100);

	tok_string(msg, sample_list_tok[4], handler_sample, (void *)&date);
	printf("[%s,%d] type-check-result(%d) \n",__func__,__LINE__,date.ds_check);
	date_check_handler(csp->cs_src, csp->cs_des);
	//inet6_subnet_check_same(csp->cs_src, csp->cs_des);
}


int tok_string( const char *msg, char **list_tok, int (*handler)(const char *, const char *, int, struct date_sample *), struct date_sample *h_data )
{
	int cnt = 0;
	int err = 0;
	int handler_ret = 0;
	char *token= NULL;
	char *mstr_p = (char *)list_tok;

	if( /*************/ 0
			|| NULL == h_data->ds_buff
			|| NULL == msg
	  )
		goto error;

	memset(h_data->ds_buff, 0, strlen(msg));
	strcpy(h_data->ds_buff, msg);
	token= strtok(h_data->ds_buff, DELIMMMM);
	cnt++;

	while( NULL != token)
	{
		if(cnt > MAXLEVEL)
			break;
		if( /*************/(strlen(mstr_p) < XXX_MAX_STR_LEN) 
				&& (strlen(token) < XXX_MAX_STR_LEN) 
				&& (NULL == strstr(mstr_p, XXX_END_KEY))
		  )//abnormal check
		{
			/********/
			printf("[%s] ? [%s] \n"
					,token
					,mstr_p
			      );
			if(handler)
			{
				handler_ret = handler(token, mstr_p, cnt, h_data);
				if(handler_ret & HANDLER_NOT_MATCH_QUIT)
					break;
				printf("[%s,%d] handler_ret(0x%x) \n",__func__,__LINE__,handler_ret);
			}
			/********/

			mstr_p += XXX_MAX_STR_LEN;
		}
		else
		{
			err++;
			printf("[%s,%d] err(%d). \n",__func__,__LINE__,err);
		}

		token= strtok(NULL, DELIMMMM);
		printf("token(%s) \n",token);
		cnt++;
	}

error:
	return 0;
}
