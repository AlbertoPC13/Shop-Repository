#include "Control.h"
#include "queueMensaje.h"

int main(int argc, char const *argv[])
{
    /*identificadores de las colas y procesos*/
    int cola_userctrl, cola_ctrluser, pid;
    int opcion;
    int id = 0;
    mensaje msg;
    key_t llave;

    /*listas a generar*/
    listaCarrito carritos;
    listaUsuarios users;
    listaProductos productos;
    /*cadenas que se usaran a lo largo del programa*/
    char cadUsers[TAMMAX];
    char *cadProductos;
    char *cadCarrito;
    /*Creacion de llave para ser usada en cola de mensajes de usuario a control*/
    llave = ftok(FICHERO_LLAVE, CLAVE_USER_CONTROL);
    if (llave == -1)
    {
        printf("La llave no fue creada");
        exit(0);
    }
    /*Obtencion del identificador de la cola de mensajes de los usuarios*/
    if ((cola_userctrl = msgget(llave, IPC_CREAT | PERMISOS)) == -1)
    {
        //En caso de que el proceso de creacion del identificador de la cola de mensajes tenga un error.
        perror("El identificador de cola de mensajes de usuarios no fue creado");
        exit(-1);
    }
    /*Creacion de llave para cola de mensajes de control a usuario*/
    llave = ftok(FICHERO_LLAVE, CLAVE_CONTROL_USER);

    /*Obtencion del identificador de la cola de mensajes del programa de control*/
    if ((cola_ctrluser = msgget(llave, IPC_CREAT | PERMISOS)) == -1)
    {
        //En caso de que el proceso de creacion del identificador de la cola de mensajes tenga un error.
        perror("El identificador de cola de mensajes de control no fue creado");
        exit(-1);
    }

    users = crearUsuarios();
    //Impresión de la lista de usuarios
    str_lisUsuarios(cadUsers, &users);
    printf("\n %s", cadUsers);

    //Creacion de memoria compartida de la cadena de Productos
    int shmid;
    llave = ftok(FICHERO_MEMORIA_PRODUCT, CLAVE_MEMORIA_PRODUCT);
    shmid = shmget(llave, sizeof(char *), IPC_CREAT | PERMISOS);
    cadProductos = shmat(shmid, 0, 0);

    /*Memoria compartida para Carrito*/
    int shmid2;
    llave = ftok(FICHERO_MEMORIA_CARRITO, CLAVE_MEMORIA_CARRITO);
    shmid2 = shmget(llave, sizeof(char *), IPC_CREAT | PERMISOS);
    cadCarrito = shmat(shmid2, 0, 0);

    /*se crea lista de productos a partir del .txt*/
    productos = crearProductos();

    while (1)
    {
        /*Recepcion de mensajes de la cola usuario-control, el mensaje se guarda en &msg*/
        msgrcv(cola_userctrl, &msg, LONGITUD, 0, 0);
        char a[TAMMAX];
        printf("%d", msg.orden);
        switch (msg.orden)
        {
        case SESION:
            printf("\nEl usuario: %lu solicito iniciar sesion\n", msg.pid);
            //Validación de que el usuario exista
            if (validar_lisUsuarios(&users, msg.user.nombre_usuario, msg.user.password, msg.user.tipo_usuario) < 0)
            {
                //En caso de no encontrar los datos de usuario ingresados
                msg.orden = ERROR;
                printf("\nEl usuario no fue encontrado:\n");
                printf("nombre:%d\n", msg.user.tipo_usuario);
            }
            else
            {
                //En caso de que si se encuentren los datos de usuario ingresados
                msg.orden = INICIADO;
                msg.CLAVE_SEM = CLAVE;
                printf("\nEl usuario fue encontrado\n");
            }
            //Regresar mensaje para indicar que fue recibido correctamente
            msgsnd(cola_ctrluser, &msg, LONGITUD, 0);
            break;

        case VER_PRODUCTOS:
            //Fin indica la recepcion exitosa del mensaje
            msg.orden = FIN;
            strcpy(cadProductos, "");
            str_lisProductos(cadProductos, &productos);
            printf("\n %s", cadProductos);
            printf("\nEl usuario: %lu solicito ver productos\n", msg.pid);
            msgsnd(cola_ctrluser, &msg, LONGITUD, 0);
            break;

        case BUY_PRODUCTOS:
            printf("\nEl usuario: %lu solicito comprar productos\n", msg.pid);
            msg.orden = FIN;
            /*Si hay suficientes existencias del articulo la compra procede*/
            if (dis_existencias(&productos, msg.prod.nombre_producto, msg.prod.nombre_proveedor, msg.prod.num_existencia) > 0)
            {
                FILE *car;
                time_t t;
                struct tm *tm;
                char fechayhora[100];
                /*Obtencion de la fecha exacta cuando se realizo la compra*/
                t = time(NULL);
                tm = localtime(&t);
                strftime(fechayhora, 100, "%d/%m/%Y %H:%M", tm);

                car = fopen("carritos.txt", "a");
                if (car == NULL)
                    printf("Hubo un error al abrir el archivo .txt");
                fprintf(car, "\n%s-%s-%d-%s-%s-%05d", msg.prod.nombre_producto, msg.prod.nombre_proveedor, msg.prod.num_existencia, msg.user.nombre_usuario, fechayhora, ++id);
                //Nombre del producto – Nombre de proveedor – Cantidad – Nombre de cliente – Fecha – ID de compra

                fclose(car);
                carritos = crearCarritos();
                strcpy(cadCarrito, "");
                str_lisCarrito(cadCarrito, &carritos);
                printf("\n %s", cadCarrito);

                strcpy(cadProductos, "");
                str_lisProductos(cadProductos, &productos);
                actualizar_Productos(cadProductos);
            }
            else
            {
                printf("\nNo esta el producto o no hay suficientes\n");
                msg.orden = ERROR;
            }
            /*se envia el mensaje a la cola*/
            msgsnd(cola_ctrluser, &msg, LONGITUD, 0);
            break;
            /*Agregar productos al stock*/
        case ADD_PRODUCTOS:
            printf("\nEl usuario: %lu solicito agregar productos\n", msg.pid);
            msg.orden = FIN; //Solicitud recibida
            productos = crearProductos();
            strcpy(cadProductos, "");
            str_lisProductos(cadProductos, &productos); //Mostrar listado de productos
            /*se envia el mensaje a la cola*/
            msgsnd(cola_ctrluser, &msg, LONGITUD, 0);
            break;
            /*Modificar productos*/
        case MOD_PRODUCTOS:
            printf("\nEl usuario: %lu solicito modificar productos\n", msg.pid);
            if (buscar_lisProductos(&productos, msg.prod.nombre_producto, msg.prod.nombre_proveedor))
            {
                msg.orden = FIN;
                dis_existencias(&productos, msg.prod.nombre_producto, msg.prod.nombre_proveedor, (-1) * msg.prod.num_existencia);
                strcpy(cadProductos, "");
                str_lisProductos(cadProductos, &productos);
                actualizar_Productos(cadProductos);
            }
            else
            {
                msg.orden = ERROR;
            }
            /*se envia el mensaje a la cola*/
            msgsnd(cola_ctrluser, &msg, LONGITUD, 0);
            break;
            /*Historial de productos*/
        case HIS_PRODUCTOS:
            msg.orden = FIN;
            strcpy(cadCarrito, "");
            str_lisCarrito(cadCarrito, &carritos);
            printf("\n %s", cadCarrito);
            printf("\nEl usuario: %lu solicito ver carrito de compras\n", msg.pid);
            msgsnd(cola_ctrluser, &msg, LONGITUD, 0);
            break;
            /*Caso que indica la existencia de errores*/
        case ERROR:
            msg.orden = ERROR;
            printf("\nHa ocurrido un error :c\n");
            /*se envia el mensaje a la cola*/
            msgsnd(cola_ctrluser, &msg, LONGITUD, 0);
            break;

        case FIN:
            /*Al finalizar, se cierra la cola de mensajes*/
            msgctl(cola_userctrl, IPC_RMID, 0);
            msgctl(cola_ctrluser, IPC_RMID, 0);
            printf("\nLa cola de mensajes ha finalizado\n");
            exit(0);
            break;
        }
    }

    return 0;
}