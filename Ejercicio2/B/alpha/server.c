#include "ej2b.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <limits.h>
#include <unistd.h>
#include <sys/resource.h>

int* ejecutartarea_1_svc(int* opcion,struct svc_req* req)
{	
	static int toReturn = 0;
	int op = *opcion;
	if(op == 1) //creo proceso hijo y le cargo la imagen.
	{
		int p_hijo = fork();

		if(p_hijo >= 0)
			if(p_hijo == 0) //hijo
             			execlp("tarea",NULL);//cargamos la tarea en el proceso hijo
			else
				wait(0); //esperando al hijo
		else
		{
			toReturn = -1; //ERROR al crear el proceso hijo
			return &(toReturn);
		}
	}
	else //realizo la tarea con system.
	   system("./tarea");
	return  &toReturn;
}
