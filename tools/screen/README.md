> \# note "screen" related file  
\# Copyright (C) 2019 Dramalife@live.com  
\#   
\# This file is part of [note](https://github.com/Dramalife/note.git)  
\#   
\# note is distributed in the hope that it will be useful, but  
\# WITHOUT ANY WARRANTY; without even the implied warranty of  
\# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
\#  
\# Ref : man 1 screen;  
\#  
\# Init : 2019.10.17;  
\# Update   
\#  
  


### 1. manual

```man
-d|-D [pid.tty.host]
	does not start screen, but detaches the elsewhere running screen session. It has the same effect as typing "C-a d" from screen's controlling  terminal.  -D  is  the
	equivalent  to  the  power  detach  key.   If  no session can be detached, this option is ignored. In combination with the -r/-R option more powerful effects can be
	achieved:
-d -r   Reattach a session and if necessary detach it first.
-d -R   Reattach a session and if necessary detach or even create it first.
-d -RR  Reattach a session and if necessary detach or create it. Use the first session if more than one session is available.
-r sessionowner/[pid.tty.host]
	resumes a detached screen session.  No other options (except combinations with -d/-D) may be specified, though an optional prefix of [pid.]tty.host may be needed to
	distinguish between multiple detached screen sessions.  The second form is used to connect to another user's screen session which runs in multiuser mode. This indi‐
	cates that screen should look for sessions in another user's directory. This requires setuid-root.
-S sessionname
	When  creating  a new session, this option can be used to specify a meaningful name for the session. This name identifies the session for "screen -list" and "screen
	-r" actions. It substitutes the default [tty.host] suffix.
-ls [match]
-list [match]
	does  not  start  screen,  but  prints  a  list of pid.tty.host strings and creation timestamps identifying your screen sessions.  Sessions marked `detached' can be
	resumed with "screen -r". Those marked `attached' are running and have a controlling terminal. If the session runs in multiuser mode, it is marked `multi'. Sessions
	marked  as  `unreachable'  either  live  on a different host or are `dead'.  An unreachable session is considered dead, when its name matches either the name of the
	local host, or the specified parameter, if any.  See the -r flag for a description how to construct matches.  Sessions marked as `dead' should be thoroughly checked
	and removed.  Ask your system administrator if you are not sure. Remove sessions with the -wipe option.
```

### 2. Use

```bash
# List screen sessions
screen -ls

# Create a new session
screen -S my1stscreen

# Resumes a detached screen session
screen -r my1stscreen

# Detaches the session from its controlling terminal
# typing "C-a d"(Ctrl + a  + d);

# Detaches the session form other terminal
screen -d my1stscreen
```

