#include "stdio.h"
#include "stdlib.h"

struct datos{
	char nombre[32];
	int edad;
	char genero;
	float estatura;
};

void recibir(void *x){
	struct datos *p = x;
	printf("nombre: ");
	scanf("%s", p->nombre);
	printf("edad: ");
	scanf("%i", &p->edad);
	printf("genero: ");
//lee el \n
	scanf("%c", &p->genero);
	printf("estatura: ");
	scanf("%f", &p->estatura);
}

void mostrar(void *x){
	struct datos *p = x;
	printf("nombre: %s\n",p->nombre);
	printf("edad: %i\n",p->edad);
	printf("genero: %c\n",p->genero);
	printf("estatura: %f\n",p->estatura);
}

int main(){
	struct datos *persona;
	persona=malloc(sizeof(struct datos));
	if(persona==NULL){
		perror("error en malloc");
		exit(-1);
	}
	recibir(persona);
	mostrar(persona);
	free(persona);


//	int *x = 0;
//	int a = 7;
//	int b = 5;
//	printf("a: %i\n",a);
//	printf("&a: %p\n",(void *)&a);
//	printf("&a+1: %p\n",(void *)&a+1);
//	printf("(&a+1): %p\n",(void *)(&a+1));
//	
//	printf("a: %i\n",b);
//	printf("&a: %p\n",(void *)&b);
//
//	(&a+1)=9;
//
//	printf("a: %i\n",a);
//	printf("&a: %p\n",(void *)&a);
//	
//	printf("a: %i\n",b);
//	printf("&a: %p\n",(void *)&b);
//	printf("\nhola mundo\n");
}
