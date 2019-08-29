> \# note "l2tp-message(L5)" related file  
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
  
### A. Model

```
message : L5  

 |			 |
 |--------xxxxxxx------->|
 |<-------xxxxxxx--------|
```

### B. Source Code

#### B.1 Header file
```c
// Source : xl2tpd/control.h
/* Control Connection Management */
#define SCCRQ 	1               /* Start-Control-Connection-Request */
#define SCCRP 	2               /* Start-Control-Connection-Reply */
#define SCCCN 	3               /* Start-Control-Connection-Connected */
#define StopCCN 4               /* Stop-Control-Connection-Notification */
/* 5 is reserved */
#define Hello	6               /* Hello */
/* Call Management */
#define OCRQ	7               /* Outgoing-Call-Request */
#define OCRP	8               /* Outgoing-Call-Reply */
#define OCCN	9               /* Outgoing-Call-Connected */
#define ICRQ	10              /* Incoming-Call-Request */
#define ICRP	11              /* Incoming-Call-Reply */
#define ICCN	12              /* Incoming-Call-Connected */
/* 13 is reserved */
#define CDN	14              /* Call-Disconnect-Notify */
/* Error Reporting */
#define WEN	15              /* WAN-Error-Notify */
/* PPP Sesssion Control */
#define SLI	16              /* Set-Link-Info */

#define MAX_MSG 16
```

#### B.2 Logic : Control Connection Management

```c
// xl2tpd/control.c +183
int control_finish (struct tunnel *t, struct call *c)
```

### C. Glossary
```
ZLB : Zero Length Body message
```

### 1. Establish

#### 1.1 L2TP Tunnle establish

|||
|--|--|
|SCCRQ	|Start-Control-Connection-ReQuest	|
|SCCRP	|Start-Control-Connection-RePly		|
|SCCCN	|Start-Control-Connection-CoNnected	|


```
LAC			LNS
 |			 |
 |-------- SCCRQ ------->|
 |			 |
 |<------- SCCRP --------|
 |			 |
 |<------- SCCCN --------|
 |			 |
```

#### 1.2 L2TP Session establish

|||
|--|--|
|ICRQ	|Incoming-Call-ReQuest	|
|ICRP	|Incoming-Call-RePly	|
|ICCN	|Incoming-Call-CoNnected|


```
LAC			LNS
 |			 |
 |-------- ICRQ  ------->|
 |	  	 	 |
 |<------- ICRP  --------|
 |	   		 |
 |<------- ICCN  --------|
 |			 |
```

### 2. 

#### 2.1 L2TP Tunnel

```
LAC/LNS			LNS/LAC
 |			 |
 |------- Hello  ------->|
 |	  	 	 |
 |<------ ZLB    --------|
 |	   		 |
```

### 3. Remove

### 3.1 L2TP Tunnel

```
LAC/LNS			LNS/LAC
 |			 |
 |------- StopCCN ------>|
 |	  	 	 |
 |<------ ZLB    --------|
 |	   		 |
```

### 3.2 L2TP Session

```
LAC/LNS			LNS/LAC
 |			 |
 |------- CDN	  ------>|
 |	  	 	 |
 |<------ ZLB    --------|
 |	   		 |
```

