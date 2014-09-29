#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	struct timeval timeInicio, timeFin;
	long total, usegInicio, usegFin;
	int pid;

	total = 0;

	gettimeofday(&timeInicio,0);
	pid = fork();

	if (pid != 0)
	{
		wait(0);
		gettimeofday(&timeFin,0);// Instante final
		usegInicio = ((timeInicio.tv_sec * 1000000) + timeInicio.tv_usec);	
		usegFin = ((timeFin.tv_sec * 1000000) + timeFin.tv_usec);
		total =usegFin - usegInicio;
		printf("crear un hijo y ejecutar la tarea tardo:%ld us \n", total);
		
		//realizamos lo mismo pero con la llamada system()
		gettimeofday(&timeInicio,0);
		system("./salida");
		gettimeofday(&timeFin,0);// Instante final
		usegInicio = ((timeInicio.tv_sec * 1000000) + timeInicio.tv_usec);	
		usegFin = ((timeFin.tv_sec * 1000000) + timeFin.tv_usec);
		total =usegFin - usegInicio;
		printf("Realizar la misma tarea pero ejecutada con la llamada system sin crear otro hijo tardo:%ld us  \n", total);
		
	}
	else
	{
		execvp("./salida", NULL);
		printf("Return not expected. Must be an execv error \n");
	}
	return 0
}
