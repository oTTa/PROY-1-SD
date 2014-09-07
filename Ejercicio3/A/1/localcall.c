#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h> 
#include <time.h>

void LocalCall (unsigned long entrada,unsigned long *salida);


int main (){
  //declaracion de variables
  unsigned long argumento;
  unsigned long* respuesta;
  double tiemponano;
  struct timespec ti_nano, tf_nano;
  //genero un numero aleatorio
  srand(time(NULL));
  argumento=rand();
  printf ("Se genero un argumento de tipo LONG (4 bytes) que tien el valor %lu\n",argumento);
  // ejecuto la llamada y calculo el tiempo
  clock_gettime(CLOCK_REALTIME, &ti_nano);  // Instante inicial
  LocalCall(argumento,respuesta);
  clock_gettime(CLOCK_REALTIME, &tf_nano);  // Instante final
  tiemponano= (tf_nano.tv_sec - ti_nano.tv_sec)*1000000000 + (tf_nano.tv_nsec - ti_nano.tv_nsec);
  //muestro los resultados
  printf ("Local Call dio como resultado en la salida: %lu\n",*respuesta);  
  printf ("La llamada a LocalCall demoro %g ns\n",tiemponano);
  return (0);
}

void LocalCall (unsigned long entrada,unsigned long *salida){
  *salida=entrada/8*2+9-6;
  printf ("Soy la llamada local y realice la siguiente operacion aritmetica, (entrada/8*2+6-9), que fue asignada a la salida\n");
}
