#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>

#define BACKLOG 10 /* Tamaño de la cola de conexiones recibidas */
#define PORT 13490	/* Puerto del servidor */ 
#define MAXDATASIZESHORT 4
#define MAXDATASIZESOLIC 32
#define MAXDATASIZELARGE 2048

double tiempo;
struct timeval ti, tf;    //Structuras para medir el tiempo
int sockdesc; //Descriptor socket: El servidor escuchara por sockdesc 
int sockclient; //  Descriptor socket cliente: las transferencias de datos se realizar mediante sockclient 
struct sockaddr_in my_addr; // contendra la direccion IP y el numero de puerto	local 
struct sockaddr_in client_addr; // Contendra la direccion IP y numero de puerto del cliente 
char buf[MAXDATASIZESOLIC]; //Buffer donde se reciben las solicitudes de cliente 

int newfd;
char cuento[MAXDATASIZELARGE] = "<<<<<<<<<<<<<<<<<ACA ESTA EL MENSAJE LARGO>>>>>>>>>>>>>>>>>>>>";

int* status;
int sin_size = sizeof(struct sockaddr_in*);

int crearSocketServer(struct sockaddr_in* my_address, int port)
{
	int sockfd;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) /*Crea un socket y verifica si hubo algun error*/
	{
		perror("socket");
		return (-1);
	}
	
	/* Asignamos valores a la estructura my_addr para luego poder llamar a la funcion bind() */
	my_address->sin_family = AF_INET;
	my_address->sin_port = htons(port); /* Puerto: debe convertirse a network byte order */
	my_address->sin_addr.s_addr = INADDR_ANY; /* automaticamente usa la IP local */
	
	bzero(&(my_address->sin_zero), 8); 

	
	/* Le asignamos un nombre al socket */
	if (bind(sockfd, (struct sockaddr *) my_address, sizeof(struct sockaddr)) < 0)
	{
		perror("ERROR bind");
		close(sockfd);
		return (-2);
	}
	printf("[Servidor: Socket TPC creado. Port %d ]\n",ntohs(my_address->sin_port));
	
	/* Habilitamos el socket para recibir conexiones, definiendo el tamaño de la cola de espera de conexiones */
	if (listen(sockfd, BACKLOG) < 0)
	{
		perror("ERROR listen");
		close(sockfd);
		return (-3);
	}

	return sockfd;
}

int aceptarConexion(int sockfd,struct sockaddr_in* their_addr)
{	
	printf("[Servidor: a la espera de conexiones de clientes]\n");
	
	/*Se espera por conexiones ,*/
	if ((newfd = accept(sockfd, (struct sockaddr *)their_addr, &sin_size)) == -1)
	{
		perror("ERROR accept");
		return (-1);
	}
	printf("[Servidor: acepta conexion desde: %s, puerto %d]\n", (char*)inet_ntoa(their_addr->sin_addr), ntohs(their_addr->sin_port));
	
	return newfd;
}

int recibir(int sock, char* buf, int longitud)
{
	int numbytes;	
	if ((numbytes=recv(sock, buf, longitud, 0)) == -1)
	{
		perror("ERROR recv");
		return (-1);
	}
	return numbytes;
}

int enviar(int sock, char* buf, int longitud)
{
	if (send(sock, buf, longitud, 0) == -1)
	{
		perror("ERROR send");
		return(-1);
	}
	return 0;
}

main()
{

	sockdesc = crearSocketServer(&my_addr,PORT); //Crea el socket, inicializa la direccion y realiza el bind y listen
	if (sockdesc < 0){
		printf("El servidor no puede arrancar \n");
		exit(1);
	}
	while(1) /* Se esperan conexiones */
	{
		sockclient = aceptarConexion(sockdesc, &client_addr);
		
		if (!fork()){ 
		// Proceso hijo, recibe y envia datos mediante sockclient 
			enviar(sockclient, "Conexión Aceptada", MAXDATASIZESOLIC); 
				
			if (recibir(sockclient,buf,MAXDATASIZESOLIC) >= 0){
				gettimeofday(&ti, NULL);   // Instante inicial
				enviar(sockclient, cuento, MAXDATASIZELARGE);
				gettimeofday(&tf, NULL);   // Instante final
				tiempo= (tf.tv_sec - ti.tv_sec)*1000000 + (tf.tv_usec - ti.tv_usec);
				printf("Tiempo para atender el mensaje largo %g microsegundos.\n\n",tiempo);
				}
			if (recibir(sockclient,buf,MAXDATASIZESOLIC) >= 0){
				gettimeofday(&ti, NULL);   // Instante inicial
				enviar(sockclient, "Mensaje Corto", MAXDATASIZESHORT);
				gettimeofday(&tf, NULL);   // Instante final
				tiempo= (tf.tv_sec - ti.tv_sec)*1000000 + (tf.tv_usec - ti.tv_usec);
				printf("Tiempo para atender el mensaje largo %g microsegundos.\n\n",tiempo);
}
			close(sockclient);
			exit(0);
		}
      close(sockclient);
		/* Se suspende la ejecucion del proceso padre hasta que finalice el proceso hijo */
		wait(status);
		printf("\n");
	
	}
}


