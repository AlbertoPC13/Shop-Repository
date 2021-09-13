#ifndef NODOPRODUCTOS_H
#define NODOPRODUCTOS_H
/**********************************************************
Declara un nodo con una liga
**********************************************************/
#include "err.h"
/***************C O N S T A N T E S************************/
#define DATO_Productos producto *
#define FORMATOVirtual " %p"
#define TAMMAX        1000
/*************** T I P O     D E     D A T O*****************/
typedef struct
{
  char nombre_producto[TAMMAX];
  int num_existencia;
  char nombre_proveedor[TAMMAX];
} producto;
typedef struct _nodoProductos
{
  DATO_Productos dato;
  struct _nodoProductos *sig;
} nodoProductos;
typedef nodoProductos *apnodoProductos;
/***************F U N C I O N E S *****************************/
int crea_nodProductos(apnodoProductos *p, DATO_Productos d); /*Crear un nodo*/
int elim_nodProductos(apnodoProductos *p);                /*Eliminar un nodo*/
char *str_nodProductos(char *, const apnodoProductos);    /*Convertir nodo a cadena*/
#endif
