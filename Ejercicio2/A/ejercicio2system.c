#include <sys/time.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(char *argv[])
{
	struct timeval timeInicio, timeFin;
	long total, usegInicio, usegFin;
	total = 0;

	gettimeofday(&timeInicio,0);
	system("./salida");
	gettimeofday(&timeFin,0);
		
	usegInicio = ((timeInicio.tv_sec * 1000000) + timeInicio.tv_usec);	
	usegFin = ((timeFin.tv_sec * 1000000) + timeFin.tv_usec);

	total =usegFin - usegInicio;
	printf("Tardo un total de %d us \n", total);
	
}
 
