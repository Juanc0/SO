#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

#define NUM_THREADS 8
#define NUM_CALCS 1e09
#define W (NUM_CALCS/NUM_THREADS)

struct myargs{
  int toprint;
  int i;
};

double* piSum(int k, int j) {
  printf("piSum %i, %i\n", k, j);
  double* sum = 0;
  int odd, i;
  for(i = k; i < j; i++) {
    if (i%2 == 0) {
      odd = 2*i + 1;
    }
    else {
      odd = -(2*i + 1);
    }
    *sum += 4.0/odd;
  }
  return sum;
}

double* myfunction(int* a){
  printf("%i\n", *a);
  double* ret = piSum(*a*W, (*a+1)*W);
  printf("%i %lf\n", *a, *ret);
  return ret;
}

int main(){
  int r=0;
  int i;
  int is[NUM_THREADS];
  for(i=0; i<NUM_THREADS; i++){
    is[i] = i;
  }
  double isret[NUM_THREADS];
  pthread_t threads[NUM_THREADS];

  for(i=0; i<NUM_THREADS; i++){
    printf("create %i\n", i);
    r = pthread_create(&threads[i], NULL, (void*)myfunction, (void*)&is[i]);
    if(r != 0){
      perror("pthread_create error");
      exit(-1);
    }
  }
  for(i=0; i<NUM_THREADS; i++){
    printf("join %i\n", i);
    r = pthread_join(threads[i], (void**)&isret[i]);
    printf("join r %i\n", r);
    if(r != 0){
        perror("pthread_join error");
        exit(-1);
    }
  }
  double sum=0;
  for (i=0; i<NUM_THREADS; i++) {
    printf("%2.9lf\n", isret[i]);
    sum += isret[i];
  }
  printf("PI %2.9lf\n", sum);
}
