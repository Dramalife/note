> \# note "ROUTE" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Ref : H3C-03-路由分册  
\#  
\# Init : 2019.09.25;  
\# Update   
\#  
  


### 1. Concept

#### 1.1 Classification - "根据来源"

|||
|--|--|
|**直连路由**|链路层协议发现的路由|
|静态路由|由网络管理员手工配置|
||动态路由协议发现的路由|

#### 1.2 Classification - "根据路由目的地"

|||
|--|--|
|子网路由|目的地为子网|
|**主机路由**|目的地为主机|

#### 1.3 Classification - "根据目的地与该路由器是否直接相连"

|||
|--|--|
|直接路由|目的地所在网络与路由器直接相连|
|间接路由|目的地所在网络与路由器非直接相连|

