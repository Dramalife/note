#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <unistd.h> /* sleep */

#include <signal.h>

#include <errno.h> /* EPIPE */

int main(int argc, char** argv) {
  if (SIG_ERR == signal(SIGPIPE, SIG_IGN)) {
    printf("signal\n");
    exit(2);
  }

  int fd_sock = -1;
  printf("socket\n");
  fd_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == fd_sock) {
    exit(2);
  }

  struct sockaddr_in my_addr;
  memset(&my_addr, 0, sizeof(struct sockaddr_in));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(10008);
  inet_aton("127.0.0.1", &my_addr.sin_addr);

  printf("connect\n");
  if (-1 == connect(fd_sock, (struct sockaddr*)&my_addr,
                    sizeof(struct sockaddr_in))) {
    exit(2);
  }

  printf("-----\n");
  char* str = "   ";
  int ret = -1;
  while (1) {
    sleep(2);
    ret = write(fd_sock, str, 3);
    printf("ret=%d\n", ret);
    if (-1 == ret) {
      printf("errno=%d, ECONNRESET=%d, EPIPE=%d\n", errno, ECONNRESET, EPIPE);
      // close, RESTART
    }
    // close(fd_sock);
    // exit(1);
  }
  return 0;
}
