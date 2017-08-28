#include <stdio.h>
#include <stdlib.h>
#define ELEMENTS 1

struct datos{
	char nombre[32];
	int edad;
	char genero;
	float estatura;
};

int recibir(void *x){
	struct datos *p = x;
	printf("genero: ");
//lee el \n
	scanf("%c", &p->genero);
	printf("estatura: ");
	scanf("%f", &p->estatura);
	printf("nombre: ");
	scanf("%s", p->nombre);
	printf("edad: ");
	scanf("%i", &p->edad);
}

void mostrar(void *x){
	struct datos *p = x;
	printf("nombre: %s\n",p->nombre);
	printf("edad: %i\n",p->edad);
	printf("genero: %c\n",p->genero);
	printf("estatura: %f\n",p->estatura);
}

main(){
	FILE *ap;
	ap = fopen("datos.txt", "w+");
	if(ap==NULL){
		perror("error opening");
		exit(-1);
	}
	char *data;
	data = malloc(sizeof(struct datos));
//	sprint(data, "holamundo");
	recibir(data);
	mostrar(data);
	size_t r = fwrite(data, sizeof(struct datos), ELEMENTS, ap);
	if(r != ELEMENTS){
		perror("error fwrite");
		exit(-1);
	}
	rewind(ap);
	r = fread(data, sizeof(struct datos), ELEMENTS, ap);
	if(r != ELEMENTS){//*sizeof(struct datos)){
		printf("r value: %i\n", (int)r);
		perror("error fread");
		exit(-1);
	}
	mostrar(data);

	int r2 = fclose(ap);
	if(r2 != 0){
		perror("error fclose");
		exit(-1);
	}

}
