#ifndef NODOUSUARIOS_H
#define NODOUSUARIOS_H
/**********************************************************
Declara un nodo con una liga
**********************************************************/
#include "err.h"
#include <stdio.h>
#include <string.h>
#define TAMMAX 1000
/***************C O N S T A N T E S************************/
#define DATO_Usuarios usuario*
#define FORMATOVirtual " %p"
/*************** T I P O     D E     D A T O*****************/
typedef struct
{
  char nombre_usuario[TAMMAX];
  char password[TAMMAX]; //Contrasenia de inicio de sesion
  int tipo_usuario; //Indica si el usuario es comprador o vendedor
  int sesion_activa; //Indica si el usuario ha iniciado sesion
} usuario;
typedef struct _nodoUsuarios
{
  DATO_Usuarios dato;
  struct _nodoUsuarios *sig;
} nodoUsuarios;
typedef nodoUsuarios *apnodoUsuarios;
/***************F U N C I O N E S *****************************/
int crea_nodUsuarios(apnodoUsuarios *p, DATO_Usuarios d); /*Crear un nodo*/
int elim_nodUsuarios(apnodoUsuarios *p);                /*Eliminar un nodo*/
char *str_nodUsuarios(char *, const apnodoUsuarios);    /*Convertir nodo a cadena*/
#endif
