#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <unistd.h> /* sleep */

#include <errno.h>

int main(int argc, char** argv) {
  int fd_sock = -1;
  printf("socket\n");
  fd_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == fd_sock) {
    exit(2);
  }

  // BIND: Address already in use
  int on = 1;
  if (-1 == setsockopt(fd_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) {
    printf("setsockopt:%s\n", strerror(errno));
    exit(2);
  }

  struct sockaddr_in my_addr;
  memset(&my_addr, 0, sizeof(struct sockaddr_in));
  my_addr.sin_family = AF_INET;
  my_addr.sin_port = htons(10008);
  // inet_aton("127.0.0.1", &my_addr.sin_addr);
  my_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  printf("bind\n");
  if (-1 ==
      bind(fd_sock, (struct sockaddr*)&my_addr, sizeof(struct sockaddr_in))) {
    printf("Error:%s\n", strerror(errno));
    exit(2);
  }

  printf("listen\n");
  /* listen()  marks the socket referred to by sockfd as a passive socket, that
   * is, as a socket that will be used to accept incoming connection requests
   * using accept(2).
   */
  if (-1 == listen(fd_sock, 50)) {
    printf("Error:%s\n", strerror(errno));
    exit(2);
  }

  /*        The  addrlen  argument is a value-result argument: the caller must
     initialize it to contain the size (in bytes) of the structure pointed to by
     addr; on return it will contain the actual size of the peer address.
         */
  socklen_t peer_len;
  struct sockaddr_in peer_addr;
  memset(&peer_addr, 0, sizeof(struct sockaddr_in));
  peer_len = sizeof(struct sockaddr_in);  // if not, EINVAL == accept

  printf("accept\n");
  int fd_accept = -1;
  if (-1 ==
      (fd_accept = accept(fd_sock, (struct sockaddr*)&peer_addr, &peer_len))) {
    // EINVAL
    printf("Error:%d:%s\n", errno, strerror(errno));
    exit(2);
  } else {
    printf("peer:%d\n", ntohs(peer_addr.sin_port));
  }

  printf("-----\n");
  char buff[8];
  int ret = -1;
  while (1) {
    memset(buff, 0, sizeof(buff));
    ret = read(fd_accept, &buff, sizeof(buff));
    if (0 < ret) {
      printf("%s\n", buff);
    } else if (0 == ret) {
      printf("EOF?\n");
    } else if (-1 == ret) {
      // [x] read(fd_socket):
      //   Error:Transport endpoint is not connected
      // [v] read(fd_accept)

      // EAGAIN

      printf("ret=%d, errno=%d, Error:%s\n", ret, errno, strerror(errno));
    }
    sleep(1);
  }
  return 0;
}
