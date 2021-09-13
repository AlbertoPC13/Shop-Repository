#ifndef NODOCARRITO_H
#define NODOCARRITO_H
/**********************************************************
Declara un nodo con una liga
**********************************************************/
#include "err.h"
#include <stdio.h>
#include <string.h>
/***************C O N S T A N T E S************************/
#define DATO_Carrito carrito *
#define FORMATOVirtual " %p"
#define TAMMAX        1000
/*************** T I P O     D E     D A T O*****************/
typedef struct
{
  char nombre_producto[TAMMAX];
  char nombre_proveedor[TAMMAX];
  int cantidad;
  char nombre_cliente[TAMMAX];
  char fecha[TAMMAX];
  int ID_compra;
} carrito;
typedef struct _nodoCarrito
{
  DATO_Carrito dato;
  struct _nodoCarrito *sig;
} nodoCarrito;
typedef nodoCarrito *apnodoCarrito;
/***************F U N C I O N E S *****************************/
int crea_nodCarrito(apnodoCarrito *p, DATO_Carrito d); /*Crear un nodo*/
int elim_nodCarrito(apnodoCarrito *p);                /*Eliminar un nodo*/
char *str_nodCarrito(char *, const apnodoCarrito);    /*Convertir nodo a cadena*/
#endif
