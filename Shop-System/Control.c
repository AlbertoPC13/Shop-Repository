#include "Control.h"

/*La funcion creaUsuarios se encarga de obtener los datos de usuario del archivo usuarios.txt y crea una lista de usuarios
Retorna:
users: lista de usuarios*/
listaUsuarios crearUsuarios()
{
    char nombre[TAMMAX];
    char password[TAMMAX];
    char tipo[TAMMAX];

    FILE *f;
    f = fopen("usuarios.txt", "r");

    int j;

    listaUsuarios users;
    crea_lisUsuarios(&users);

    usuario *user;
    int i;
    while (!feof(f))
    {
        user = (usuario *)malloc((i + 1) * sizeof(usuario));
        //Limpieza del arreglo
        bzero(nombre, TAMMAX - 1);
        char aux;
        aux = '\0';
        for (j = 0; aux != '-'; j++)
        {
            aux = fgetc(f);
            if (aux != '-')
                nombre[j] = aux;
        }
        strcpy(user[i].nombre_usuario, nombre);

        bzero(password, TAMMAX - 1);
        char aux2;
        aux2 = '\0';
        for (j = 0; aux2 != '-'; j++)
        {
            aux2 = fgetc(f);
            if (aux2 != '-')
                password[j] = aux2;
        }
        strcpy(user[i].password, password);

        bzero(tipo, TAMMAX - 1);
        char aux3;
        aux3 = ' ';
        for (j = 0; aux3 != '\n' && !feof(f); j++)
        {
            aux3 = fgetc(f);
            if (aux3 != '-')
                tipo[j] = aux3;
        }

        user[i].tipo_usuario = atoi(tipo);
        user[i].sesion_activa = 0;

        insf_lisUsuarios(&users, &user[i]);
        i++;
    }
    fclose(f);

    return users;
}

/*La funcion creaProductos se encarga de obtener los datos de usuario del archivo productos.txt y crea una lista de usuarios
Retorna:
users: lista de usuarios*/
listaProductos crearProductos()
{
    char nombre[TAMMAX];
    char proveedor[TAMMAX];
    char numEx[TAMMAX];
    int j, i;

    FILE *f;
    f = fopen("productos.txt", "r");

    listaProductos productos;
    crea_lisProductos(&productos);
    producto *prod;
    while (!feof(f))
    {
        prod = (producto *)malloc((i + 1) * sizeof(producto));
        bzero(nombre, TAMMAX - 1);
        char aux;
        aux = '\0';
        for (j = 0; aux != '-'; j++)
        {
            aux = fgetc(f);
            if (aux != '-')
                nombre[j] = aux;
        }
        strcpy(prod[i].nombre_producto, nombre);

        bzero(proveedor, TAMMAX - 1);
        char aux2;
        aux2 = '\0';
        for (j = 0; aux2 != '-'; j++)
        {
            aux2 = fgetc(f);
            if (aux2 != '-')
                proveedor[j] = aux2;
        }
        strcpy(prod[i].nombre_proveedor, proveedor);

        bzero(numEx, TAMMAX - 1);
        char aux3;
        aux3 = ' ';
        for (j = 0; aux3 != '\n' && !feof(f); j++)
        {
            aux3 = fgetc(f);
            if (aux3 != '-')
                numEx[j] = aux3;
        }

        prod[i].num_existencia = atoi(numEx);

        insf_lisProductos(&productos, &prod[i]);
        i++;
    }
    fclose(f);

    return productos;
}

int actualizar_Productos(char *s)
{
    FILE *f;
    f = fopen("productos.txt", "w");
    fprintf(f, "%s", s);
    fclose(f);
    return OK;
}

/* La funcion crearCarritos crea los nodos de la listaCarritos a partir del archivo txt correspondiente.*/
listaCarrito crearCarritos()
{
    char nombre[TAMMAX];
    char proveedor[TAMMAX];
    char numEx[TAMMAX];
    char cliente[TAMMAX];
    char fecha[TAMMAX];
    char ID[TAMMAX];

    int j, i;

    FILE *f;
    f = fopen("carritos.txt", "r");

    listaCarrito carritos;
    crea_lisCarrito(&carritos);
    carrito *car;

    while (!feof(f))
    {
        //Obtencion del nombre de producto
        car = (carrito *)malloc((i + 1) * sizeof(carrito));
        bzero(nombre, TAMMAX - 1);
        char aux;
        aux = '\0';
        for (j = 0; aux != '-'; j++)
        {
            aux = fgetc(f);
            if (aux != '-')
                nombre[j] = aux;
        }
        strcpy(car[i].nombre_producto, nombre);

        //Obtencion del nombre del proveedor
        bzero(proveedor, TAMMAX - 1);
        char aux2;
        aux2 = '\0';
        for (j = 0; aux2 != '-'; j++)
        {
            aux2 = fgetc(f);
            if (aux2 != '-')
                proveedor[j] = aux2;
        }
        strcpy(car[i].nombre_proveedor, proveedor);

        //Obtencion del numero de existencias
        bzero(numEx, TAMMAX - 1);
        char aux3;
        aux3 = '\0';
        for (j = 0; aux3 != '-'; j++)
        {
            aux3 = fgetc(f);
            if (aux3 != '-')
                numEx[j] = aux3;
        }

        car[i].cantidad = atoi(numEx);

        //Obtenciondel nnombre del cliente
        bzero(cliente, TAMMAX - 1);
        char aux4;
        aux4 = '\0';
        for (j = 0; aux4 != '-'; j++)
        {
            aux4 = fgetc(f);
            if (aux4 != '-')
                cliente[j] = aux4;
        }
        strcpy(car[i].nombre_cliente, cliente);

        //Obtencion de la fecha
        bzero(fecha, TAMMAX - 1);
        char aux5;
        aux5 = '\0';
        for (j = 0; aux5 != '-'; j++)
        {
            aux5 = fgetc(f);
            if (aux5 != '-')
                fecha[j] = aux5;
        }
        strcpy(car[i].fecha, fecha);

        //Obtencion del ID
        bzero(ID, TAMMAX - 1);
        char aux6;
        aux6 = ' ';
        for (j = 0; aux6 != '\n' && !feof(f); j++)
        {
            aux6 = fgetc(f);
            if (aux6 != '-')
                ID[j] = aux6;
        }

        car[i].ID_compra = atoi(ID);

        //Insercion del nodo en la listaCarrito
        insf_lisCarrito(&carritos, &car[i]);
        i++;
    }
    fclose(f);

    return carritos;
}
