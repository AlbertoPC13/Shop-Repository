#ifndef CONTROL_H
#define CONTROL_H
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include "queueMensaje.h"
#include "listaUsuarios.h"
#include "listaProductos.h"


#define CLAVE       'S'

/**********FUNCIONES************/
listaUsuarios crearUsuarios();
listaProductos crearProductos();
int actualizar_Productos(char *s); /*Actualiza el archivo de productos*/ 
listaCarrito crearCarritos();
/******************************/

#endif