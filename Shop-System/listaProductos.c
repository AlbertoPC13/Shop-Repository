#include "listaProductos.h"

/*La funcion crea_lisProductos se encarga de inicializar la lista Productos.
Recibe: 
listaProductos *l: apuntador a la lista que almacenara los Productos registrados.
Retorna:
OK en en caso de exito
Diferente de OK en caso de error */
int crea_lisProductos(listaProductos *l)
{
  if (!AP_VAL(l))
    return AP_INV;
  *l = NULL;
  return OK;
}
/*La funcion dest_lisProductos destruye la lista Productos mediante la liberacion de memoria de los nodos que la forman.
Recibe:
listaProductos * l: lista a destruira.
Retorna:
OK en en caso de exito
Diferente de OK en caso de error
*/
int dest_lisProductos(listaProductos *l)
{
  if (!AP_VAL(l))
    return AP_INV;
  while (!VAC_LIS(*l))
    elip_lisProductos(l);
  return OK;
}
/*La funcion ante_lisProductos determina el nodo anterior a la posicion p de la lista Productos.
Recibe:
listaProductos: lista cuyo nodo anterior sera obtenido
int p: posicion de la cual se obtendra su nodo anterior.
Retorna: nodo anterior*/
listaProductos ante_lisProductos(listaProductos l, int p)
{
  listaProductos aux, ant;
  int pos;
  aux = l;
  ant = aux;
  pos = 0;
  while (aux && pos < p)
  {
    ant = aux;
    aux = aux->sig;
    pos++;
  }
  return ant;
}
/*La funcion long_lisProductos determina la longitud de la lista Productos.
Recibe: 
listaProductos *l: lista cuya longitud se determinara 
Retorna: longitud de la lista*/
int long_lisProductos(listaProductos *l)
{
  int cont;
  listaProductos aux;
  if (!AP_VAL(l))
    return AP_INV;
  cont = 0;
  aux = *l;
  while (aux)
  {
    cont++;
    aux = aux->sig;
  }
  return cont;
}

/*La funcion inse_lisProductos inserta nuevos nodos en la lista Productos.
Recibe:
listaProductos *l: lista a la que se le agregara el nodo
int pos: la posicion en la que se agregará el nodo
DATOProductos D: dato que se almacenara en dicho nodo.
Retorna:
OK en en caso de exito
Diferente de OK en caso de error*/
int inse_lisProductos(listaProductos *l, int pos, DATO_Productos d)
{
  apnodoProductos nuevo;
  listaProductos aux;
  if (!AP_VAL(l))
    return AP_INV;
  if (!(pos <= long_lisProductos(l) && pos >= 0))
    return POS_INV;
  if (!(crea_nodProductos(&nuevo, d) == OK))
    return OVERFLOW;
  aux = ante_lisProductos(*l, pos);
  nuevo->sig = aux->sig;
  aux->sig = nuevo;
  return OK;
}

/*La funcion ulti_lisProductos regresa el ultimo nodo de la lista.
Recibe: 
listaProductos l: lista cuyo ultimo nodo se buscara 
Retorna:
ultimo nodo de la lista*/
listaProductos ulti_lisProductos(const listaProductos l)
{
  listaProductos aux, ant;
  aux = l;
  ant = aux;
  while (aux)
  {
    ant = aux;
    aux = aux->sig;
  }
  return ant;
}

/*La funcion insf_lisProductos inserta un nodo al final de la lista Productos.
Recibe:
listaProductos *l: lista en la que se realizara la operacion de insercion
DATOProductos: dato a insertar 
Retorna:
 OK en en caso de exito
Diferente de OK en caso de error*/
int insf_lisProductos(listaProductos *l, DATO_Productos d)
{
  apnodoProductos nuevo, aux;
  if (!AP_VAL(l))
    return AP_INV;
  aux = *l;
  if (!(crea_nodProductos(&nuevo, d) == OK))
    return OVERFLOW;
  if (VAC_LIS(aux)) /*Si la lista esta vacia*/
    (*l) = nuevo;
  else
  {
    aux = ulti_lisProductos(*l);
    aux->sig = nuevo;
  }
  return OK;
}

/* La funcion elim_lisProductos saca el elemento de la posicion pos de la lista Productos. 
Recibe:
listaProductos *l: lista en la que se realizara la operacion de eliminacion
Int pos: posicion que determina el nodo a eliminar.
Retorna:
 OK en en caso de exito
Diferente de OK en caso de error*/
int elim_lisProductos(listaProductos *l, int pos)
{
  listaProductos aux, borrar;
  if (!AP_VAL(l))
    return AP_INV;
  if (!TIE_DAT(*l))
    return UNDERFLOW;
  if (!(pos <= long_lisProductos(l) && pos > 0))
    return POS_INV;

  aux = ante_lisProductos(*l, pos);
  if (aux->sig)
  {
    borrar = aux->sig;
    aux->sig = borrar->sig;
    free(borrar);
  }
  return OK;
}

