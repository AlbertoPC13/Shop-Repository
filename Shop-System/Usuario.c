#include "Usuario.h"
/*La función Menu, muestra las distintas opciones que puede seleccionar el usuario*/
void menu()
{
    printf("\n------------Menu-----------\n\n");
    printf("Selecciona una opcion\n\n");
    printf("1 Iniciar sesión\n");
    printf("2 Ver los productos\n");
    printf("3 Comprar un producto\n");
    printf("4 Agregar un producto\n");
    printf("5 Modificar un producto\n");
    printf("6 Mostrar historial de compras \n");
    printf("7 Finalizar programa\n");
    printf("\n----------------------------\n\n");
}

/*Funcion ini_sesion, solicita al usuario los datos para el ingreso al sistema
Retorna:
user: una estructura de usuario
*/
usuario ini_sesion()
{
    usuario user;
    char nombre_usuario[TAMMAX];
    char password[TAMMAX];
    int tipo_usuario=0;;
    strcpy(nombre_usuario,"");
    strcpy(password,"");
    printf("\nEscribe el nombre de usuario: ");
    scanf("%s", nombre_usuario);
    strcpy(user.nombre_usuario,nombre_usuario);

    printf("\nEscribe el password: ");
    scanf("%s", password);
    strcpy(user.password,password);

    printf("\nEscribe el tipo de usuario: ");
    scanf("%d", &tipo_usuario);
    user.tipo_usuario = tipo_usuario;
    return user;
}
//Funcion que crea el semaforo que media la secuencia de procesamiento de los procesos 
int Crea_semaforo(key_t llave, int valor_inicial)
{
    int semid = semget(llave, 1, IPC_CREAT | PERMISOS);
    if (semid == -1)
    {
        return -1;
    }
    semctl(semid, 0, SETVAL, valor_inicial);
    return semid;
}
//Funcion que decrementa el valor del semaforo. Como argumento recibe el identificador del semaforo en cuestion.
void down(int semid)
{
    struct sembuf op_p[] = {0, -1, 0};
    semop(semid, op_p, 1);
}
//Funcion que incrementa el valor del semaforo. Como argumento recibe el identificador del semaforo en cuestion.
void up(int semid)
{
    struct sembuf op_v[] = {0, +1, 0};
    semop(semid, op_v, 1);
}