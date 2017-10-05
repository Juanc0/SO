#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#define PORT 3536

void sendData(int datos, char *argv[]) {
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

  serverSize = sizeof(struct sockaddr_in);

  int r = connect(sd, (struct sockaddr*)&server, serverSize);
  if(r == -1) {
    perror("Connect error");
    exit(-1);
  }

  r = send(sd, &datos, sizeof(int), 0);
  if(r == -1){
    perror("Send error\n");
    exit(-1);
  }

  close(sd);
}

void sendConfirmation() {
  int descr = open("pipe", O_WRONLY);
  if(descr == -1) {
    perror("open pipe error");
    exit(-1);
  }

  int r = write(descr, "OK", 2);
  if(r != 2) {
    perror("write error");
    exit(-1);
  }

  close(descr);
}

int recvData() {
  int *datos = malloc(sizeof(int));

  unlink("pipe");
  int r = mkfifo("pipe", 0600);
  if(r == -1) {
    perror("mkfifo error");
    exit(-1);
  }

  int descr = open("pipe", O_RDONLY);
  if(descr == -1) {
    perror("open error");
    exit(-1);
  }

  r = read(descr, datos, sizeof(int));
  if(r != sizeof(int)) {
    perror("read error");
    exit(-1);
  }

  close(descr);
  return *datos;
}

int main(int argc, char *argv[]) {
  int datos = recvData();
  printf("%d\n", datos);

  // sendConfirmation();

  sendData(datos, argv);

  return 0;
}
