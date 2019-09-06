> \# note "scp - secure copy" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Ref : runoob.com;  
\#  
\# Init : 2019.09.04;  
\# Update   
\#  
  


### scp — secure copy (remote file copy program)

#### 1. copy file

```bash
# Send file to remote
scp LOCALFILE REMOTE_USERNAME@REMOTE_HOST:/FOLDER 

# Receive file from remote
scp USERNAME@HOSTIP:/home/dramalife/TARGET.FILE ./RECV_PATH
```


#### 2. copy folder

```bash
scp -r LOCAL_FOLDER REMOTE_USER@REMOTE:REMOTE_FOLDER

scp -r REMOTE_USER@REMOTE:REMOTE_FOLDER LOCAL_FOLDER
```


#### 3. firewall - port

```bash
# scp use port 4588
scp -P 4588 REMOTEUSER@REMOTE:/REMOTE LOCAL
```

