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
  double tiemponano;
  struct timespec ti_nano, tf_nano;
  //genero un numero aleatorio
  srand(time(NULL));
  int i;
  for (i=0;i<256;i++){
    *(argumento1+i)=rand();
    *(argumento2+i)=rand();
  }
  printf ("Se generaron 2 argumentos con 256 datos de tipo LONG (4 bytes) como entrada a la llamada local\n");
  // ejecuto la llamada y calculo el tiempo
  clock_gettime(CLOCK_REALTIME, &ti_nano);  // Instante inicial
  LocalCall(argumento1,argumento2,respuesta);
  clock_gettime(CLOCK_REALTIME, &tf_nano);  // Instante final
  tiemponano= (tf_nano.tv_sec - ti_nano.tv_sec)*1000000000 + (tf_nano.tv_nsec - ti_nano.tv_nsec);
  //muestro los resultados
  printf ("La llamada a LocalCall demoro %g us | %g ns\n",tiemponano/1000,tiemponano);
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
