#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(char *argv[])
{
	struct timeval timeInicio, timeFin;
	long total, usegInicio, usegFin;
	int pid;

	total = 0;

	gettimeofday(&timeInicio,0);
	pid = fork();

	if (pid != 0)
	{
		wait(pid);
		gettimeofday(&timeFin,0);
		
		usegInicio = ((timeInicio.tv_sec * 1000000) + timeInicio.tv_usec);	
		usegFin = ((timeFin.tv_sec * 1000000) + timeFin.tv_usec);

		total =usegFin - usegInicio;
		printf("Tardo un total de %d us \n", total);
	}
	else
	{
		execvp("./salida", NULL);
		printf("Return not expected. Must be an execv error \n");
	}
}
