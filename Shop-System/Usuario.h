#ifndef USUARIO_H
#define USUARIO_H
#include "queueMensaje.h"
/***************variables globales semaforo************/
key_t llave_sem;
int semaforo;
/****************FUNCIONES*****************/
/*imprime menu*/
void menu();
/*inica sesion del usuario*/
usuario ini_sesion();
/************SEMAFOROS***************/
/*crea los semaforos*/
int Crea_semaforo(key_t llave, int valor_inicial);
/*bloquea el semaforo*/
void down(int semid);
/*desbloquea el semaforo*/
void up(int semid);
#endif