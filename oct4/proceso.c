#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void recvConfirmation() {
  char buffer[2];

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

  r = read(descr, buffer, 2);
  if(r != 2) {
    perror("read error");
    exit(-1);
  }

  printf("%s\n", buffer);
  close(descr);
}

void sendData(int *datos) {

//   unlink("pipe");
// int r = mkfifo("pipe", 0600);
// if(r == -1) {
//   perror("mkfifo error");
//   exit(-1);
// }
  int descr = open("pipe", O_WRONLY);
  if(descr == -1) {
    perror("open error");
    exit(-1);
  }

  int r = write(descr, datos, sizeof(int));
  if(r != sizeof(int)) {
    perror("write error");
    exit(-1);
  }

  close(descr);
}

int main() {
  int *datos = malloc(sizeof(int));
  *datos = 123;
  sendData(datos);

  // recvConfirmation();

  return 0;
}
