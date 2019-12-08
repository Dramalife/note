## Source code 
wget http://man7.org/tlpi/code/download/tlpi-191118-dist.tar.gz
Path : tlpi-dist/pipes/fifo_seqnum_client.c

## Why need prepared source file - "fifo_seqnum_client.i" ?
Dramalife don`t like to sort out TLPI defined headers, so prepared
source files.

## Need other works ?
Yes, we just solved header problems, don`t have the function implementation yet.
Find the function names gcc can`t found when compiling, then copy them from TLPI.
Example:
	root@orangepizero:~/note/80-userspace_programming/ipc/fifo# gcc fifo_seqnum_client.i
	/tmp/ccUYfPe7.o: In function `main':
	fifo_seqnum_client.c:(.text+0x4c): undefined reference to `usageErr'
	fifo_seqnum_client.c:(.text+0x98): undefined reference to `errExit'
	fifo_seqnum_client.c:(.text+0xb2): undefined reference to `errExit'
	fifo_seqnum_client.c:(.text+0xd2): undefined reference to `getInt'
	fifo_seqnum_client.c:(.text+0x100): undefined reference to `errExit'
	fifo_seqnum_client.c:(.text+0x11e): undefined reference to `fatal'
	fifo_seqnum_client.c:(.text+0x144): undefined reference to `errExit'
	fifo_seqnum_client.c:(.text+0x162): undefined reference to `fatal'
	collect2: error: ld returned 1 exit status
	root@orangepizero:~/note/80-userspace_programming/ipc/fifo# gcc fifo_seqnum_server.i
	/tmp/ccS40JxW.o: In function `main':
	fifo_seqnum_server.c:(.text+0x46): undefined reference to `errExit'
	fifo_seqnum_server.c:(.text+0x6c): undefined reference to `errExit'
	fifo_seqnum_server.c:(.text+0x92): undefined reference to `errExit'
	fifo_seqnum_server.c:(.text+0xac): undefined reference to `errExit'
	fifo_seqnum_server.c:(.text+0x10a): undefined reference to `errMsg'
	fifo_seqnum_server.c:(.text+0x150): undefined reference to `errMsg'
	collect2: error: ld returned 1 exit status
Function implementation we need: (tips - vim block edit && sort u)
	errExit
	errMsg
	fatal

	getInt
	usageErr
