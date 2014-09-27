#define MSG_SIZE         512 //tamaño del mensaje
#define MAXBUF           1025

//verifico si hay un amigo ya conectado y si es asi se inicia como cliente
int amigoConectado (char *hostname, char * port);

// Envio un mensaje al amigo
void enviarMsj (char* msj);

//Recibo un mensaje del amigo
char* recibirMsj ();

//Inicio una conexion como servidor para que luego se conecte e amigo
void iniciarServicio ();

//cerrar la conexion con el amigo
int cerrarSesion ();