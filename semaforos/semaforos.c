#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <pthread.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#define MAX_PROCESOS 1
#define SEMAFORO_NAME "semaforo_name"

sem_t *semaforo;

struct datos_tipo{
  int dato;
  int p;
};

void *proceso(void *datos){
  int error;
  struct datos_tipo *datos_proceso;
  datos_proceso = (struct datos_tipo*) datos;
  int a, i, p;
  error = sem_wait(semaforo);
  if(error == -1){
    perror("No pudo esperar el hilo");
    exit(-1);
  }

  a = datos_proceso->dato;
  p = datos_proceso->p;
  for(i=0; i<=p; i++){
    printf("%i",a);
  }
  fflush(stdout);
  sleep(1);
  for(i=0; i<=p; i++){
    printf("- ");
  }
  fflush(stdout);
  error = sem_post(semaforo);
  if(error == -1){
    perror("No pudo seguir el hilo");
    exit(-1);
  }
}

int main(){
  int error;
  char *valor_devuelto;
  struct datos_tipo hilo1_datos, hilo2_datos;
  pthread_t idhilo1, idhilo2;
  hilo1_datos.dato = 1;
  hilo2_datos.dato = 2;
  hilo1_datos.p = 10;
  hilo2_datos.p = 5;
  printf("%i\n", MAX_PROCESOS);
  semaforo = sem_open(SEMAFORO_NAME, O_CREAT, 0700, MAX_PROCESOS);
  if(semaforo == SEM_FAILED){
    perror("No pudo crear el semaforo");
    exit(-1);
  }
  error = pthread_create(&idhilo1, NULL, (void *)proceso, (void *)(&hilo1_datos));
  if(error != 0){
    perror("No pudo crear hilo1");
    exit(-1);
  }
  error = pthread_create(&idhilo2, NULL, (void *)proceso, (void *)(&hilo2_datos));
  if(error != 0){
    perror("No pudo crear hilo2");
    exit(-1);
  }
  pthread_join(idhilo2, (void **)&valor_devuelto);
  pthread_join(idhilo1, (void **)&valor_devuelto);
  sem_close(semaforo);
  unlink(SEMAFORO_NAME);
}
