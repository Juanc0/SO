#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

#define NUM_THREADS 32753

struct myargs{
  int toprint;
  int i;
};

void* myfunction(int* a){
  printf("%i\n", *a);
}

int main(){
  int r=0;
  int i;
  int is[NUM_THREADS];
  for(i=0; i<NUM_THREADS; i++){
    is[i] = i;
  }
  pthread_t threads[NUM_THREADS];

  for(i=0; i<NUM_THREADS; i++){
    // printf("create %i\n", i);
    r = pthread_create(&threads[i], NULL, myfunction, (void*)&is[i]);
    if(r != 0){
      perror("pthread_create error");
      exit(-1);
    }
  }
  for(i=0; i<NUM_THREADS; i++){
    // printf("join %i\n", i);
    r = pthread_join(threads[i], NULL);
    // printf("join r %i\n", r);
    if(r != 0){
        perror("pthread_join error");
        exit(-1);
    }
  }
}
