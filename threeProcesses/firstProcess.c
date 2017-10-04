#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>



// #include <sys/mode.h>

int main (){
  int descr, longmens, i;
  char mensaje[100];

  sprintf (mensaje, "Un saludo desde el proceso uno");
  longmens = strlen (mensaje) + 1;
  printf("%i\n", longmens);
  int r=0;
  r = unlink("myfifo");
  // if(r == -1){
    // printf("Error unlink\n");
    // perror("Error unlink\n");
    // exit(-1);
  // }
  r = mkfifo("myfifo",0);
  if(r == -1){
    perror("Error mkfifo\n");
    exit(-1);
  }
  r = chmod("myfifo", 0600);
  if(r == -1){
    perror("Error mkfifo\n");
    exit(-1);
  }
  // desc = open("myfifo", RD_ONLY);
  descr = open("myfifo", O_WRONLY);
  r = write(descr, mensaje, longmens);
  // r = read(desc, datos, tam);
  close(descr);

  return 0;





  // int descr, longmens, i;
  // char mensaje[100];
  //
  // sprintf (mensaje, "Un saludo desde el proceso %d", getpid ());
  // longmens = strlen (mensaje) + 1;
  // do{		/* intentar la conexion */
  //   descr = open ("tuberia", O_WRONLY);
  //   if (descr == -1) sleep (1);
  // }while (descr == -1);
  // for (i=0; i<3; i++){
  //   write (descr, mensaje, longmens);
  //   sleep (3);
  // }
  // close (descr);
  // printf "Fin del escritor %d\n", getpid ());
}
