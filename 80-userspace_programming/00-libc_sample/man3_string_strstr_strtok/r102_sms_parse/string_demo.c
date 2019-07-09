/*
 Demo for content & area code of Spain.
*/
#include <stdio.h>
#include <string.h>

#define CNONE   "\e[0m"
#define CLGREEN "\e[1;32m"
#define CLRED   "\e[1;31m"
#define RED                  "\e[0;31m"
#define GREEN                "\e[0;32m"
#define BROWN                "\e[0;33m"
#define YELLOW               "\e[1;33m"

#define MAX_READ_LEN 1024
struct receive_message_info
{
	char message_cont[160];
	char phone_num[16];
};
struct receive_message_info message_info;

char global_string_phone_nums[64];

int parse_content(char *read_buf, int fd, struct receive_message_info *message_info)
{
	char *tmp;
	char *tmp2;
	char at_cmd[64];
	if(fd == 8)
	{
		printf(CLRED"######## bufstart %d#########"CNONE"\r\n%s\r\n####### bufend ########\r\n", strlen(read_buf),read_buf);
	}
	if((tmp = strstr(read_buf, "CMGR:")) && (strlen(read_buf)<=100))
	{	
		printf("cdma read a sms and begin to parse it\r\n");
		if(0)//usb_netcard.operators==CHINA_TELECOM)
		{
			strncpy(message_info->phone_num, tmp+5, 11);
			if((tmp = strstr(read_buf,"0\r\n")) && (tmp2 = strstr(read_buf,"OK")))
			{
				strncpy(message_info->message_cont, tmp+3, tmp2-tmp-5);
				sprintf(at_cmd, "AT+CMGD=,4");
				//send_at_cmd(fd,at_cmd); //delete all message
			}
			else
			{
				return 11;
			}
		}
		else
		{
			if(tmp = strstr(read_buf,"REC UNREAD"))
			{
#if 0
#else
				if( (tmp = strstr(read_buf, "\"+")) && (tmp2 = strstr(tmp, "\",")) )//TODO : need zone num?
				{    
					tmp +=1;
					strncpy(message_info->phone_num, tmp, strlen(tmp) - strlen(tmp2));/* with area code*/
					printf(CLRED"**num:%s**\n"CNONE, message_info->phone_num);
					if((tmp = strstr(tmp, "+")) && (tmp2 = strstr(read_buf, "OK")))
					{
						strncpy(message_info->message_cont, tmp+3, tmp2-tmp-5);
					}
				}    
				else
				{
					printf("++%dreturn 11\r\n",__LINE__);
					return 11;
				}

#endif
			}
			//send_at_cmd(fd,"AT+CMGD=,4"); //delete all message
		}
		printf("++%d,,num_len:%d,cont_len%d \r\n",__LINE__, strlen(message_info->phone_num), strlen(message_info->message_cont));
		printf("[%s] phone number is %s content is %s\n", __func__, message_info->phone_num, message_info->message_cont);
		return 0;
	}
	else if((tmp = strstr(read_buf, "CMGR:")) && (strlen(read_buf)>100))
	{
		//send_at_cmd(fd,"AT+CMGD=,4"); //delete all message
		return 11;
	}
	else
	{
		return 11;
	}
}


#define ADMID_NUM_TOK   "," 
#define ADMIN_NUM_T	1
#define ADMIN_NUM_F	0
int is_admin_phone(char *phone_num)
{
	char *tmp[5];
	int index;
	if( ( strlen(global_string_phone_nums) < 5 ) || ( strlen(phone_num) < 5 ) )
		return ADMIN_NUM_F;
	for(index = 0; index < 5;  index++)
	{    
		if( 0 == index )
		{    
			tmp[index] = strtok(global_string_phone_nums, ADMID_NUM_TOK);
		}    
		else 
		{    
			tmp[index] = strtok(NULL, ADMID_NUM_TOK);
		}    
		if(NULL == tmp[index])
		{    
			return ADMIN_NUM_F;
		}    
		else
		{
			if(strstr(phone_num, tmp[index]))
			{
				return ADMIN_NUM_T;
			}

		}
	}    
}



int main(void)
{
	char test_spain[]="*\n+CMGR: \"REC UNREAD\",\"+34667198888\",,\"19/03/19,10:49:20+04\"*\n22*\n*\r\nOK*\n\0";
	char test_china[]="*\n+CMGR: \"REC UNREAD\",\"+8615733338859\",,\"19/03/19,10:49:20+32\"*\n1*\n*\r\nOK*\n\0";
	char test_china222[]="*\n+CMGR: \"REC UNREAD\",\"+8615733338859\",,\"19/03/19,10:49:20+32\"*\nREBOOT*\n*\r\nOK*\n\0";
	char read_buff[1024];

	char str1[]="+86bbbbbccccc";//CFG
	char str2[]="6";
	if ( strstr(str1,str2))
	{
		printf("111\n");
	}
	else
	{
		printf("00\n");
	}

//strcpy(global_string_phone_nums, "+8615788889999,+8615711112222");
strcpy(global_string_phone_nums, "+8615777778888");
printf("#####%d,%d,%d,\n", is_admin_phone("+8615788889999") ,is_admin_phone("+8615777778888"), is_admin_phone("+8615766667777")   );
//printf("#####%d,,\n", is_admin_phone("15788889999"));
sleep(2);

	while(1)
	{
		memset(read_buff,0,sizeof(read_buff));
		memset(&message_info,0,sizeof(message_info));
		strcpy(read_buff,test_spain);
		parse_content(read_buff, 8, &message_info);
		sleep(2);

		memset(read_buff,0,sizeof(read_buff));
		memset(&message_info,0,sizeof(message_info));
		strcpy(read_buff,test_china);
		parse_content(read_buff, 8, &message_info);
		sleep(2);
	}

	return 0;
}

