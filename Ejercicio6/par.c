#include "socket.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

char buf[MSG_SIZE];
void Preguntas(char * mensaje);
char * ingresarMensaje();
void mostrar(char * msg);
void Menu();
void MostrarFuncionamiento();
void nombreMaquina(char * mensaje);
void horaMaquina(char * mensaje);
void Clima(char * mensaje);

int main(int argc, char **argv)
{
    char * amigo;
    char * mensaje;
    char * puerto;
    //controlamos la cantidad de parametros ingresada
    if(argc<3 || argc>3)
    {
		printf("Cantidad de parametros invalido, debe ingresar <IP AMIGO,PUERTO> -\n"); 
		exit(1);
    }
    
    amigo=argv[1];
    puerto = argv[2];
    MostrarFuncionamiento();
   if ( amigoConectado(amigo, puerto)){//Modo cliente
	while(1)
	{
            Menu();
	    mensaje = ingresarMensaje();
	    if(strcmp(mensaje,"5\n")==0){
		enviarMsj(mensaje);
		break;
	    }
            enviarMsj(mensaje);
            mensaje = recibirMsj();
            mostrar(mensaje);
            mensaje = recibirMsj();
            if(strcmp(mensaje,"5\n")==0)
                break;
            Preguntas(mensaje);
            enviarMsj(mensaje);
	}
		cerrarSesion();
    }
    else //Modo Servidor
    {
        iniciarServicio(puerto); 
	while(1){
	    mensaje = recibirMsj();
	    if(strcmp(mensaje,"5\n")==0)
		break;
	    Preguntas(mensaje);
	    enviarMsj(mensaje);
	    Menu();
            mensaje = ingresarMensaje();
	    	if(strcmp(mensaje,"5\n")==0)
                {
                    enviarMsj(mensaje);
                    break;
                }
	    	enviarMsj(mensaje);
	    	mensaje = recibirMsj();
	    	mostrar(mensaje);
		}
		cerrarSesion();
    }
    exit(0);
}


//Lee desde la consola los caracteres necesarios
char * ingresarMensaje()
{
    buf[0]='\0';
    printf("[SD2014]$");
    //lee hasta el caracter MSG_SIZE escrito en consola
    fgets(buf, MSG_SIZE+1, stdin);
    return buf;
}

/** Muestra el mensaje recibido **/
void mostrar(char * msg)
{
    printf("> %s\n",msg);
}

//Muestra las posibles preguntas que se pueden hacer
void Menu()
{
    printf("\n################¿QUE INFORMACION DESEA OBTENER DEL PROCESO AMIGO?#################\n");
	printf("1- Los usuarios logueados del sistema\n2- La hora del sistema S\n3- Nombre de la maquina\n4- Temperatura de la localidad donde esta ubicado\n-Cualquier otra tecla'Salir'\n \n");	
}
//explica el funcionamiento del programa
void MostrarFuncionamiento()
{
   printf("\nEsta aplicacion funciona de manera tal que cada uno de los pares se intercambian las preguntas, es decir que cada par no puede hacer dos preguntas seguidas, para hacer la segunda pregunta se debe esperar a que me pregunte el otro par \n\n\n");	
}

//Nos devuelve el nombre de la maquina
void nombreMaquina(char * mensaje){

	if(gethostname(mensaje, 255)<0)
	{
		printf("Error al obtener el hostname.-\n");
		exit(1);
	}
}

//Nos devuelve la hora del sistema
void horaMaquina(char * mensaje)
{
    char * tiempo;
	time_t t;
	struct tm * tiem;
	t = time(NULL);
	tiem= localtime(&t);
	strftime(mensaje, 10, "%H:%M:%S", tiem);

}

//Nos devuelve el clima
void Clima(char * mensaje)
{
    char temp [MSG_SIZE] = "Hacen 26 Grandos en la ciudad\n";
    strcpy(mensaje, temp);
}

//Nos informa de los usuarios logueados en el sistema
void usuariosLogueados(char * mensaje)
{
FILE * log;
    char linea [100];
    system("who > usuarios.sd");
    log = fopen ("usuarios.sd" , "r");

    strcpy(mensaje, "");

    while( fgets(linea, 100, log) != NULL ){
        strcat( mensaje, linea);
    }
    system("rm usuarios.sd");
    fclose(log);
}

//Es la encargada de ver que pergunta es la que me hicieron y llama al procedimiento correspondiente
void Preguntas(char * mensaje)
{
    if(strcmp(mensaje, "1\n")==0)
        usuariosLogueados(mensaje);
    else if(strcmp(mensaje, "2\n")==0)
	horaMaquina(mensaje);
    else if(strcmp(mensaje, "3\n")==0)
	nombreMaquina(mensaje);
    else if(strcmp(mensaje, "4\n")==0)
             Clima(mensaje);
    else
         strcpy(mensaje, "Opcion invalida");    
}

