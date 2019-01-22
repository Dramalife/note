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
