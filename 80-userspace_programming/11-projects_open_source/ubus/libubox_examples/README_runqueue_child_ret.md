runqueue是libubox提供的子进程管理框架，主要接口如下：
|Fun|desc|
|--|--|
|runqueue_init||
|runqueue_task_add||
|runqueue_process_add|把进程（子进程）添加到runqueue|
|runqueue_task_complete|当前进程完成/超时，使能下一个子进程|
runqueue_process_add函数只用到了struct runqueue_process中的struct runqueue_task task，所以在调用runqueue_process_add之前对struct uloop_process proc的cb进行赋值，用来指定wait之后的回调函数是无效的；
解决：重写runqueue_process_add函数，对p->proc.cb进行赋值；
```c
void runqueue_process_add(struct runqueue *q, struct runqueue_process *p, pid_t pid)
{
        if (p->proc.pending)
                return;
		p->proc.pid = pid;
        p->proc.cb = __runqueue_proc_cb;//使用了内置的__runqueue_proc_cb函数，定义在后面列出
        if (!p->task.type)
                p->task.type = &runqueue_proc_type;
        uloop_process_add(&p->proc);
        if (!p->task.running)
                runqueue_task_add(q, &p->task, true);
}                                              
struct runqueue_process {                                         
        struct runqueue_task task;
        struct uloop_process proc;// uloop的进程结构体，声明在如下
};
struct uloop_process                                        
{
        struct list_head list;
        bool pending;
		uloop_process_handler cb; //此进程wait到之后的回调函数
        pid_t pid;
};

static void uloop_handle_processes(void)
{
        struct uloop_process *p, *tmp;
        pid_t pid;
        int ret;

        do_sigchld = false;

        while (1) {
                pid = waitpid(-1, &ret, WNOHANG);
                if (pid < 0 && errno == EINTR)
                        continue;

                if (pid <= 0)
                        return;

                list_for_each_entry_safe(p, tmp, &processes, list) {
                        if (p->pid < pid)
                                continue;

                        if (p->pid > pid)
                                break;

                        uloop_process_delete(p);                                                                    
                        p->cb(p, ret);//这里调用了cb，ret是wait到的子进程的状态
                }   
        }   

}
```
默认使用的回调函数的ret入参没有被使用
```c
static void
__runqueue_proc_cb(struct uloop_process *p, int ret)
{
        struct runqueue_process *t = container_of(p, struct runqueue_process, proc);

        runqueue_task_complete(&t->task);
}
```