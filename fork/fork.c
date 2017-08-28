#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//compile
//gcc fork.c -o fork -lm

void procesar(){
	int i;
	double x=0;
	for(i=0; i<2e09; i++){
		x = sin(x)+x;
	}
}

int main(){
	pid_t id;
	printf("hola\n");
	fflush(stdout);
	id = fork();
	if(id == -1){
		perror("error fork");
		exit(-1);
	}
	if(id == 0){
		procesar();
	}else{
		procesar();
	}
}
