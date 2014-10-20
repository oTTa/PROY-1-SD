all :
	rpcgen -C ej2b.x
	gcc -o tarea tarea.c
	gcc -o server ej2b_svc.c server.c -lnsl
	gcc -o cliente ej2b_clnt.c cliente.c -lnsl 
