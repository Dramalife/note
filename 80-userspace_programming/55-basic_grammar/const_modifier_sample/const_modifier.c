/*
 const ���εı���var����ı��ʺ����ǳ�����ͨ�����ñ������� var
 ���ܹ������޸ģ������� var ������ָ���Ƕ��ڴ����ݲ����޸�
*/
#include<string.h>
#include<stdlib.h>/*malloc*/

/* Ref Url : https://blog.csdn.net/m0_37806112/article/details/81252151 */

/* ����һ��ָ���ַ����ַ���������ָ��(p��ָ������ݲ����޸�) 
   ccp0 is a pointer to const char */
const char *ccp0 = "asdfghjkl"; 

/* ͬ�� 
   ͬ����ΪC++����û��const*�������������constֻ������ǰ������͡�
   C++��׼�涨��const�ؼ��ַ������ͻ������֮ǰ�ȼ۵ġ�*/
char const *ccp1;

/*����һ��ָ���ַ����ַ�����ָ�볣�������������޸�p��ֵ��Ҳ���ǵ�ַ�޷��޸ġ�*/
char * const cpc;

/* Ref end. */

#define DEFAULT_SIZE (100 * sizeof(char))
int main(void)
{
	char *tmp;

	tmp = ccp0;
	//ccp1 = tmp;

	printf("%s \n",ccp0);

	/*
	   char *strcpy(char *dest, const char *src);
	 */
	strcpy(tmp, "1234567");
	printf("%s \n",ccp0);
	tmp[1] = 'Z';/*worked*/
	printf("%s \n",ccp0);

	/*
	   char *strcat(char *dest, const char *src);
	 */
	strcat(ccp0, "88");/* gcc:warning */
	printf("%s \n",ccp0);

	//ccp0[1] = 'c';	/* gcc:error */
	printf("%s \n",ccp0);

	return 0;
}
