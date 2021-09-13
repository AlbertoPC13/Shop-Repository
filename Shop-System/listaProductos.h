#ifndef LISTAPRODUCTOS_H
#define LISTAPRODUCTOS_H
/**********************************************************
Implementa una lista utilizando nodos de una liga.
**********************************************************/
#include "nodoProductos.h"
/*****************M A C R O S*******************************/
#define TIE_DAT(p)  ((p)!=NULL)   /*Si tiene datos*/
#define VAC_LIS(p)  ((p)==NULL)   /* Si es un lista vacia*/
/***************T I P O     D E     D A T O****************/
typedef apnodoProductos listaProductos;
/************** F U N C I O N E S**************************/
int crea_lisProductos(listaProductos* l); /*Inicializa la lista Productos*/
int insf_lisProductos(listaProductos*,DATO_Productos); /*Inserta el ultimo nodo*/
int dest_lisProductos(listaProductos*);      /*Elimina por completo una lista*/
int inse_lisProductos(listaProductos*,int,DATO_Productos);/*inserta nuevos nodos en la lista Productos*/
listaProductos ante_lisProductos(listaProductos, int); /*Determina el nodo anterior a la posicion p de la lista Productos*/
int long_lisProductos(listaProductos*);      /*Calcula la longitud de la lista*/
int buscar_lisProductos(listaProductos *l, char* nombre_producto,char* nombre_proveedor);/*Busca la pagina en la lista*/
int elim_lisProductos(listaProductos*,int);  /*Saca un elemento del lista*/
int elip_lisProductos(listaProductos*);      /*Elimina el primer dato*/
char *str_lisProductos(char *s, listaProductos *l);
int dis_existencias(listaProductos* l, char* nombre_producto,char* nombre_proveedor, int art_comprados);
#endif

