identify processes using files or sockets

#### 1. sample

```bash
# -k, --kill
# 	Kill processes accessing the file.  Unless changed with -SIGNAL, SIGKILL is sent.  An fuser process never kills itself, but may kill other fuser  processes.   The
# 	effective user ID of the process executing fuser is set to its real user ID before attempting to kill.

fuser -k FILE
```
