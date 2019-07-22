/*
 const 修饰的变量var不变的本质含义是程序中通过引用变量符号 var
 不能够进行修改，而不是 var 变量所指向那段内存数据不能修改
*/
#include<string.h>
#include<stdlib.h>/*malloc*/
#include<signal.h>

/* Ref Url : https://blog.csdn.net/m0_37806112/article/details/81252151 */

/* 声明一个指向字符或字符串常量的指针(p所指向的内容不可修改) 
   ccp0 is a pointer to const char */
const char *ccp0 = "asdfghjkl"; 

/* 同上 
   同上因为C++里面没有const*的运算符，所以const只能属于前面的类型。
   C++标准规定，const关键字放在类型或变量名之前等价的。*/
char const *ccp1;

/*声明一个指向字符或字符串的指针常量，即不可以修改p的值，也就是地址无法修改。*/
char * const cpc;

/* Ref end. */


extern void signal_handler(int signo);
extern void dump(void);
extern int vdso_get(int argc, char **argv);

#define DEFAULT_SIZE (100 * sizeof(char))
#define VDSO_FILE_NAME "/tmp/vdso.txt"

int main(void)
{
	char *tmp;

	signal(SIGSEGV, signal_handler);

	char *argv[3]={"program",VDSO_FILE_NAME,"vdso"};
	vdso_get(3,&argv);
	system("objdump -d /tmp/vdso.txt > vdso.ass");

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

