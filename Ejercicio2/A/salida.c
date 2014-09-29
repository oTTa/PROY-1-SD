#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
  int i;
  FILE *archivo;
  
  
  archivo = fopen ("salida.txt", "w");
  i=0;
  
  while(i<1000)
  {
    double aux=2.5*4.3;
    fprintf(archivo, "Soy el proceso hijo \n");
    i++;
  }
  
  fprintf(archivo, "Mi PID es %i \n",getpid());
  fclose (archivo);
  return 0;
}