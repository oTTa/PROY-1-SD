 
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include "MiniFuncion.h"
#include "semaforo.h"

void eliminarMemoria();

int main()
{
  int ch=0;
  int lines=0;
  FILE *fp; 
  clave = obtenerClave(archivoCompartido, enteroCompartido);
  printf("Obtuve la clave.\n");
  crearMemoria();
  printf("Cree la memoria.\n");
  direccionarMemoria();
  printf("Memoria LISTA para usar.\n");

  
  semaforo_cliente=crearSemaforo(obtenerClave(archivoCompartido,enteroCompartido));
  semaforo_servidor=crearSemaforo(obtenerClave(archivoCompartido,enteroCompartido+1));

  while(1)
  {
    signal(semaforo_cliente);
    printf("Esperando solicitud\n");
    wait(semaforo_servidor);
    switch (memoria[0].operacion)
    {
      case 0:
      {
	printf("Terminado");
	eliminarMemoria();
	wait(semaforo_cliente);
	exit(0);
      }
      case 1:
      {
	time_t t;
	struct tm *tm;
	t=time(NULL);
	tm=localtime(&t);
	strftime(memoria[0].resultado, 100, "%H:%M:%S", tm);
	break;
      }
      
      case 2:
      {
	time_t t;
	struct tm *tm;
	t=time(NULL);
	tm=localtime(&t);
	strftime(memoria[0].resultado, 100, "%d/%m/%y", tm);
	break;
      }
      
      case 3:
      {
	gethostname(memoria[0].resultado,100);
	
	break;
      }
      
      case 4:
      {
	
	system ("who >> usuarios.txt");
	
	 fp = fopen("usuarios.txt","r");
	
	 if (fp==NULL){
	   printf ("No existe el archivo\n");
	   return 0;
	 }
	 
	 

	 
      
	 lines++;
	 while ((ch = fgetc(fp)) != EOF)
	 {
	    if (ch == '\n')
		      lines++;
	
	 }
	fclose(fp);
	system ("rm usuarios.txt");
	
	sprintf(memoria[0].resultado, "%i",lines );
	break;
      }
      
     
      
    }
     signal(semaforo_cliente);
  }
  return 0;
}

void eliminarMemoria()
{
	shmdt (memoria);
	shmctl (memory_id , IPC_RMID, (struct shmid_ds *)NULL);
}
