#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

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

int main() {
  int pipefd[2], r;
  pid_t pid;
  
  r = pipe(pipefd);
  if(r != 0) {
    perror("pipe error");
    exit(-1);
  }

  pid = fork();
  if(pid == -1) {
    perror("fork error");
    exit(-1);
  }

  if(pid == 0) { // Hijo
    double data = piSum(0, 5e08);
    r = write(pipefd[1], &data, 8);
    if(r != 8) {
      perror("write error");
      exit(-1);
    }
  }

  else { // Padre
    double result=0;
    double data = piSum(5e08, 1e09 + 1);
    r = read(pipefd[0], &result, 8);
    result += data;
    if(r != 8) {
      perror("read error");
      exit(-1);
    }
    printf("%2.9lf\n", result);
  }

  return 0;
}
