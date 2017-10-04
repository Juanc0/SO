#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>


double piSum(int k, int j) {
  double sum = 0;
  int odd, i;
  for(i = k; i < j; i++) {
    if (i%2 == 0) {
      odd = 2*i + 1;
    }
    else {
      odd = -(2*i + 1);
    }
    sum += 4.0/odd;
  }
  return sum;
}

int main(){
  int r;
  pid_t pid;
  pid = fork();
  if(pid == -1) {
    perror("fork error");
    exit(-1);
  }

  key_t key=666;
  int shmId = shmget(key, sizeof(double), 0666|IPC_CREAT);
  if(shmId == -1){
    perror("Error shmget\n");
    exit(-1);
  }
  float* ap = (float*)shmat(shmId, 0, 0);
  if(ap == (float*)(-1)){
    perror("Error shmat\n");
    exit(-1);
  }

  if(pid == 0) { // Hijo
    double data = piSum(0, 5e08);
    *ap = data;
    sleep(1);
    exit(0);
    // r = write(ap, &data, sizeof(double));
    // if(r != sizeof(double)) {
    //   perror("write error");
    //   exit(-1);
    // }
  }else{ // Padre

    double data = piSum(5e08, 1e09 + 1);
    // int cpid=0;
    // if((cpid=wait(&status)) == pid){
    //
    // }
    double result=0;
    result=*ap;
    // result += data;
    printf("%2.9lf\n", result);
    // printf("%s\n", result);
    // do{
    //   r = read(ap, &result, sizeof(double));
    // }while(r != sizeof(double));

    r = shmdt(ap);
    if(r != 0) {
      perror("Error shmdt");
      exit(-1);
    }
  }
  return 0;
}
