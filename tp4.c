#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tarea {
    int TareaID;
    char *Descripcion;
    int Duracion;
};

typedef struct tarea Tarea;

struct nodo {
    Tarea T;
    struct nodo *siguiente;
};

typedef struct nodo Nodo;
typedef Nodo *Lista;

void mostrarMenu();
Lista crearLista();
void insertarNodo(Lista *l, Lista n);
void cargaDeTarea(Lista *l,int *contador);
void borrarTarea(Lista *l, int idTarea);
void mostrarTareas(Lista l);
void realizarTarea(Lista *l1, Lista *l2, int idTarea);
void liberarTarea(Lista *l);
void buscaTareaId(Lista l, int id);
void buscaTareaPalabra(Lista l, char *palabra);

int main() {
    Lista tareasPen, tareasRe;
    int opcion = 0, contador = 0, idTarea;
    char palabra[30];

    tareasPen = crearLista();
    tareasRe = crearLista();

    do {
        mostrarMenu();
        printf("\nElija una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                int bandera = 0;
                do {
                    cargaDeTarea(&tareasPen, &contador);
                    printf("\nDesea continuar cargando Tareas? (si: 1 | no: 0): ");
                    scanf("%d", &bandera);
                } while (bandera == 1);
                break;

            case 2:
                printf("\n-----------Tareas PENDIENTES----------\n");
                mostrarTareas(tareasPen);
                break;

            case 3:
                printf("\nEscriba el ID de la tarea que desea marcar como realizada: ");
                scanf("%d", &idTarea);
                realizarTarea(&tareasPen, &tareasRe, idTarea);
                break;

            case 4:
                printf("\n-----------Tareas REALIZADAS----------\n");
                mostrarTareas(tareasRe);
                break;

            case 5:
                printf("\nIngrese el ID de la tarea Pendiente a buscar: ");
                scanf("%d", &idTarea);
                buscaTareaId(tareasPen, idTarea);
                break;

            case 6:
                printf("\nIngrese la palabra clave de la tarea Pendiente a buscar: ");
                fflush(stdin);
                fgets(palabra, sizeof(palabra), stdin);
                palabra[strcspn(palabra, "\n")] = '\0';
                buscaTareaPalabra(tareasPen, palabra);
                break;

            case 7:
                printf("\nIngrese el ID de la tarea Realizada a buscar: ");
                scanf("%d", &idTarea);
                buscaTareaId(tareasRe, idTarea);
                break;

            case 8:
                printf("\nIngrese la palabra clave de la tarea Realizada a buscar: ");
                // fflush(stdin);
                // fgets(palabra, sizeof(palabra), stdin);
                // palabra[strcspn(palabra, "\n")] = '\0';
                // buscaTareaPalabra(tareasRe, palabra);
                break;

            case 9:
                printf("\nIngrese el ID de la tarea Pendiente a quitar: ");
                scanf("%d", &idTarea);
                borrarTarea(&tareasPen, idTarea);
                break;

            case 10:
                return 0;

            default:
                printf("\nNo ingresaste una opcion valida");
                break;
        }

    } while (opcion != 10);

    liberarTarea(&tareasPen);
    liberarTarea(&tareasRe);

    return 0;
}

void mostrarMenu() {
    printf("\n");
    printf("1. Cargar Tarea/s Pendiente/s\n");
    printf("2. Mostrar Tarea/s Pendiente/s\n");
    printf("3. Marcar como tarea realizada\n");
    printf("4. Mostrar Tarea/s Realizada/s\n");
    printf("5. Buscar tarea Pendiente por ID\n");
    printf("6. Buscar tarea Pendiente por palabra clave\n");
    printf("7. Buscar tarea Realizada por ID\n");
    printf("8. Buscar tarea Realizada por palabra clave\n");
    printf("9. Quitar tarea pendiente\n");
    printf("10. Salir\n");
}

Lista crearLista() {
    return NULL;
}

void insertarNodo(Lista *l, Lista n) {
    n->siguiente = *l;
    *l = n;
}

void cargaDeTarea(Lista *l, int *contador) {
    Lista tareaAux = (Lista)malloc(sizeof(struct nodo));
    printf("\nTarea numero %d", *contador);
    tareaAux->T.TareaID = *contador;
    tareaAux->T.Descripcion = (char *)malloc(sizeof(char) * 30);
    printf("\nIngresar descripcion: ");
    fflush(stdin);
    fgets(tareaAux->T.Descripcion, 30, stdin);
    tareaAux->T.Duracion = rand() % 91 + 10;
    insertarNodo(l, tareaAux);
    (*contador)++;
}

void borrarTarea(Lista *l, int idTarea) {
    Lista aux = *l;
    Lista anterior = NULL;

    while (aux != NULL && aux->T.TareaID != idTarea) {
        anterior = aux;
        aux = aux->siguiente;
    }

    if (aux == NULL) {
        printf("\nNo existe la tarea a borrar");
        return;
    }

    if (anterior == NULL) {
        *l = aux->siguiente;
    } else {
        anterior->siguiente = aux->siguiente;
    }

    free(aux->T.Descripcion);
    free(aux);
    printf("\nSe ha borrado la tarea exitosamente");
}

void mostrarTareas(Lista l) {
    Lista aux = l;
    while (aux != NULL) {
        printf("\n\nNumero de Tarea: %d", aux->T.TareaID);
        printf("\nDescripcion: %s", aux->T.Descripcion);
        printf("\nDuracion: %d", aux->T.Duracion);
        aux = aux->siguiente;
    }
}

void realizarTarea(Lista *l1, Lista *l2, int idTarea) {
    Lista aux1 = *l1;
    
    if (*l1 == NULL)
    {
        printf("\nNo hay tareas en Tareas Pendientes");
    }else
    {
        Lista aux2;
        while (aux1 != NULL && aux1->T.TareaID != idTarea )
        {
            aux2 = aux1;
            aux1 = aux1->siguiente;
        }
        if (aux1 == NULL)
        {
            printf("\nNo existe la tarea a realizar");
            return;
        }else
        {
            if (aux2 == NULL)
            {
                    *l1 = aux1->siguiente;
            }
            else
            {
                    aux2->siguiente = aux1->siguiente;
            }
            insertarNodo(l2, aux1);   
            printf("Tarea marcada como realizada.\n");
        }
        
    }
}

void liberarTarea(Lista *l) {
    Lista aux;
    while (*l != NULL) {
        aux = *l;
        *l = aux->siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}

void buscaTareaId(Lista l, int id) {
    Lista aux = l;
    while (aux != NULL) {
        if (aux->T.TareaID == id) {
            printf("\n\nNumero de Tarea: %d", aux->T.TareaID);
            printf("\nDescripcion: %s", aux->T.Descripcion);
            printf("\nDuracion: %d", aux->T.Duracion);
            return;
        }
        aux = aux->siguiente;
    }
    printf("\nNo se encontro la tarea.\n");
}

void buscaTareaPalabra(Lista l, char *palabra) {
    Lista aux = l;
    while (aux != NULL) {
        if (strstr(aux->T.Descripcion, palabra) != NULL) {
            printf("\n\nNumero de Tarea: %d", aux->T.TareaID);
            printf("\nDescripcion: %s", aux->T.Descripcion);
            printf("\nDuracion: %d", aux->T.Duracion);
            return;
        }
        aux = aux->siguiente;
    }
    printf("\nNo se encontró la tarea.\n");
}
