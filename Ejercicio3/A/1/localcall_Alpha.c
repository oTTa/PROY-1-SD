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
  double tiempo;
  struct timeval ti_usec, tf_usec;
  //genero un numero aleatorio
  argumento=rand();
  printf ("Se genero un argumento de tipo LONG (4 bytes) que tien el valor %lu\n",argumento);
  // ejecuto la llamada y calculo el tiempo
  gettimeofday(&ti_usec,0);  // Instante inicial
  LocalCall(argumento,respuesta);
  gettimeofday(&tf_usec,0);  // Instante final
  tiempo= (tf_usec.tv_sec - ti_usec.tv_sec)*1000000 + (tf_usec.tv_usec - ti_usec.tv_usec);
  //muestro los resultados
  printf ("Local Call dio como resultado en la salida: %lu\n",*respuesta);  
  printf ("La llamada a LocalCall demoro %g us\n",tiempo);
  return (0);
}

void LocalCall (unsigned long entrada,unsigned long *salida){
  *salida=entrada/8*2+9-6;
  printf ("Soy la llamada local y realice la siguiente operacion aritmetica, (entrada/8*2+6-9), que fue asignada a la salida\n");
}
