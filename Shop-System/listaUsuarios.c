#include "listaUsuarios.h"

/*La funcion crea_lisUsuarios se encarga de inicializar la lista Usuarios.
Recibe: 
listaUsuarios *l: apuntador a la lista que almacenara los usuarios registrados.
Retorna:
OK en en caso de exito
Diferente de OK en caso de error */
int crea_lisUsuarios(listaUsuarios *l)
{
  if (!AP_VAL(l))
    return AP_INV;
  *l = NULL;
  return OK;
}
/*La funcion dest_lisUsuarios destruye la lista Usuarios mediante la liberacion de memoria de los nodos que la forman.
Recibe:
listaUsuarios *l: lista a destruir.
Retorna:
OK en en caso de exito
Diferente de OK en caso de error
*/
int dest_lisUsuarios(listaUsuarios *l)
{
  if (!AP_VAL(l))
    return AP_INV;
  while (!VAC_LIS(*l))
    elip_lisUsuarios(l);
  return OK;
}
/*La funcion ante_lisUsuarios determina el nodo anterior a la posicion p de la lista Usuarios.
Recibe:
listaUsuarios: lista cuyo nodo anterior sera obtenido
int p: posicion de la cual se obtendra su nodo anterior.
Retorna: nodo anterior*/
listaUsuarios ante_lisUsuarios(listaUsuarios l, int p)
{
  listaUsuarios aux, ant;
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
/*La funcion long_lisUsuarios determina la longitud de la lista Usuarios.
Recibe: 
listaUsuarios *l: lista cuya longitud se determinara 
Retorna: longitud de la lista*/
int long_lisUsuarios(listaUsuarios *l)
{
  int cont;
  listaUsuarios aux;
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

/*La funcion inse_lisUsuarios inserta nuevos nodos en la lista Usuarios.
Recibe:
listaUsuarios *l: lista a la que se le agregara el nodo
int pos: la posicion en la que se agregará el nodo
DATOUsuarios D: dato que se almacenara en dicho nodo.
Retorna:
OK en en caso de exito
Diferente de OK en caso de error*/
int inse_lisUsuarios(listaUsuarios *l, int pos, DATO_Usuarios d)
{
  apnodoUsuarios nuevo;
  listaUsuarios aux;
  if (!AP_VAL(l))
    return AP_INV;
  if (!(pos <= long_lisUsuarios(l) && pos >= 0))
    return POS_INV;
  if (!(crea_nodUsuarios(&nuevo, d) == OK))
    return OVERFLOW;
  aux = ante_lisUsuarios(*l, pos);
  nuevo->sig = aux->sig;
  aux->sig = nuevo;
  return OK;
}

/*La funcion ulti_lisUsuarios regresa el ultimo nodo de la lista.
Recibe: 
listaUsuarios l: lista cuyo ultimo nodo se buscara 
Retorna:
ultimo nodo de la lista*/
listaUsuarios ulti_lisUsuarios(const listaUsuarios l)
{
  listaUsuarios aux, ant;
  aux = l;
  ant = aux;
  while (aux)
  {
    ant = aux;
    aux = aux->sig;
  }
  return ant;
}

/*La funcion insf_lisUsuarios inserta un nodo al final de la lista Usuarios.
Recibe:
listaUsuarios *l: lista en la que se realizara la operacion de insercion
DATOUsuarios: dato a insertar 
Retorna:
 OK en en caso de exito
Diferente de OK en caso de error*/
int insf_lisUsuarios(listaUsuarios *l, DATO_Usuarios d)
{
  apnodoUsuarios nuevo, aux;
  if (!AP_VAL(l))
    return AP_INV;
  aux = *l;
  if (!(crea_nodUsuarios(&nuevo, d) == OK))
    return OVERFLOW;
  if (VAC_LIS(aux)) /*Si la lista esta vacia*/
    (*l) = nuevo;
  else
  {
    aux = ulti_lisUsuarios(*l);
    aux->sig = nuevo;
  }
  return OK;
}

/* La funcion elim_lisUsuarios saca el elemento de la posicion pos de la lista Usuarios. 
Recibe:
listaUsuarios *l: lista en la que se realizara la operacion de eliminacion
Int pos: posicion que determina el nodo a eliminar.
Retorna:
 OK en en caso de exito
Diferente de OK en caso de error*/
int elim_lisUsuarios(listaUsuarios *l, int pos)
{
  listaUsuarios aux, borrar;
  if (!AP_VAL(l))
    return AP_INV;
  if (!TIE_DAT(*l))
    return UNDERFLOW;
  if (!(pos <= long_lisUsuarios(l) && pos > 0))
    return POS_INV;

  aux = ante_lisUsuarios(*l, pos);
  if (aux->sig)
  {
    borrar = aux->sig;
    aux->sig = borrar->sig;
    free(borrar);
  }
  return OK;
}

/*La funcion elip_lisUsuarios se encarga de borrar el primer nodo de la lista Usuarios.
Recibe: 
listaUsuarios *l cuyo primer nodo sera borrado
Retorna:
OK en en caso de exito
Diferente de OK en caso de error*/
int elip_lisUsuarios(listaUsuarios *l)
{
  apnodoUsuarios borrar;
  if (!AP_VAL(l))
    return AP_INV;
  if (!TIE_DAT(*l))
    return UNDERFLOW;
  borrar = *l;
  *l = (*l)->sig;
  free(borrar);
  return OK;
}
/*La funcion str_lisUsuarios convierte a cadena la lista Usuarios, para que esta pueda ser visualizada
Recibe:
listaUsuarios *l: apuntador a la lista Usuarios cuya cadena sera formada
char *s: apuntador a caracter que almacenara la cadena 
Devuelve:
char *str_lisUsuarios: cadena resultante 
*/

char *str_lisUsuarios(char *s, listaUsuarios *l)
{
  char aux[TAMMAX+1];
  char aux1[TAMMAX+1];
  char aux2[TAMMAX+1];
  listaUsuarios l1, l2;
  l2 = NULL;
  l1 = *l;
  strcpy(s, "\nLista de usuarios\n");
  while (l1)
  {
    sprintf(aux, "%s", l1->dato->nombre_usuario);
    strcat(s, aux);
    sprintf(aux1, "-%s", l1->dato->password);
    strcat(s, aux1);
    sprintf(aux2, "-%d", l1->dato->tipo_usuario);
    strcat(s, aux2);
    strcat(s, "\n");
    l2 = l1;
    l1 = l1->sig;
  }
  return s;
} 
/* La funcion buscar_lisUsuarios se encarga de buscar un dato en una lista de Usuarios.
Recibe:
listaUsuarios *l: lista en la que debe buscar
int datos_buscado:dato que se busca.
Regresa:posicion del dato buscado.*/
int buscar_lisUsuarios(listaUsuarios *l, char* datos_buscado)
{
  if (!AP_VAL(l))
    return AP_INV;
  if (!TIE_DAT(*l))
    return UNDERFLOW;

  listaUsuarios l1, l2;
  //l2 es una lista auxiliar
  int i = 0;
  l2 = NULL;
  l1 = *l;
  while (l1)
  {
    if (datos_buscado == l1->dato->nombre_usuario)
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

/* La funcion buscar_lisUsuarios se encarga de buscar un dato en una lista de Usuarios.
Recibe:
listaUsuarios *l: lista en la que debe buscar
int datos_buscado:dato que se busca.
Regresa:posicion del dato buscado.*/
int validar_lisUsuarios(listaUsuarios *l, char* usuario, char* password, int tipo)
{
  if (!AP_VAL(l))
    return AP_INV;
  if (!TIE_DAT(*l))
    return UNDERFLOW;

  listaUsuarios l1, l2;
  //l2 es una lista auxiliar
  int i = 0;
  l2 = NULL;
  l1 = *l;
  while (l1)
  {
    
    if (strcmp(usuario,l1->dato->nombre_usuario)==0 && strcmp(password,l1->dato->password)==0 &&tipo==l1->dato->tipo_usuario){
      l1->dato->sesion_activa=1;
      return i;
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
