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
double time1_nano, time2_nano;
struct rlimit rlim;
struct timespec ti_nano, tf_nano;	
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
	

	printf("Se tardo en crear un proceso en una maquina remota: %g microsegundos || %u nanosegundos\n", time1_nano/1000, (uint) time1_nano);	
	printf("Se tardo en hacer una llamada system en una maquina remota: %g microsegundos || %u nanosegundos\n", time2_nano/1000, (uint) time2_nano);	

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

double calcularTiempo_nano()
{
	return (   (tf_nano.tv_sec - ti_nano.tv_sec)*1000000000 + (tf_nano.tv_nsec - ti_nano.tv_nsec)   );
}

void realizarFork()
{
	//1 = fork + cargar imagen
	//!=1 = system
	opcion = 1;
	clock_gettime( id, &ti_nano);
	
	ejecutartarea_1( &opcion, clnt);	

	clock_gettime( id, &tf_nano);
	
	time1_nano = calcularTiempo_nano();	
}

void realizarSystem()
{
	//1 = fork + cargar imagen
	//!=1 = system
	opcion = 2;
	clock_gettime( id, &ti_nano);

	ejecutartarea_1( &opcion, clnt);	

	clock_gettime( id, &tf_nano);
	
	time2_nano = calcularTiempo_nano();	
} 
