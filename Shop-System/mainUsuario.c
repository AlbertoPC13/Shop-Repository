#include "Usuario.h"
int main(int argc, char const *argv[])
{
    int cola_userctrl, cola_ctrluser, pid;
    listaCarrito lisCarritoDani;
    listaUsuarios users;
    listaProductos productos;
    char cadUsers[TAMMAX];
    char *cadProductos;
    char *cadCarrito;

    mensaje msg;
    key_t llave;
    enum
    {
        NO,
        SI
    } recibir = NO;

    /*Creacion de las colas de mensajes*/
    llave = ftok(FICHERO_LLAVE, CLAVE_USER_CONTROL);

    if ((cola_userctrl = msgget(llave, IPC_CREAT | PERMISOS)) == -1)
    {
        perror("msget");
        exit(-1);
    }

    llave = ftok(FICHERO_LLAVE, CLAVE_CONTROL_USER);

    if ((cola_ctrluser = msgget(llave, IPC_CREAT | PERMISOS)) == -1)
    {
        perror("msget");
        exit(-1);
    }
    /*Memoria compartida para Productos*/
    int shmid;
    llave = ftok(FICHERO_MEMORIA_PRODUCT, CLAVE_MEMORIA_PRODUCT);
    shmid = shmget(llave, sizeof(char *), IPC_CREAT | PERMISOS);
    cadProductos = shmat(shmid, 0, 0);
    msg.pid = pid = getpid();

    /*Memoria compartida para Carrito*/
    int shmid2;
    llave = ftok(FICHERO_MEMORIA_CARRITO, CLAVE_MEMORIA_CARRITO);
    shmid2 = shmget(llave, sizeof(char *), IPC_CREAT | PERMISOS);
    cadCarrito = shmat(shmid2, 0, 0);

    usuario userActual;
    while (1)
    {
        menu();
        int orden;
        printf("\nEscribe la opcion que desees:\n");
        scanf(" %d", &orden);
        switch (orden)
        {
            /*Caso para iniciar sesion*/
        case SESION:
            recibir = SI;
            msg.orden = orden;
            userActual = ini_sesion();
            msg.user = userActual;
            /*Impresion de los datos de usuario (nombre de usuario, constraseña, tipo de usuariom*/
            printf("nombre:%s\n", msg.user.nombre_usuario);
            printf("pass:%s\n", msg.user.password);
            printf("tipo:%d\n", msg.user.tipo_usuario);
            msgsnd(cola_userctrl, &msg, LONGITUD, 0);
            break;
            /*Visualizacion de los productos en stock*/
        case VER_PRODUCTOS:
            /*Se bloquea el semaforo*/
            down(semaforo);
            if (userActual.sesion_activa)
            {
                /*Visualizacion de los productos en stock*/
                recibir = SI;
                msg.orden = orden;
                printf("\n%s\n", cadProductos);
            }
            else
            {
                /*Error cuando el usuario no ha iniciado sesion*/
                recibir = SI;
                msg.orden = ERROR;
                printf("\nNo has iniciado sesion -_-\n");
            }
            msgsnd(cola_userctrl, &msg, LONGITUD, 0);
            break;
            /*Comprar productos*/
        case BUY_PRODUCTOS:
            /*Se bloquea el semaforo*/
            down(semaforo);
            /*Se verifica que se haya iniciado sesion y que el usuario sea un cliente*/
            if (userActual.sesion_activa && !userActual.tipo_usuario)
            {
                char producto[TAMMAX];
                char proveedor[TAMMAX];
                int numEx;

                recibir = SI;
                msg.orden = orden;
                /*Recepcion de datos ingresados por el usuario ára señalar que articulo desea comprar*/
                strcpy(msg.user.nombre_usuario, userActual.nombre_usuario);
                strcpy(producto, "");
                strcpy(proveedor, "");
                printf("\nEscribe el nombre del producto: ");
                scanf("%s", producto);
                strcpy(msg.prod.nombre_producto, producto);
                printf("\nEscribe el nombre del proveedor: ");
                scanf("%s", proveedor);
                strcpy(msg.prod.nombre_proveedor, proveedor);
                printf("\nEscribe la cantidad deseada: ");
                scanf("%d", &numEx);
                msg.prod.num_existencia = numEx;
            }
            else
            {
                /*Error arrojado por el sistema cuando un usuario desea comprar articulos sin antes iniciar sesion*/
                recibir = SI;
                msg.orden = ERROR;
                printf("\nNo has iniciado sesion o no eres Cliente\n");
            }
            msgsnd(cola_userctrl, &msg, LONGITUD, 0);
            break;
            /*Agregar productos, para ello se necesita que el usuario sea de tipo proveedor*/
        case ADD_PRODUCTOS:
            /*Se bloquea el semaforo*/
            down(semaforo);
            /*Se verifica que se haya iniciado sesion y que tenga los permisos necesarios*/
            if (userActual.sesion_activa && userActual.tipo_usuario)
            {
                FILE *f;
                f = fopen("productos.txt", "a");
                char continuar = 's';
                char nombre[TAMMAX];
                int numEx;

                recibir = SI;
                msg.orden = orden;
                /*Se le solicita al usuario que ingrese el producto, su cantidad y si desea agregar otro producto*/
                do
                {
                    printf("\nEscribe el nombre del producto: ");
                    scanf("%s", nombre);

                    printf("\nEscribe la cantidad: ");
                    scanf("%d", &numEx);
                    /*Los datos ingresados, se agregan en el archivo .txt*/
                    fprintf(f, "\n%s-%s-%d", nombre, userActual.nombre_usuario, numEx);

                    printf("\n¿Quiere agregar otro producto? s/n: ");
                    scanf("%s", &continuar);
                } while (continuar == 's');
                fclose(f);
            }
            else
            {
                /*En caso que no se haya iniciado sesion, se enviaria al Control que hubo un error*/
                recibir = SI;
                msg.orden = ERROR;
                printf("\nNo has iniciado sesion o no tienes los permisos para realizar la accion\n");
            }
            msgsnd(cola_userctrl, &msg, LONGITUD, 0);
            break;
            /*Modificar productos*/
        case MOD_PRODUCTOS:
            /*Se bloquea el semaforo*/
            down(semaforo);
            /*Se verifica que se haya iniciado sesion y que tenga los permisos necesarios*/
            if (userActual.sesion_activa && userActual.tipo_usuario)
            {
                char producto[TAMMAX];
                int numEx;
                recibir = SI;
                msg.orden = orden;
                /*Recopilacion de datis necesarios para identificar al articulo a modificar y los datos que seran reemplazados*/
                strcpy(producto, "");
                printf("\nEscribe el nombre del producto: ");
                scanf("%s", producto);
                strcpy(msg.prod.nombre_producto, producto);
                strcpy(msg.prod.nombre_proveedor, userActual.nombre_usuario);
                printf("\nEscribe la cantidad a incrementar: ");
                scanf("%d", &numEx);
                msg.prod.num_existencia = numEx;
            }
            else
            {
                /*Error arrojado cuando un usuario intenta modificar articulos y no ha iniciado sesion o no es un proveedor*/
                recibir = SI;
                msg.orden = ERROR;
                printf("\nNo has iniciado sesion o no tienes los permisos para realizar la accion\n");
            }
            msgsnd(cola_userctrl, &msg, LONGITUD, 0);
            break;
            /*Historial de productos del usuario*/
        case HIS_PRODUCTOS:
            if (userActual.sesion_activa)
            {
                recibir = SI;
                msg.orden = orden;
                printf("\n%s\n", cadCarrito);
            }
            else
            {
                /*Error arrojado cuando un usuario intenta acceder al historial de compras y no ha iniciado sesion*/
                recibir = SI;
                msg.orden = ERROR;
                printf("\nno has iniciado sesion\n");
            }
            msgsnd(cola_userctrl, &msg, LONGITUD, 0);
            break;

        case FIN:
            recibir = NO;
            msg.orden = FIN;
            msgsnd(cola_userctrl, &msg, LONGITUD, 0);
            break;

        default:
            recibir = NO;
            printf("no se reconoce\n");
            break;
        }

        if (recibir == SI)
        {
            do
            {
                /*recibe las respuestas del programa control*/
                msgrcv(cola_ctrluser, &msg, LONGITUD, pid, 0);

                switch (msg.orden)
                {
                case FIN:
                    /*Se desbloquea el semaforo*/
                    up(semaforo);
                    break;

                case ERROR:
                    up(semaforo);
                    printf("\nQue hubo un error dice\n");
                    break;

                case INICIADO:
                    /*Si se inicio correctamente, se activa la sesion y se obtiene el semaforo del programa Control*/
                    userActual.sesion_activa = 1;
                    printf("\nInicio correctamente\n");
                    printf("\nsemaforo %c\n", msg.CLAVE_SEM);
                    /*Se actualiza la llave del semaforo*/
                    llave_sem = ftok(FICHERO_SEMAFORO, msg.CLAVE_SEM);
                    /*se crea el semaforo*/
                    semaforo = Crea_semaforo(llave_sem, 1);
                    break;
                default:
                    printf("no se reconoce\n");
                    break;
                }
            } while (!msg.orden);
        }
    }

    return 0;
}
