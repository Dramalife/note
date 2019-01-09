## [linux下利用backtrace追踪函数调用堆栈以及定位段错误](https://www.cnblogs.com/lidabo/p/5344768.html)
### backtrace()的作用
一般察看函数运行时堆栈的方法是使用GDB（bt命令）之类的外部调试器,但是,有些时候为了分析程序的BUG,(主要针对长时间运行程序的分析),在程序出错时打印出函数的调用堆栈是非常有用的。
### 函数定义
在glibc头文件"execinfo.h"中声明了三个函数用于获取当前线程的函数调用堆栈。
#### backtrace
```
int backtrace(void **buffer,int size) 
```
该函数用于获取当前线程的调用堆栈,获取的信息将会被存放在buffer中,它是一个指针列表。参数 size 用来指定buffer中可以保存多少个void* 元素。函数返回值是实际获取的指针个数,最大不超过size大小

在buffer中的指针实际是从堆栈中获取的返回地址,每一个堆栈框架有一个返回地址

注意:某些编译器的优化选项对获取正确的调用堆栈有干扰,另外内联函数没有堆栈框架;删除框架指针也会导致无法正确解析堆栈内容
#### backtrace_symbols

```
char ** backtrace_symbols (void *const *buffer, int size)  
```
backtrace_symbols将从backtrace函数获取的信息转化为一个字符串数组. 参数buffer应该是从backtrace函数获取的指针数组,size是该数组中的元素个数(backtrace的返回值)   
   
函数返回值是一个指向字符串数组的指针,它的大小同buffer相同.每个字符串包含了一个相对于buffer中对应元素的可打印信息.它包括函数名，函数的偏移地址,和实际的返回地址

现在,只有使用ELF二进制格式的程序才能获取函数名称和偏移地址.在其他系统,只有16进制的返回地址能被获取.另外,你可能需要传递相应的符号给链接器,以能支持函数名功能(比如,在使用GNU ld链接器的系统中,你需要传递(-rdynamic)， -rdynamic可用来通知链接器将所有符号添加到动态符号表中，如果你的链接器支持-rdynamic的话，建议将其加上！)

该函数的返回值是通过malloc函数申请的空间,因此调用者必须使用free函数来释放指针.

注意:如果不能为字符串获取足够的空间函数的返回值将会为NULL
####backtrace_symbols_fd

```
void backtrace_symbols_fd (void *const *buffer, int size, int fd)  
```
backtrace_symbols_fd与backtrace_symbols 函数具有相同的功能,不同的是它不会给调用者返回字符串数组,而是将结果写入文件描述符为fd的文件中,每个函数对应一行.它不需要调用malloc函数,因此适用于有可能调用该函数会失败的情况

### 下面是glibc中的实例（稍有修改）：
```
#include <execinfo.h>  
#include <stdio.h>  
#include <stdlib.h>  
  
/* Obtain a backtrace and print it to @code{stdout}. */  
void print_trace (void)  
{  
    void *array[10];  
    size_t size;  
    char **strings;  
　   size_t i;  
　  
    size = backtrace (array, 10);  
    strings = backtrace_symbols (array, size);  
    if (NULL == strings)  
    {  
　       perror("backtrace_synbols");  
        Exit(EXIT_FAILURE);  
    }  
  
    printf ("Obtained %zd stack frames.\n", size);  
  
    for (i = 0; i < size; i++)  
        printf ("%s\n", strings[i]);  
  
    free (strings);  
　   strings = NULL;  
}  
  
/* A dummy function to make the backtrace more interesting. */  
void dummy_function (void)  
{  
    print_trace ();  
}  
  
int main (int argc, char *argv[])  
{  
    dummy_function ();  
    return 0;  
}  
```
输出：
```
Obtained 4 stack frames.  
./execinfo() [0x80484dd]  
./execinfo() [0x8048549]  
./execinfo() [0x8048556]  
/lib/i386-linux-gnu/libc.so.6(__libc_start_main+0xf3) [0x70a113] 
```
### 定位段错误位置
通常情况系，程序发生段错误时系统会发送SIGSEGV信号给程序，缺省处理是退出函数。我们可以使用 signal(SIGSEGV, &your_function);函数来接管SIGSEGV信号的处理，程序在发生段错误后，自动调用我们准备好的函数，从而在那个函数里来获取当前函数调用栈。

