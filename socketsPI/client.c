#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#include <arpa/inet.h>

#define PORT 3536
#define MESSAGESIZE 22



// tarea ssh
// tcp udp

// ./cliente 192.168.0.3
// ./cliente 127.0.0.1
// argv[0]   arvg[1]     argv[2]


int main(int argc, char *argv[]){
  char buffer[MESSAGESIZE];
  int sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd == -1){
    perror("Socket error\n");
    exit(-1);
  }

  struct sockaddr_in server;
  socklen_t serverSize;

  // Assigning a name to a socket
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = inet_addr(argv[1]);
  // server.sin_addr.s_addr = INADDR_ANY;
  bzero(server.sin_zero, 8);

  serverSize = sizeof(struct sockaddr);

  int r = connect(sd, (struct sockaddr*)&server, serverSize);
  if(r == -1){
    perror("Connect error");
    exit(-1);
  }

  // 10 --> define
  r = recv(sd, buffer, MESSAGESIZE, 0);
  if(r != MESSAGESIZE){
    perror("Recv error");
    exit(-1);
  }
  printf("%s\n", buffer);
  close(sd);
}


// to detect ctrl+c ===> signal
// setsockopt(....,REUSE,...);
