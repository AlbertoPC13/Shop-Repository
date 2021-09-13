#ifndef QUEUEMENSAJE_H
#define QUEUEMENSAJE_H
#include "listaUsuarios.h"
#include "listaProductos.h"
#include "listaCarrito.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/sem.h>

typedef struct
{
  long pid; //ID del proceso
  int orden; //Indica el numero de pedido realizado por un usuario
  usuario user;
  producto prod;
  char CLAVE_SEM;
} mensaje;

#define LONGITUD (sizeof(mensaje)-sizeof(long))

  //producto product[TAMMAX];
  //char clave_sem;
/**********OPCIONES************/
#define SESION          1  
#define VER_PRODUCTOS   2
#define BUY_PRODUCTOS   3
#define ADD_PRODUCTOS   4
#define MOD_PRODUCTOS   5
#define HIS_PRODUCTOS   6
#define FIN             7
#define ERROR           8
#define INICIADO        9
/******************************/

/**********CONSTANTES*********/
#define PERMISOS 0666
#define FICHERO_LLAVE "Control"
#define FICHERO_MEMORIA_PRODUCT "File1"
#define FICHERO_MEMORIA_CARRITO "File2"
#define FICHERO_SEMAFORO "Semaforo"
#define CLAVE_USER_CONTROL  'K'
#define CLAVE_CONTROL_USER  'L'
#define CLAVE_MEMORIA_PRODUCT       'M'
#define CLAVE_MEMORIA_CARRITO       'J'

/******************************/

/**********FUNCIONES************/
void menu();
/******************************/
#endif