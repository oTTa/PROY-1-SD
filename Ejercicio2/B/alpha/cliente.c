#include "ej2b.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <sys/resource.h>

//time1 es para el tiempo con el metodo de creacion del proceso hijo
//time2 es para el tiempo con el metodo del system
double time1, time2;
struct rlimit rlim;
struct timeval Tinicio, Tfin;	
clockid_t id = CLOCK_REALTIME;
CLIENT *clnt;
int opcion;

CLIENT* establecerConexion(char *servername);

void cerrarConexion();

double calcularTiempo_nano();

void realizarFork();

void realizarSystem();

int main(int argc, char *argv[])
{
	printf("Estableciendo conexion...\n");
	clnt = establecerConexion(argv[1]);

	if(clnt != NULL)
		printf("Conexion establecida\n");
	else
	{
		printf("No se ha podido establecer conexion!\n");
		exit(1);
	}

	realizarFork();
	realizarSystem();
	

	printf("Se tardo en crear un proceso en una maquina remota: %g microsegundos \n", time1);	
	printf("Se tardo en hacer una llamada system en una maquina remota: %g microsegundos\n", time2);	

	printf("Cerrando conexion...\n");
	cerrarConexion();
	
	return 0;
}

CLIENT* establecerConexion(char *servername)
{
	return clnt_create(servername, ej2b, ej2bv1, "tcp");
}

void cerrarConexion()
{
	clnt_destroy(clnt);
}

double calcularTiempo_micro()
{
	return (((Tfin.tv_sec * 1000000) + Tfin.tv_usec) - ((Tinicio.tv_sec * 1000000) + Tinicio.tv_usec));
}

void realizarFork()
{
	//1 = fork + cargar imagen
	//!=1 = system
	opcion = 1;
	gettimeofday(&Tinicio,0);
	
	ejecutartarea_1( &opcion, clnt);	

	gettimeofday(&Tfin,0);
	
	time1= calcularTiempo_micro();	
}

void realizarSystem()
{
	//1 = fork + cargar imagen
	//!=1 = system
	opcion = 2;
	gettimeofday(&Tinicio,0);

	ejecutartarea_1( &opcion, clnt);	

	gettimeofday(&Tfin,0);
	
	time2= calcularTiempo_micro();	
} 
