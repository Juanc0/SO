#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//compile
//gcc fork.c -o fork -lm

// void calculateSin(){
// 	int i;
// 	double x=0;
// 	for(i=0; i<2e09; i++){
// 		x = sin(x)+x;
// 	}
// }

int main(){
	pid_t id;
	char str[32];

	fflush(stdin);
	printf("Ingrese una cadena: ");
	scanf("%[^\n]", str);
	printf("str: %s\n", str);
	int len = strlen(str);
	printf("len: %i\n", len);

	id = fork();
	if(id == -1){
		perror("error fork");
		exit(-1);
	}
	if(id == 0){
		printf("Hijo str: %s\n", str);
		int i=0;
		for(i=0; i<len; i++){
			if(str[i]=='a' || str[i]=='e' || str[i]=='i' || str[i]=='o' || str[i]=='u')
				str[i]-=32;
		}
		FILE *ap;
		ap = fopen("datos.txt", "w+");
		if(ap==NULL){
			perror("error opening");
			exit(-1);
		}
		size_t r = fwrite(str, sizeof(char), len, ap);
		if(r != len){
			perror("error fwrite");
			exit(-1);
		}

		int r2 = fclose(ap);
		if(r2 != 0){
			perror("error fclose");
			exit(-1);
		}
	}else{
		double hfr;
		FILE *ap;
		ap = fopen("datos.txt", "r");
		while(ap == NULL){
			perror("error opening");
		};
		size_t r;
		while((r = fread(str, sizeof(char), len, ap)) != len){};
		// size_t r = fread(str, sizeof(char), len, ap);
		// printf("%i\n", (int)r);
		// if(r != len){//*sizeof(struct datos)){
		// 	perror("error fread");
		// 	exit(-1);
		// }
		printf("Padre str: %s\n", str);
		int r2 = fclose(ap);
		if(r2 != 0){
			perror("error fclose");
			exit(-1);
		}
	}
//
// 	char *data;
// 	data = malloc(sizeof(struct datos));
// //	sprint(data, "holamundo");
// 	recibir(data);
// 	mostrar(data);
// 	size_t r = fwrite(data, sizeof(struct datos), ELEMENTS, ap);
// 	if(r != ELEMENTS){
// 		perror("error fwrite");
// 		exit(-1);
// 	}
// 	rewind(ap);
// 	r = fread(data, sizeof(struct datos), ELEMENTS, ap);
// 	if(r != ELEMENTS){//*sizeof(struct datos)){
// 		printf("r value: %i\n", (int)r);
// 		perror("error fread");
// 		exit(-1);
// 	}
// 	mostrar(data);
}

// #define ELEMENTS 1

// struct datos{truct datos{
// 	char nombre[32];
// 	int edad;
// 	char genero;
// 	float estatura;
// };
//
// int recibir(void *x){
// 	struct datos *p = x;
// 	printf("genero: ");
// //lee el \n
// 	scanf("%c", &p->genero);
// 	char nombre[32];
// 	int edad;
// 	char genero;
// 	float estatura;
// };
//
// int recibir(void *x){
// 	struct datos *p = x;
// 	printf("genero: ");
// //lee el \n
// 	scanf("%c", &p->genero);
// 	printf("estatura: ");
// 	scanf("%f", &p->estatura);
// 	printf("nombre: ");
// 	scanf("%s", p->nombre);
// 	printf("edad: ");
// 	scanf("%i", &p->edad);
// }
//
// void mostrar(void *x){
// 	struct datos *p = x;
// 	printf("nombre: %s\n",p->nombre);
// 	printf("edad: %i\n",p->edad);
// 	printf("genero: %c\n",p->genero);
// 	printf("estatura: %f\n",p->estatura);
// }
//
// main(){
// 	FILE *ap;
// 	ap = fopen("datos.txt", "w+");
// 	if(ap==NULL){
// 		perror("error opening");
// 		exit(-1);
// 	}
// 	char *data;
// 	data = malloc(sizeof(struct datos));
// //	sprint(data, "holamundo");
// 	recibir(data);
// 	mostrar(data);
// 	size_t r = fwrite(data, sizeof(struct datos), ELEMENTS, ap);
// 	if(r != ELEMENTS){
// 		perror("error fwrite");
// 		exit(-1);
// 	}
// 	rewind(ap);
// 	r = fread(data, sizeof(struct datos), ELEMENTS, ap);
// 	if(r != ELEMENTS){//*sizeof(struct datos)){
// 		printf("r value: %i\n", (int)r);
// 		perror("error fread");
// 		exit(-1);
// 	}
// 	mostrar(data);
//
// 	int r2 = fclose(ap);
// 	if(r2 != 0){
// 		perror("error fclose");
// 		exit(-1);
// 	}
//
// }
