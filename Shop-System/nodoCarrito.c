#include "nodoCarrito.h"
/* Convierte un nodo en una cadena
Recibe:
  Cadena que almacenara la representacion del nodo
  Apuntador a nodo a ser convertido
Regresa:
  El mismo apuntador que recibe
*/
char *str_nodCarrito(char *s, const apnodoCarrito ap)
{
  if (!(AP_VAL(s) && AP_VAL(ap)))
    return s;
  sprintf(s, FORMATOVirtual, ap->dato);
  return s;
}
/* Inicializa un nodo
Recibe:
  Apuntador a nodo a ser inicializado
  Dato para inicializar el nodo
Regresa
  Codigo de error
*/
int crea_nodCarrito(apnodoCarrito *p, DATO_Carrito d)
{
  if (!AP_VAL(p))
    return AP_INV;
  *p = (nodoCarrito *)malloc(sizeof(nodoCarrito));
  if (!AP_VAL(*p))
    return NO_MEM;
  (*p)->dato = d;
  (*p)->sig = NULL;
  return OK;
}
/* Elimina un nodo
Recive
  Apuntador a nodo a ser eliminado
Regresa
  Codigo de error
*/
int elim_nodCarrito(apnodoCarrito *p)
{
  if (!AP_VAL(p))
    return AP_INV;
  free(*p);
  *p = NULL;
  return OK;
}
