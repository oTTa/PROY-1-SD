#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>


int main() {

	struct timespec ini, fin;

	long duracion;
	int pid, err;

	
	// Tiempo de Inicio
	clock_gettime( CLOCK_REALTIME, &ini);   // inicio
	// Nuevo proceso
	pid = fork();
	
	// proceso padre...
	if (pid != 0) {
		// Tiempo final
		 clock_gettime( CLOCK_REALTIME, &fin) ;    // fin
		// Lo transformo a nSegundos
		duracion =( fin.tv_sec - ini.tv_sec )*1000000000+ (double)( fin.tv_nsec - ini.tv_nsec );
	} else {
	//proceso hijo...
		exit(0);
	};

	printf("Tiempo para crear un nuevo hijo: %d nSegs \n",duracion);

}