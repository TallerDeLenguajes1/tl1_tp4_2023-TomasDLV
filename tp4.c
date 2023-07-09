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
void mostrarDatos(Lista l);//tp5
void mostrarMenuSeleccion();

int main() {
    Lista tareasPen, tareasRe;
    Lista tareasEnProceso;//tp5 agrego tareasEnProceso
    int opcion = 0, contador = 0, idTarea;
    char palabra[30];

    tareasPen = crearLista();
    tareasRe = crearLista();
    tareasEnProceso = crearLista();//tp5

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
                printf("\n-----------Tareas EN PROCESO----------\n");
                mostrarTareas(tareasEnProceso);
                printf("\n-----------Tareas REALIZADAS----------\n");
                mostrarTareas(tareasRe);
                break;

            case 3:
                int opcion2;
                printf("\nEscriba el ID de la tarea que desea seleccionar: ");
                scanf("%d", &idTarea);
                mostrarMenuSeleccion();
                do
                {
                    printf("\nIngresa una opcion: ");
                    scanf("%d",&opcion2);
                } while (opcion2 < 1 || opcion2 > 4);
                switch (opcion2)
                {
                case 1:
                    realizarTarea(&tareasPen, &tareasRe, idTarea);
                    break;
                case 2:
                    realizarTarea(&tareasPen, &tareasEnProceso, idTarea);
                    break;
                case 3:
                    borrarTarea(&tareasPen,idTarea);
                    break;
                case 4:
                    break;
                }
                break;

            case 4:
                printf("\nDatos de Tareas PENDIENTES");
                mostrarDatos(tareasPen);
                printf("\nDatos de Tareas En PROCESO");
                mostrarDatos(tareasEnProceso);
                printf("\nDatos de Tareas REALIZADAS");
                mostrarDatos(tareasRe);
                break;

            case 5:
                return 0;

            default:
                printf("\nNo ingresaste una opcion valida");
                break;
        }

    } while (opcion != 5);

    liberarTarea(&tareasPen);
    liberarTarea(&tareasRe);

    return 0;
}

void mostrarMenu() {
    printf("\n");
    printf("1. Cargar Tarea/s Pendiente/s\n");
    printf("2. Mostrar Tareas\n");
    printf("3. Operar tarea\n");
    printf("4. Mostrar datos de las tareas\n");
    printf("5. Salir\n");
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
void mostrarDatos(Lista l){
    int contador = 0;
    int duracionTotal = 0;
    Lista aux = l;
    while (aux != NULL)
    {
        contador++;
        duracionTotal+= aux->T.Duracion;
        aux = aux->siguiente;
    }
    printf("\nCantidad de tareas: %d",contador);
    printf("\nDuracion total : %d",duracionTotal);
}
void mostrarMenuSeleccion(){
    printf("\n 1. Mover a Tareas REALIZADAS");
    printf("\n 2. Mover a Tareas En PROCESO");
    printf("\n 3. Eliminar Tarea");
    printf("\n 4. Cancelar");
}
