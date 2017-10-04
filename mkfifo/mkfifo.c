#include <sys/types.h>
#include <sys/stat.h>

int main(){
  int r=0;
  r = unlink("nombre",0);
  if(r == -1){
    perror("Error unlink\n");
    exit(-1);
  }
  r = mkfifo("nombre",0);
  if(r == -1){
    perror("Error mkfifo\n");
    exit(-1);
  }
  r = chmod("nombre", 0600);
  if(r == -1){
    perror("Error mkfifo\n");
    exit(-1);
  }
  desc = open("nombre", RD_ONLY);
  desc = open("nombre", WR_ONLY);
  r = write(desc, datos, tam);
  r = read(desc, datos, tam);
  close(desc);

  return 0;
}
