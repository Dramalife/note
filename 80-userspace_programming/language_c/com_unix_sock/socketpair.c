#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char **argv)
{
	int z;			/* Status return code */
	int s[2];		/* Pair of sockets */
	struct msghdr msg;
	struct iovec iov[1];
	char send_buf[100] = "TEST";
	struct msghdr msgr;
	struct iovec iovr[1];
	char recv_buf[100];

	/*
	 * Create a pair of local sockets:
	 */
	z = socketpair(AF_LOCAL, SOCK_STREAM, 0, s);

	if (z == -1) {
		fprintf(stderr,
			"%s:socketpair(AF_LOCAL,SOCK_STREAM," "0)/n",
			strerror(errno));
		return 1;	/* Failed */
	}

	/*
	 * Sendmsg s[1]:
	 */

	bzero(&msg, sizeof(msg));
	msg.msg_name = NULL;	/* attention this is a pointer to void* type */
	msg.msg_namelen = 0;
	iov[0].iov_base = send_buf;
	iov[0].iov_len = sizeof(send_buf);
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	printf("sendmsg begin./n");
	z = sendmsg(s[1], &msg, 0);
	if (z == -1) {
		fprintf(stderr, "Sendmsg failed.  errno : %s/n",
			strerror(errno));
		return -1;
	}
	printf("Sendmsg Success!/n");

	/*
	 * Read from socket s[0]:
	 */

	bzero(&msg, sizeof(msg));
	msgr.msg_name = NULL;	/* attention this is a pointer to void* type */
	msgr.msg_namelen = 0;
	iovr[0].iov_base = &recv_buf;
	iovr[0].iov_len = sizeof(recv_buf);
	msgr.msg_iov = iovr;
	msgr.msg_iovlen = 1;

	z = recvmsg(s[0], &msgr, 0);
	if (z == -1) {
		fprintf(stderr, "Recvmsg failed.  errno : %s/n",
			strerror(errno));
		return -1;
	}
	printf("Recvmsg Success!/n");
	printf("recvmsg : %s/n", recv_buf);

	/*
	 * Close the sockets:
	 */
	close(s[0]);
	close(s[1]);

	puts("Done");
	return 0;
}
