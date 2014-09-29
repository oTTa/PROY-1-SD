#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h> 
#include <time.h>

void LocalCall (unsigned long *entrada1,unsigned long *entrada2,unsigned long *salida);


int main (){
  //declaracion de variables
  unsigned long argumento1  [256],argumento2  [256];
  unsigned long respuesta[512];
  double tiempo;
  struct timeval ti_usec, tf_usec;
  int i;
  for (i=0;i<256;i++){
    *(argumento1+i)=rand();
    *(argumento2+i)=rand();
  }
  printf ("Se generaron 2 argumentos con 256 datos de tipo LONG (4 bytes) como entrada a la llamada local\n");
  // ejecuto la llamada y calculo el tiempo
  gettimeofday(&ti_usec,0);  // Instante inicial
  LocalCall(argumento1,argumento2,respuesta);
  gettimeofday(&tf_usec,0);  // Instante final
  tiempo= (tf_usec.tv_sec - ti_usec.tv_sec)*1000000 + (tf_usec.tv_usec - ti_usec.tv_usec);
  //muestro los resultados
  printf ("La llamada a LocalCall demoro %g us\n",tiempo);
  return (0);
}

void LocalCall (unsigned long *entrada1,unsigned long *entrada2,unsigned long *salida){
  int i=0;
  int j=0;
  while (i<256){
    *(salida+j)=*(entrada1+i)/10*8+9-6;
    j++;
    *(salida+j)=*(entrada2+i)/10*8+9-6;
    j++;
    i++;
  }
}
