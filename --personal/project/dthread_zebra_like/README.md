> \# note "dthread-mcu" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : DATE:2019.03.23(RECALL);  
\# Update   
\#  
  


### 1 Introduction
Date：2018.8  
Provide fake thread like Zebra on no-os devices,and interface used to add task.  
The "dthread" means fake thread,it\`s name come form but opposite to"pthread". 'p' rotate 180 degrees becomes 'd'.  
Need "uptime" of system it\`s running on.    
Source code may be pushed after a few month,because it need to be optimised (Game Of Thrones again ; )

#### 1.1 Programming Interfaces
```c
int dthread_add(u8_t id, int period, u8_t (*_fun_ptr)(u8_t,u8_t));/* add user`s task to dthread */
int dthread_call(u8_t id, u8_t arg1, u8_t arg2);/* add this in main_loop */
```

#### 1.2 Application : GSM / NB-IOT Module init
##### 1.2.1 Add AT commands and it`s handle func to user struct
```c
int gprs_cmd_add(u8_t flag, struct gprs_cmd st, int delay, char *buff2send, char *ok_string, char *err_string, int timeout);
```
sample : gprs_cmd_add((W_NET_TRY_ONLY | W_NET_ERR_ONLY | W_NET_NEXT_EN),pdt28,0,"AT+CSQ","OK","ERROR",300);
1. arg0 flag  
  enable sending AT command .  
  enable analysis of ERR response(rsp).   
  enable auto run of next AT command.  
  enable running this AT command immediately.  
2. arg1 gprs_cmd  st
  dev_id : to support multi-dev.  
  enable : switch of sending.  
  init : currnet init status (bit).  
  char at[] : string being sent to module.  
  char rsp[] : correct response of module.   
  char err[] : error response of module.  
  u8_t ready : flag weather current AT command is done correctly.  
  u8_t ing : flag weather it\`s running.  
3. arg2 delay  
    Running task after devices up "delay" seconds.
4. arg3 buff2send  
    Buff sent to GSM / NB-IOT Module.
5. arg4 ok_string  
    The correct response of the module.
6. arg5 err_string  
    The incorrect response of the module.
7. arg6 timeout  
    Max retry time of the AT command.


##### 1.2.2 Add user`s task to dthread
```c
void gprs_loop(u8_t max_steps, ,,void *uart);/* add this task by calling dthread_add */
```
