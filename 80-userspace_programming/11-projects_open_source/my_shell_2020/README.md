2021/03/26,  dramalife@live.com

这是一个简单的shell，基本实现了一个功能完整的shell（比如bash，sh）。

涉及到Linux系统编程的一些接口，主要使用系统调用壳函数，不包括system和popen这类会执行其他shell的接口，可以说此项目是一个功能比较完整的真正的shell。



主要概念：内置命令，内部命令；作业控制；管道，重定向；

主要技术：管道，信号;



最早在2020年4月实现第一版，闭源在gitee的仓库中。

英文版本后续添加。

### 目录说明

|文件（夹）|说明|
|--|--|
|Makefile			|makefile|
|README.md|此文件|
|dl_builtin.c|内置命令的具体策略部分，包括这些命令的具体实现：cd, exit, where, pwd, list, pid, kill, printenv, set等|
|dl_builtin.h||
|dl_port.h|任务管理和作业管理相关结构体；调试宏debug_out的定义（自动显示函数名和行号）；|
|doc|需求文档|
|get_path.c|用于获取环境变量PATH的值|
|get_path.h||
|log|调试过程的log，用于后续深入分析程序出现问题的原因|
|os_shell_a.c|这个shell的主要实现代码，包括这些实现：内置命令（比如cd, jobs, fg,  bg等），内部命令（ls, grep 等），作业控制(job control)，管道(pipes)和重定向(redirection)的实现，这里的实现不会调用system和popen等会间接执行sh的接口；|
|sample_code|一些示例代码|
|sh.h|一部分shell内置命令对应函数实现的声明|
|shell-with-builtin.c|main函数所在文件，调用初始化和主循环函数；|
|showusers.c|watchuser命令的实现：监控用户的登入和登出|
|simple_ls.c|主要是ls命令的实现|
|which.c|主要是which命令的实现|



### 代码说明（后续更新详细 ... ...）

程序入口

```c
/* 初始化函数
* 注册SIGINT和SIGTSTP信号，对应键盘的Ctrl + C 和 Ctrl + z；
* 初始化当前目录，并设置prompt（比如： dramalife@ubuntu-focal:~/note/ ）；
* 初始化history(历史命令)需要的数据；
* 初始化任务数据
*/
dl_sh_init(NULL);

/*
* 从标准输入（stdin）读取一行输入并解析字符串，
* 比如管道（|），重定向（>, <），后台运行(&)等符号，再判断内置、内部命令
*
* wait子进程（由内部命令创建的）；
*/
dl_loop(NULL);
```

内置命令注册说明(部分)

```c
struct dl_cmd_st dlcmd[]=
{
	{.type=BTTYPE_OSSHELL,		.cmd="bg",				.HANDLE_VAR_NAME=handler_bg},

	/// Simple Shell (mysh) Start
	{.type=BTTYPE_SIMPLE,		.cmd="exit",	.HANDLE_VAR_NAME=dlfun_exit},	
    
    // 等等 ... ...
}；
// 执行：解析到命令字符串后，调用对应的函数；

// 两种type（BTTYPE_OSSHELL和BTTYPE_SIMPLE）用来区分内置命令是否有参数；
```

内部命令的执行

```c
int parse_command_line_all(char *buff)
{                                                                                                                                        
        int piped = 0; 
        char *target[2];
        char *args_no_pipe[MAX_ARG_NUM] = {NULL};
        char *args_piped[MAX_ARG_NUM];

		/* 判断是否有 管道 和 重定向 */
        if( 0 == (piped = parse_command_line_strsep(buff, target, DELIM_STRING_PIPE)) )
                if( 0 == (piped = parse_command_line_strsep(buff, target, DELIM_STRING_REDIRECTION_IN)) )
                        piped = parse_command_line_strsep(buff, target, DELIM_STRING_REDIRECTION_OUT);

    	/* 分别处理 管道， 重定向 或者 简单命令的情况 */
        switch(piped)
        {    
                case TYPE_PIPE:
                        parse_command_line_strsep(target[0], args_no_pipe,  DELIM_STRING_SPACE);
                        parse_command_line_strsep(target[1], args_piped,  DELIM_STRING_SPACE);
                        break;
                case TYPE_REDI:
                case TYPE_REDO:
                        parse_command_line_strsep(target[0], args_no_pipe,  DELIM_STRING_SPACE);
                        parse_command_line_strsep(target[1], args_piped,  DELIM_STRING_SPACE);
                        break;
                default:
                        parse_command_line_strsep(buff, args_no_pipe,  DELIM_STRING_SPACE);
                        break;
        }    

    	/* 如果是内置命令，顺便调用对应的函数，
         * 否则进入内部命令的情况 - exec_external_prog
         */
        if( 0 == is_builtin_cmd(args_no_pipe) )
        {    
            	/* 以管道为例，fork之后exec，再dump标准输入输出的fd（0和1） */
                exec_external_prog(piped, args_no_pipe, args_piped);
        }    

        return 0;
}

```

作业管理状态相关

```c
struct signal_status_st sig_sta[]=
{
	{SIGINT,	S_TERM,		"Terminated"},
	{SIGTSTP,	S_STOPPED,	"Stopped"},
	{SIGCONT,	S_RUNNING,	"Running"},
	{0 ,	S_FG,	"Frong-ground"},
	{0 ,	S_BG,	"Back-ground"},
	{0, 0, NULL},
};
```



### 测试命令

```bash
    pwd
    ls &
    ls -l &
    cd /
    sleep 20 &
    ls & 			; run before sleep is done
    pid
    tty
    /bin/ps -lfu USERNAME	; replace USERNAME with your own  
    cd
    cd [project test dir of your choosing]
    pwd
    ls -l
    rm -f mail1 mail2
    touch mail1			; create this file
    watchmail mail1
    echo hi >> mail1
    echo HiThere > mail2	; create another file
    watchmail mail2
    echo there >> mail1
    echo Subject: >> mail2
    cat mail1
    cat mail2
    watchmail mail1 off
    echo bye >> mail1
    echo bye >> mail2		; still watching this one

    rm -f test1 test2 test3 test4 test5 test6 test7 test8
    test-1+2 > test1
    test-1+2 >> test2
    test-1+2 >& test3
    test-1+2 >>& test4
    cat test1 test2 test3 test4
    test-1+2 > test1
    test-1+2 >> test2
    test-1+2 >& test3
    test-1+2 >>& test4
    cat test1 test2 test3 test4

    test-1+2 > test5
    test-1+2 >> test6
    test-1+2 >& test7
    test-1+2 >>& test8
    cat test5 test6 test7 test8
    test-1+2 > test5
    test-1+2 >> test6
    test-1+2 >& test7
    test-1+2 >>& test8
    cat test5 test6 test7 test8

    grep hello < test8
    grep error < test8

    rm -f test9 test10 test11 test12

    test-1+2 > test9
    test-1+2 >> test10
    test-1+2 >& test11
    test-1+2 >>& test12
    cat test9 test10 test11 test12

    ls | fgrep .c                   ; show pipes works
    ./test-1+2 | grep  hello
    ./test-1+2 |& grep hello
    ./test-1+2 | grep output
    ./test-1+2 |& grep output
    ./test-1+2 |& grep error

    pid                                        ; zombie avoidance checking
    /bin/ps -lfu USERNAME | grep defunct       ; replace USERNAME with your username
```

