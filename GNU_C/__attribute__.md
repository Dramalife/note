#### referenced Dramalife
|no|path|Remarks|
|0|/README.md||
|1|/note/CMD-CLI.md||

### 概述

```
GNU C的一大特色（却不被初学者所知）就是__attribute__机制。
__attribute__可以设置函数属性（Function Attribute）、变量属性（Variable Attribute）和类型属性（Type Attribute）。
大致有六个参数值可以被设定，即：aligned, packed, transparent_union, unused, deprecated 和 may_alias 。
```
[主要参考url](https://blog.csdn.net/tang_jin_chan/article/details/9079373)

### unused
- This attribute, attached to a function, means that the function is meant to be possibly unused. GCC will not produce a warning for this function.

### section
使用格式为：
```
__attribute__((section("section_name")))
```
其作用是将作用的函数或数据放入指定名为"section_name"输入段。
这里还要注意一下两个概念：输入段和输出段
输入段和输出段是相对于要生成最终的elf或binary时的Link过程说的，Link过程的输入大都是由源代码编绎生成的目标文件.o，那么这些.o文件中包含的段相对link过程来说就是输入段，而Link的输出一般是可执行文件elf或库等，这些输出文件中也包含有段，这些输出文件中的段就叫做输出段。输入段和输出段本来没有什么必然的联系，是互相独立，只是在Link过程中，Link程序会根据一定的规则（这些规则其实来源于Link Script），将不同的输入段重新组合到不同的输出段中，即使是段的名字，输入段和输出段可以完全不同。

#### 示例-section
类比u-boot CMD的安装：存放在section里面然后对这个section进行遍历
car.h
```
\#ifndef _CAR_H_
\#define _CAR_H_

typedef struct __car
{
  const char *name;
  const char *owner;
  int (*price)(void);
}car,*pcar;

#ifndef MKSTR
#define MKSTR(x)    #x
#endif

#define CAR_SECTION __attribute__((used,section("car")))
\#define CAR(__name,__owner,__price) \
    static car car##__name CAR_SECTION = {  \
        .name = MKSTR(__name),\
        .owner = MKSTR(__owner),\
        .price = __price,\
        }

\#endif
```
car.c
main,获取输入
```
/*To Show How To Use GNU_C __attribute__(section("xx"))
 *Modify By SE7EN @2013-6-11
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#include "car.h"

extern car __start_car,__stop_car;

static const char *const short_option = "hqo:";
static const struct option long_option[] =
{
    {"help",0,NULL,'h'},
    {"quit",0,NULL,'q'},
    {"owner",1,NULL,'o'},
    {0,0,0,0}
};

static void print_usage(FILE *stream,char *app_name,int exit_code)
{
    fprintf(stream,"Usage:\n");
    fprintf(stream,
        "-h --help Display This APP Usage Information As Follow:\n"
        "-q --quit Quit This APP.\n"
        "-o --owner Select Whose Car.For Example -o your/my/his/other.\n"
    );

    exit(exit_code);
}

int main(int argc,char **argv)
{
    int ret = -1;
    char *car_owner = NULL;
    pcar ptmp = NULL;

    while((ret = getopt_long(argc,argv,short_option,long_option,NULL)) != -1)
    {
        switch(ret)
        {
            case 'h':
                    print_usage(stdout,argv[0],EXIT_SUCCESS);
                break;

            case 'o':
                    car_owner = optarg;
                break;

            case 'q':
                exit(1);
                break;
            default:
                abort();
        }
    }

    for(ptmp = &__start_car; ptmp != &__stop_car; ptmp++)
    {
        if(!(strcmp(ptmp->owner,car_owner)))
            {
                printf("This Is %s-Car\n",ptmp->owner);
                printf("This Car Named %s.\n",ptmp->name);
                printf("The Price Of This Car Is %d.\n",ptmp->price());
            }
    }

    return 0;
}
```
owner.c
安装CMD
```
#include "car.h"

int his_car_price(void)
{
    return 5000000;
}

int your_car_price(void)
{
    return 6000000;
}

int other_car_price(void)
{
    return 7000000;
}

int my_car_price(void)
{
    return 100;
}

CAR(BMW,his,his_car_price);
CAR(Audi,your,your_car_price);
CAR(Benz,other,other_car_price);
CAR(Bike,my,my_car_price);
```
Makefile
语法看起来比较高级:-)
```
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
CC=gcc
#INCLUDE=-I/xxx
#LIBS=-L/xxx
CCFLAGS= -g -Wall -O2

car:$(OBJS)
    $(CC) $^ -o $@ #$(INCLUDE) $(LIBS)

%.o:%.c
    $(CC) -c $< $(CCFLAGS)

clean:
    rm -f *.o car

.PHONY:
    clean
```
编译测试
```
root@seven-laptop:~/learn/gnu_c# make clean
rm -f *.o car
root@seven-laptop:~/learn/gnu_c# make
gcc -c car.c -g -Wall -O2
gcc -c owner.c -g -Wall -O2
gcc car.o owner.o -o car #
root@seven-laptop:~/learn/gnu_c# chmod +x car
root@seven-laptop:~/learn/gnu_c# ./car -h
Usage:
-h --help Display This APP Usage Information As Follow:
-q --quit Quit This APP.
-o --owner Select Whose Car.For Example -o your/my/his/other.
root@seven-laptop:~/learn/gnu_c# ./car -o your
This Is your-Car
This Car Named Audi.
The Price Of This Car Is 6000000.
root@seven-laptop:~/learn/gnu_c# ./car -o his
This Is his-Car
This Car Named BMW.
The Price Of This Car Is 5000000.
root@seven-laptop:~/learn/gnu_c# ./car -o other
This Is other-Car
This Car Named Benz.
The Price Of This Car Is 7000000.
root@seven-laptop:~/learn/gnu_c# ./car -o my
This Is my-Car
This Car Named Bike.
The Price Of This Car Is 100.
root@seven-laptop:~/learn/gnu_c#
```
