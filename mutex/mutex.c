#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_PROCESOS 1
#define NUM_HILOS 8
static pthread_mutex_t *mymutex;


struct datos_tipo{
	int dato;
	int p;
};

void *proceso(void *datos){
	struct datos_tipo* datos_proceso;
	datos_proceso = (struct datos_tipo*) datos;
	int a, i, p, error;

	a = datos_proceso -> dato;
	p = datos_proceso -> p;

	error = pthread_mutex_lock(mymutex);
	if(error != 0){
		perror("pthread_mutex_lock error");
		exit(-1);
	}
	for(i=0; i <= p; i++){
		printf("%i", a);
	}
	fflush(stdout);
	sleep(1);
	for(i=0; i<=p; i++){
		printf("-");
	}
	fflush(stdout);
	error = pthread_mutex_unlock(mymutex);
	if(error != 0){
		perror("pthread_mutex_unlock error");
		exit(-1);
	}
}

int main(){
	int error, i;
	char* valor_devuelto;
	struct datos_tipo hilo_datos [NUM_HILOS];
	pthread_t idhilo[NUM_HILOS];
	mymutex = (void*)malloc(sizeof(pthread_mutex_t));

	for(i = 0; i < NUM_HILOS; i++){
		hilo_datos[i].dato = i;
		hilo_datos[i].p = i+1;
	}

	error = pthread_mutex_init(mymutex, NULL);
	if(error != 0){
		perror("pthread_mutex_init error");
		exit(-1);
	}

	for(i = 0; i <NUM_HILOS; i++){
		error = pthread_create(&idhilo[i], NULL, (void*) 	proceso, (void*)(&hilo_datos[i]));
		if(error != 0){
			perror("No puedo crear hilo");
			exit(-1);
		}
	}
	for(i=0; i< NUM_HILOS; i++){
		pthread_join(idhilo[i], (void**)&valor_devuelto);
	}
	error = pthread_mutex_destroy(mymutex);
	if(error != 0){
		perror("pthread_mutex_destroy error");
		exit(-1);
	}
	return 0;
}
