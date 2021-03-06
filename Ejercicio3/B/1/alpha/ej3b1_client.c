/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "ej3b1.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <sys/resource.h>

void
ej3b1_1(char *host)
{
	CLIENT *clnt;
	u_long  *result_1;
	u_long  ejecutartarea_1_arg;
	double time;
	struct timeval Tinicio, Tfin;	
	clockid_t id = CLOCK_REALTIME;
	
#ifndef	DEBUG
	clnt = clnt_create (host, ej3b1, ej3b1v1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	ejecutartarea_1_arg=rand();
	printf ("Se genero un argumento de tipo LONG (4 bytes) que tien el valor %lu\n",ejecutartarea_1_arg);
	//realizo la llamada al server
	gettimeofday(&Tinicio,0); //tiempo Inicio
	result_1 = ejecutartarea_1(&ejecutartarea_1_arg, clnt);
	gettimeofday(&Tfin,0); //tiempo final
	//calculo el tiempo de ejecucion
	time=((Tfin.tv_sec * 1000000) + Tfin.tv_usec) - ((Tinicio.tv_sec * 1000000) + Tinicio.tv_usec);
	//muestro los resultados
	printf("El valor de la salida es:%lu\n",*result_1);
	printf("Se tardo en realizar la tarea en una maquina remota: %g microsegundos \n", time);
	if (result_1 == (u_long *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	printf("Cerrando conexion...\n");
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	ej3b1_1 (host);
exit (0);
}
