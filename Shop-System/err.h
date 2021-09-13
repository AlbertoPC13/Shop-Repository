#ifndef ERR_H
#define ERR_H
/**********************************************************
Definir errores comunes a programas
**********************************************************/
#include <stdlib.h> /* Para definir NULL */
#include <stdio.h>
#include <string.h>
/*****************C O N S T A N T E S*************************/
#define OK 0         /* No hay errores */
#define AP_INV 1     /* Recibe un apuntador nulo */
#define NO_MEM 2     /* malloc regresa NULL*/
#define OVERFLOW 30  /* Si no hay memoria*/
#define UNDERFLOW 31 /* En casos de lista o cola vacia*/
#define POS_INV 32   /* Posicion invalida */
#define TAMDAT 10
#define NO_EXISTE -2 /* El dato buscado no existe*/
#define CANT_INV -3 /*Cantidad invalid*/

/****************M A C R O S***********************/
/* Verifica que un apuntador no tenga direccion nula*/
#define AP_VAL(p) ((p) != NULL)
#endif