举例如下：
```
#include <stdio.h>  
#include <stdlib.h>  
#include <stddef.h>  
#include <execinfo.h>  
#include <signal.h>  
  
void dump(int signo)  
{  
    void *buffer[30] = {0};  
    size_t size;  
    char **strings = NULL;  
    size_t i = 0;  
  
    size = backtrace(buffer, 30);  
    fprintf(stdout, "Obtained %zd stack frames.nm\n", size);  
    strings = backtrace_symbols(buffer, size);  
    if (strings == NULL)  
    {  
        perror("backtrace_symbols.");  
        exit(EXIT_FAILURE);  
    }  
      
    for (i = 0; i < size; i++)  
    {  
        fprintf(stdout, "%s\n", strings[i]);  
    }  
    free(strings);  
    strings = NULL;  
    exit(0);  
}  
  
void func_c()  
{  
    *((volatile char *)0x0) = 0x9999;  
}  
  
void func_b()  
{  
    func_c();  
}  
  
void func_a()  
{  
    func_b();  
}  
  
int main(int argc, const char *argv[])  
{  
    if (signal(SIGSEGV, dump) == SIG_ERR)  
        perror("can't catch SIGSEGV");  
    func_a();  
    return 0;  
}  
```
编译程序：

gcc -g -rdynamic test.c -o test; ./test

输出如下：
```
Obtained6stackframes.nm  
./backstrace_debug(dump+0x45)[0x80487c9]  
[0x468400]  
./backstrace_debug(func_b+0x8)[0x804888c]  
./backstrace_debug(func_a+0x8)[0x8048896]  
./backstrace_debug(main+0x33)[0x80488cb]  
/lib/i386-linux-gnu/libc.so.6(__libc_start_main+0xf3)[0x129113] 
```
（这里有个疑问： 多次运行的结果是/lib/i368-linux-gnu/libc.so.6和[0x468400]的返回地址是变化的，但不变的是后三位， 不知道为什么）

接着：

objdump -d test > test.s

在test.s中搜索804888c如下：

```
8048884 <func_b>:  
8048884:    55              push %ebp  
8048885:    89 e5            mov %esp, %ebp  
8048887:    e8 eb ff ff ff       call 8048877 <func_c>  
804888c:    5d                pop %ebp  
804888d:    c3                ret 
```

其中80488c时调用（call 8048877）C函数后的地址，虽然并没有直接定位到C函数，通过汇编代码， 基本可以推出是C函数出问题了（pop指令不会导致段错误的）。

我们也可以通过addr2line来查看
```
addr2line 0x804888c -e backstrace_debug -f 
```
输出：
```
func_b  
/home/astrol/c/backstrace_debug.c:57
```
以下是简单的backtrace原理实现：
```
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
  
#define LEN 4  
#define FILENAME "stack"  
  
int backtrace(void **buffer, int size)  
{  
    int i = 0;  
    unsigned long int reg_eip = 0;  
    unsigned long int reg_ebp = 0;  
    char cmd[size][64];  
  
    memset(cmd, 0, size * 64);  
    __asm__ volatile (  
        /* get current EBP */  
        "movl %%ebp, %0 \n\t"  
        :"=r"(reg_ebp)  /* output register */  
        :       /* input  register */  
        :"memory"   /* cloberred register */  
    );    
  
    for (i = 0; i < size; i++)  
    {  
        reg_eip = *(unsigned long int *)(reg_ebp + 4);  
        reg_ebp = *(unsigned long int *)(reg_ebp);  
        buffer[i] = (void *)reg_eip;  
        fprintf(stderr, "%p -> ", buffer[i]);  
        sprintf(cmd[i], "addr2line %p -e ", buffer[i]);  
        strncat(cmd[i], FILENAME" -f", strlen(FILENAME)+3);  
        system(cmd[i]);  
        puts("");         
    }  
  
    return size;  
}  
  
static void test2(void)  
{  
    int i = 0;  
    void *buffer[LEN] = {0};  
    backtrace(buffer, LEN);  
    return;  
}  
  
static void test1(void)  
{  
    test2();  
}  
  
static void test(void)  
{  
    test1();  
}  
  
int main(int argc, const char *argv[])  
{  
    test();  
    return 0;  
}  
```