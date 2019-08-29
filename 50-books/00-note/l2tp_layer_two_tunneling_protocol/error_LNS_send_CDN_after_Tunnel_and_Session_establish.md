> \# note "xl2tpd" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Init : 2019.08.28;  
\# Update   
\#  
  

#### 1. ERROR LOG

##### 1.1 Regulation

Connection established > Call established > call_close > Connection closed   


##### 1.2 LOG

```bash
handle_avps:  no handler for attribute 5 (Tie Breaker).
xl2tpd[4488]: Connection established to 192.168.1.24, 1701.  Local: 50888, Remote: 27906 (ref=0/0).  LNS session is 'default'
xl2tpd[4488]: write_packet: tty is not open yet.
xl2tpd[4488]: start_pppd: I'm running: 
xl2tpd[4488]: "/usr/sbin/pppd" 
xl2tpd[4488]: "plugin" 
xl2tpd[4488]: "pppol2tp.so" 
xl2tpd[4488]: "pppol2tp" 
xl2tpd[4488]: "7" 
xl2tpd[4488]: "pppol2tp_lns_mode" 
xl2tpd[4488]: "pppol2tp_tunnel_id" 
xl2tpd[4488]: "50888" 
xl2tpd[4488]: "pppol2tp_session_id" 
xl2tpd[4488]: "48585" 
xl2tpd[4488]: "passive" 
xl2tpd[4488]: "nodetach" 
xl2tpd[4488]: "192.168.1.50:192.168.0.1" 
xl2tpd[4488]: "auth" 
xl2tpd[4488]: "require-chap" 
xl2tpd[4488]: "name" 
xl2tpd[4488]: "myhostname" 
xl2tpd[4488]: Call established with 192.168.1.24, PID: 4497, Local: 48585, Remote: 54280, Serial: 520
/usr/sbin/pppd: using the plugin option requires root privilege
xl2tpd[4488]: child_handler : pppd exited for call 54280 with code 2
xl2tpd[4488]: call_close: Call 48585 to 192.168.1.24 disconnected
xl2tpd[4488]: control_finish: Connection closed to 192.168.1.24, port 1701 (Last session has closed), Local: 50888, Remote: 27906
xl2tpd[4488]: Terminating pppd: sending TERM signal to pid 4497
xl2tpd[4488]: 
```

##### 1.3 Tcp dump

LAC > SCCRQ > LNS  
LNS > SCCRP > LAC  
LAC > SCCCN > LNS  
LNS > ZLB   > LAC  
LAC > ICRQ  > LNS  
LNS > ICRP  > LAC  
LAC > ICCN  > LNS  
LNS > **CDN**   > LAC  
LAC > StopCCN > LNS  


#### 2. Keep the Tunnel and Session

##### 2.1 Guess

May it because of pppd exiting ?   


##### 2.2 Find the basis

"xl2tpd[4488]: child_handler : pppd exited for call 54280 with code 2" is printed form   
	xl2tpd.c + 225 : static void child_handler (int sig);  

##### 2.3 Try it

```diff
//break after it printing.
 if ( WIFEXITED( status ) )
 {    
 	l2tp_log (LOG_DEBUG, "%s : pppd exited for call %d with code %d\n", __FUNCTION__,
 			c->cid, WEXITSTATUS( status ) ); 
+ 	break;
 }    

```

LAC show that the tunnel established ;)    
but keeping a short time, **TODO** : pppd


