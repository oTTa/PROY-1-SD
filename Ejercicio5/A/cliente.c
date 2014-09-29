 
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include "MiniFuncion.h"
#include "semaforo.h"

int op;
struct timeval ti,tf;
long tiempo;

void llamar();
void eliminarMemoria();

int main()
{
  clave = obtenerClave(archivoCompartido, enteroCompartido);
  crearMemoria();
  direccionarMemoria();
  semaforo_cliente=asociarseSemaforo(obtenerClave(archivoCompartido,enteroCompartido));

  semaforo_servidor=asociarseSemaforo(obtenerClave(archivoCompartido,enteroCompartido+1));

  while(1)
  {
    printf("Esperando al servidor\n");
    wait(semaforo_cliente);
    printf("---MiniFuncion---\n");
    printf("(1)Obtener hora de sistema\n");
    printf("(2)Obtener fecha de sistema\n");
    printf("(3)Obtener nombre de la máquina\n");
    printf("(4)Obtener cantidad de usuarios logueados\n");
    printf("(0)Salir\n");
     scanf("%i",&op);  
    while (op<0 || op>4)
    {
      printf("Ingrese nuevamente\n");
      scanf("%i",&op);      
    }
    
    if (op==0)
    {
      memoria->operacion=op;
      printf("Saliendo\n");
      signal(semaforo_servidor);
      exit(0);
    }
    
    gettimeofday(&ti, NULL);
    llamar();
    gettimeofday(&tf, NULL);
    tiempo = (tf.tv_sec - ti.tv_sec)*1000000 + (tf.tv_usec - ti.tv_usec);
    
    printf("Resultado=%s\n",memoria->resultado);
    printf("El tiempo que tardó es de %d us\n\n",tiempo);
   
    
  }
}
  
  void llamar()
  {

   memoria->operacion=op;
   signal(semaforo_servidor);
   wait(semaforo_cliente);

  }
  
  void eliminarMemoria()
{
	if (memory_id  != -1)
	{
		shmdt ((char *)memoria);
	}
}
