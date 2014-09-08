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

int socketfd, numbytes; 

char buf0[MAXDATASIZESOLIC], buf1[MAXDATASIZELARGE], buf2[MAXDATASIZESHORT]; /* Buffers donde se reciben y mandan los datos */

struct hostent * he; /* Se utiliza para convertir el nombre del host a su dirección IP */

struct sockaddr_in serv_addr; /* dirección del server donde se conectara */


int crearSocketCliente(struct sockaddr_in* serv_addr, int port, struct hostent* he)
{
	int sockdesc;
	
	/* Creamos el socket */
	if ((sockdesc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("ERROR socket");
		return(-1);
	}
	/* Establecemos serv_addr con la dirección del server */
	serv_addr->sin_family = AF_INET;
	serv_addr->sin_port = htons(port);
	serv_addr->sin_addr = *((struct in_addr *)he->h_addr);
	
	bzero(&(serv_addr->sin_zero), 8);

	printf("[Cliente: Socket TCP creado]\n");

	return sockdesc;

}

int conectarCliente(int sockfd,struct sockaddr_in* server_addr)
{
  /* Intentamos conectarnos con el servidor */
	if (connect(sockfd, (struct sockaddr *)server_addr, sizeof(struct sockaddr)) < 0)
	{
//		perror("ERROR connect");
		return(-1);
	}
	printf("[Cliente: Conexión establecida con el servidor IP %s, port %d] \n",(char*)inet_ntoa(server_addr->sin_addr),ntohs(server_addr->sin_port));

	return (0);
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


int main(int argc,char *argv[])
{
  if (argc != 2)
	{
		fprintf(stderr,"uso: client hostname\n");
		exit(1);
	}
	if ((he=gethostbyname(argv[1])) == NULL)
	{
		printf("Error con el hostname");
		exit(1);
	}

	if ((socketfd = crearSocketCliente(&serv_addr,PORT,he)) < 0) //Creamos el socket y nos fijamos si fue posible
	{
		printf("Imposible crear el cliente. \n");
		exit(1);
	}	

	printf("Conectado\n");
	while(conectarCliente(socketfd, &serv_addr) != 0i);
	if ((numbytes = recibir(socketfd, buf0, MAXDATASIZESOLIC)) < 0)
	{
		printf("No se puede recibir el mensaje\n\n");
	}
	buf0[numbytes] = '\0';
	
	printf("\nRecibimos: %s \n\n", buf0);

	printf("Presione Intro:");
	getchar();
	//Pedimos el mensaje de 2048 bytes	
	if (enviar(socketfd, "Quiero un mensaje largo", MAXDATASIZESOLIC) < -1)
	{
		printf("No se puede contactar con el servidor\n\n");
	}
	else
	{
		
	
		printf("Solicito el mensaje largo al servidor \n");
		
		gettimeofday(&ti, NULL);   // Instante inicial
	
		if ((numbytes = recibir(socketfd, buf1, MAXDATASIZELARGE)) < -1)
		{
			printf("No se recibió ninguna respuesta\n\n");
		}
		
		gettimeofday(&tf, NULL);   // Instante final
	  	tiempo= (tf.tv_sec - ti.tv_sec)*1000000 + (tf.tv_usec - ti.tv_usec);
		buf1[numbytes] = '\0';
		
		printf("Tiempo de espera del cliente para el mensaje largo %g microsegundos.\n\n",tiempo);
	}
	printf("Presione Intro");
	getchar();

	/* Envia mensaje de solicitud, y recibe dato de 4 bytes */
	if (enviar(socketfd, "Solicito mensaje corto", MAXDATASIZESOLIC) < -1)
	{
		printf("No se puede contactar con el servidor\n\n");
	}
	else
	{
		printf("Solicito al servidor el mensaje corto\n");
	
		gettimeofday(&ti, NULL);   // Instante inicial
	
		if ((numbytes=recibir(socketfd, buf2, MAXDATASIZESHORT)) == -1)
		{
			printf("No se recibió ninguna respuesta\n\n");
		}
		gettimeofday(&tf, NULL);   // Instante final
  		tiempo= (tf.tv_sec - ti.tv_sec)*1000000 + (tf.tv_usec - ti.tv_usec);
		buf2[numbytes] = '\0';
		printf("Tiempo de espera del cliente para el mensaje corto: %g microsegundos.\n\n",tiempo);
	}

	/* Devolvemos recursos al sistema */
	close(socketfd);

	return 0;
  
}