#include "nodoUsuarios.h"
/* Convierte un nodo en una cadena
Recibe:
  Cadena que almacenara la representacion del nodo
  Apuntador a nodo a ser convertido
Regresa:
  El mismo apuntador que recibe
*/
char *str_nodUsuarios(char *s, const apnodoUsuarios ap)
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
int crea_nodUsuarios(apnodoUsuarios *p, DATO_Usuarios d)
{
  if (!AP_VAL(p))
    return AP_INV;
  *p = (nodoUsuarios *)malloc(sizeof(nodoUsuarios));
  if (!AP_VAL(*p))
    return NO_MEM;
  (*p)->dato = d;
  (*p)->sig = NULL;
  return OK;
}
/* Elimina un nodo
Recibe
  Apuntador a nodo a ser eliminado
Regresa
  Codigo de error
*/
int elim_nodUsuarios(apnodoUsuarios *p)
{
  if (!AP_VAL(p))
    return AP_INV;
  free(*p);
  *p = NULL;
  return OK;
}
