#include "nodoProductos.h"
/* Convierte un nodo en una cadena
Recibe:
  Cadena que almacenara la representacion del nodo
  Apuntador a nodo a ser convertido
Regresa:
  El mismo apuntador que recibe
*/
char *str_nodProductos(char *s, const apnodoProductos ap)
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
int crea_nodProductos(apnodoProductos *p, DATO_Productos d)
{
  if (!AP_VAL(p))
    return AP_INV;
  *p = (nodoProductos *)malloc(sizeof(nodoProductos));
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
int elim_nodProductos(apnodoProductos *p)
{
  if (!AP_VAL(p))
    return AP_INV;
  free(*p);
  *p = NULL;
  return OK;
}
