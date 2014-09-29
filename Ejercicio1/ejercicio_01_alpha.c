#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

	struct timeval Tinicio, Tfin;

	long duracion;
	int pid, err;

	
	// Tiempo de Inicio
	gettimeofday(&Tinicio,0);
	// Nuevo proceso
	pid = fork();
	
	// proceso padre...
	if (pid != 0) {
		// Tiempo final
		gettimeofday(&Tfin,0);
		// Lo transformo a uSegundos
		duracion= ((Tfin.tv_sec * 1000000) + Tfin.tv_usec) - ((Tinicio.tv_sec * 1000000) + Tinicio.tv_usec);
	} else {
	//proceso hijo...
		exit(0);
	};

	printf("Tiempo para crear un nuevo hijo: %d uSegs \n",duracion);
	printf ("Cantidad de procesos que puede crear:%lu \n",sysconf(_SC_CHILD_MAX));
	return 0;
}

