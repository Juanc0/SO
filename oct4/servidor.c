#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>
#define BACKLOG 2
#define PORT 3536

int main() {
  int *datos = malloc(sizeof(int));
  int serversd, clientsd;
  struct sockaddr_in server, client;
  socklen_t clientSize;
  int serverSize, r;

  serversd = socket(AF_INET, SOCK_STREAM, 0);
  if(serversd == -1){
    perror("Socket error\n");
    exit(-1);
  }

  // Assigning a name to a socket
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;
  bzero(server.sin_zero, 8);

  serverSize = sizeof(struct sockaddr);

  r = bind(serversd, (struct sockaddr*)&server, serverSize);//  same as accept?
  if(r == -1){
    perror("Bind error\n");
    exit(-1);
  }

  r = listen(serversd, BACKLOG);
  if(r == -1){
    perror("Listen error\n");
    exit(-1);
  }

  // process or thread
  clientsd = accept(serversd, (struct sockaddr*)&client, (socklen_t*)&clientSize);
  if(clientsd == -1){
    perror("Accept error\n");
    exit(-1);
  }

  r = recv(clientsd, datos, sizeof(int), 0);
  if(r != sizeof(int)){
    perror("Recv error");
    exit(-1);
  }

  close(clientsd);
  close(serversd);
  printf("%d\n", *datos);
}
