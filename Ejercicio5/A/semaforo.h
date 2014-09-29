 
/*
Definicion e implementacion de semaforo
*/
#ifndef SEMAFORO_H_INCLUDED
#define SEMAFORO_H_INCLUDED

# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/sem.h>

union semun {
  int val;
}arg;

int crearSemaforo(int key){
  return(semget(key, 1, IPC_CREAT|0666));
}

int asociarseSemaforo(int key){
  return(semget(key,1,0));
}

int initSemaforo(int semid, int valor){
  arg.val = valor;
  if (semctl(semid, 0, SETVAL, arg)==-1){return(-1);}
  else{return(0);}
}

int signal(int semid){
  struct sembuf operacion;
  operacion.sem_num = 0;
  operacion.sem_op = 1;
  operacion.sem_flg = 0;
  if (semop(semid, &operacion, 1)==-1){return(-1);}
  else{return(0);}
}

int wait(int semid){
  struct sembuf operacion;
  operacion.sem_num = 0;
  operacion.sem_op = -1;
  operacion.sem_flg = 0;
  if (semop(semid, &operacion, 1)==-1){return(-1);}
  else{return(0);}
}


#endif // SEMAFORO_H_INCLUDED