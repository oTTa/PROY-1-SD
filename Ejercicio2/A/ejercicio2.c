#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	double tiemponano;
	struct timespec ti_nano, tf_nano;
	int pid;

	clock_gettime(CLOCK_REALTIME, &ti_nano);  // Instante inicial
	pid = fork();

	if (pid != 0)
	{
		wait(pid);
		clock_gettime(CLOCK_REALTIME, &tf_nano);  // Instante final
		tiemponano= (tf_nano.tv_sec - ti_nano.tv_sec)*1000000000 + (tf_nano.tv_nsec - ti_nano.tv_nsec);
		printf("crear un hijo y ejecutar la tarea tardo:%g us | %g ns \n", tiemponano/1000,tiemponano);
		
		//realizamos lo mismo pero con la llamada system()
		clock_gettime(CLOCK_REALTIME, &ti_nano);  // Instante inicial
		system("./salida");
		clock_gettime(CLOCK_REALTIME, &tf_nano);  // Instante final
		tiemponano= (tf_nano.tv_sec - ti_nano.tv_sec)*1000000000 + (tf_nano.tv_nsec - ti_nano.tv_nsec);
		printf("Realizar la misma tarea pero ejecutada con la llamada system sin crear otro hijo tardo:%g us | %g ns \n", tiemponano/1000,tiemponano);
		
	}
	else
	{
		execvp("./salida", NULL);
		printf("Return not expected. Must be an execv error \n");
	}
}
