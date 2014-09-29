 
 
 #include <sys/shm.h>
 
 
 /*Datos para obtener la clave unica*/
#define enteroCompartido 2
#define archivoCompartido "/bin/ls"

key_t clave;
int memory_id;
int semaforo_cliente;
int semaforo_servidor;

typedef struct msj
{
	int operacion;
	char resultado[100];
} msj;

msj *memoria;

//retorna la clave generada a partir de file e int.
int obtenerClave(char *file, int i)
{
	clave = ( ftok ( file, i) );
	if( clave == -1)
	{
		printf("No se pudo obtener la clave para la memoria compartida\n");
		exit(0);
	}
	return clave;
}

//Si esta creada solo obtenemos el id (omitiendo poner IPC_CREAT).
//Retorna 1 si la creo, otro valor caso contrario.
int crearMemoria()
{
	//intento obtener id de una memoria ya creada, caso contrario, la creo
	memory_id = ( shmget (clave, sizeof(struct msj), 0777 ) );
	if( memory_id == -1)
	{
		//creo la memoria compartida.
		memory_id = ( shmget (clave, sizeof(struct msj) , 0777 | IPC_CREAT) );
		return 1;
	}
	if( memory_id == -1)
	{
		printf("ID");
		printf("ERROR en la creacion de la memoria. Abortando...\n");
		exit(0);
	}
	return 0;
}

//Con el id obtenido, direccionamos la memoria a un puntero a int.
void direccionarMemoria()
{
	memoria  = (msj *)shmat (memory_id, (char *)0, 0);
	if( memoria == NULL)
	{
		printf("[CLNT]No se pudo obtener la memoria\n");
		exit(0);
	}
}

//Procedimiento para eliminar la memoria compartida.
//La deberia eliminar el proceso creador.
void eliminarMemoria();