#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int i;
	double aux;
	FILE *file;
    file = fopen ("salida.txt", "w" );
 
	for( i = 0; i < 1000; i++)
	{
		 aux=2.5*4.3;
		fprintf(file, "Soy el proceso hijo con pid:%i\n",getpid());
	}
	fprintf(file, "Finalizo el ciclo, mi pid = %i \n", getpid());
	fclose(file);

	return 0;
}