#ifndef LISTACARRITO_H
#define LISTACARRITO_H
/**********************************************************
Implementa una lista utilizando nodos de una liga.
**********************************************************/
#include "nodoCarrito.h"
/*****************M A C R O S*******************************/
#define TIE_DAT(p)  ((p)!=NULL)   /*Si tiene datos*/
#define VAC_LIS(p)  ((p)==NULL)   /* Si es un lista vacia*/
/***************T I P O     D E     D A T O****************/
typedef apnodoCarrito listaCarrito;
/************** F U N C I O N E S**************************/
int crea_lisCarrito(listaCarrito* l); /*Inicializa la lista Carrito*/
int insf_lisCarrito(listaCarrito*,DATO_Carrito); /*Inserta el ultimo nodo*/
int dest_lisCarrito(listaCarrito*);      /*Elimina por completo una lista*/
int inse_lisCarrito(listaCarrito*,int,DATO_Carrito);/*inserta nuevos nodos en la lista Carrito*/
listaCarrito ante_lisCarrito(listaCarrito, int); /*Determina el nodo anterior a la posicion p de la lista Carrito*/
int long_lisCarrito(listaCarrito*);      /*Calcula la longitud de la lista*/
int buscar_lisCarrito(listaCarrito *l, char* datos_buscado);/*Busca la pagina en la lista*/
int elim_lisCarrito(listaCarrito*,int);  /*Saca un elemento del lista*/
int elip_lisCarrito(listaCarrito*);      /*Elimna el primer dato*/
char *str_lisCarrito(char *s, listaCarrito *l);
#endif