/*La funcion elip_lisProductos se encarga de borrar el primer nodo de la lista Productos.
Recibe: 
listaProductos *l cuyo primer nodo sera borrado
Retorna:
OK en en caso de exito
Diferente de OK en caso de error*/
int elip_lisProductos(listaProductos *l)
{
  apnodoProductos borrar;
  if (!AP_VAL(l))
    return AP_INV;
  if (!TIE_DAT(*l))
    return UNDERFLOW;
  borrar = *l;
  *l = (*l)->sig;
  free(borrar);
  return OK;
}
/*La funcion str_lisProductos convierte a cadena la lista Productos, para que esta pueda ser visualizada
Recibe:
listaProductos *l: apuntador a la lista Productos cuya cadena sera formada
char *s: apuntador a caracter que almacenara la cadena 
Devuelve:
char *str_lisProductos: cadena resultante 
*/

char *str_lisProductos(char *s, listaProductos *l)
{
  char aux[TAMMAX + 1];
  char aux1[TAMMAX + 1];
  char aux2[TAMMAX + 1];
  listaProductos l1, l2;
  l2 = NULL;
  l1 = *l;
  while (l1)
  {
    sprintf(aux, "%s", l1->dato->nombre_producto);
    strcat(s, aux);
    sprintf(aux1, "-%s", l1->dato->nombre_proveedor);
    strcat(s, aux1);
    sprintf(aux2, "-%d", l1->dato->num_existencia);
    strcat(s, aux2);
    if(l1->sig != NULL)
      strcat(s, "\n");
    l2 = l1;
    l1 = l1->sig;
  }
  return s;
}

/* La funcion buscar_lisProductos se encarga de buscar un dato en una lista.
Recibe:
listaProductos *l: lista en la que debe buscar
char *nombre_producto: nombre de producto que se busca.
char *nombre_proveedor: nombre de proveedor que se busca.
Regresa:posicion del dato buscado.*/
int buscar_lisProductos(listaProductos *l, char *nombre_producto, char* nombre_proveedor)
{
  if (!AP_VAL(l))
    return AP_INV;
  if (!TIE_DAT(*l))
    return UNDERFLOW;

  listaProductos l1, l2;
  //l2 es una lista auxiliar
  int i = 0;
  l2 = NULL;
  l1 = *l;
  while (l1)
  {
    if (strcmp(nombre_producto,l1->dato->nombre_producto)==0 && strcmp(nombre_proveedor,l1->dato->nombre_proveedor)==0)
      return i;
    else
    {
      l2 = l1;
      l1 = l1->sig;
      i++;
    }
  }
  return NO_EXISTE;
}
/*dis_existencias: disminuye el numero de existencias de un articulo en una unidad.
Para identificar el articulo cuya existencia será disminuida se utiliza el nombre del producto y el proveedor.
Recibe: 
listaProductos: lista en la que se encuentra el producto cuya existencia sera modificada
char* nombre_producto: nombre del producto que se busca
char* nombre_proveedor: nombre del proveedor que se busca
*/
int dis_existencias(listaProductos *l, char *nombre_producto, char *nombre_proveedor, int art_comprados)
{
  if (!AP_VAL(l))
    return AP_INV;
  if (!TIE_DAT(*l))
    return UNDERFLOW;

  listaProductos l1, l2;
  //l2 es una lista auxiliar
  int i = 0;
  l2 = NULL;
  l1 = *l;
  while (l1)
  {
    //En caso de que el articulo buscado sea encontrado
    if (strcmp(nombre_producto, l1->dato->nombre_producto) == 0 && strcmp(nombre_proveedor, l1->dato->nombre_proveedor) == 0)
    {
      if (art_comprados > l1->dato->num_existencia)
      {
        printf("\nCantidad invalida :'c\n");
        return CANT_INV;
      }
      else
      {
        //El numero de existencias del articulo disminuira en funcion de la cantidad de elementos comprados

        l1->dato->num_existencia = l1->dato->num_existencia - art_comprados;
        return i;
      }
    }
    else
    {
      l2 = l1;
      l1 = l1->sig;
      i++;
    }
  }
  return NO_EXISTE;
}
