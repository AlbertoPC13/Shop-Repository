#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H
/**********************************************************
Implementa una lista utilizando nodos de una liga.
**********************************************************/
#include "nodoUsuarios.h"
/*****************M A C R O S*******************************/
#define TIE_DAT(p)  ((p)!=NULL)   /*Si tiene datos*/
#define VAC_LIS(p)  ((p)==NULL)   /* Si es un lista vacia*/
/***************T I P O     D E     D A T O****************/
typedef apnodoUsuarios listaUsuarios;
/************** F U N C I O N E S**************************/
int crea_lisUsuarios(listaUsuarios* l); /*Inicializa la lista Usuarios*/
int insf_lisUsuarios(listaUsuarios*,DATO_Usuarios); /*Inserta el ultimo nodo*/
int dest_lisUsuarios(listaUsuarios*);      /*Elimina por completo una lista*/
int inse_lisUsuarios(listaUsuarios*,int,DATO_Usuarios);/*inserta nuevos nodos en la lista Usuarios*/
listaUsuarios ante_lisUsuarios(listaUsuarios, int); /*Determina el nodo anterior a la posicion p de la lista Usuarios*/
int long_lisUsuarios(listaUsuarios*);      /*Calcula la longitud de la lista*/
int buscar_lisUsuarios(listaUsuarios *l, char* datos_buscado);/*Busca la pagina en la lista*/
int elim_lisUsuarios(listaUsuarios*,int);  /*Saca un elemento del lista*/
int elip_lisUsuarios(listaUsuarios*);      /*Elimina el primer dato*/
char *str_lisUsuarios(char *s, listaUsuarios *l);

int validar_lisUsuarios(listaUsuarios *l, char* usuario, char* password, int tipo);
#endif

