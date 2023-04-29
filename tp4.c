#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Tarea{
    int TareaID; //Numerado en ciclo iteraivo
    char *Descripcion;
    int Duracion; //entre 10-100
}Tarea;
struct nodo
{
    Tarea T;
    struct nodo *siguiente;
};

typedef struct nodo * lista;


void mostrarMenu();
lista crearLista();
lista aislarNodoXId(lista *l,int idTarea);
void insertarNodo(lista *l,lista n);
void cargaDeTarea(lista *l,int * contador);
void borrarTarea(lista *l,int idTarea);
void mostrarTarea(lista l);
void realizarTarea(lista *l1,lista *l2,int idTarea);
void liberarTarea(lista l);
void buscaTareaId(lista l,int id);
void buscaTareaPalabra(lista l,char * palabra);


void main(){
    lista tareasPen,tareasRe;
    int numTarea,opcion =0,contador = 0,idTarea;
    char palabra[30];

    tareasPen = crearLista();
    tareasRe = crearLista();

    do{
        mostrarMenu();
        printf("\nElija una opcion: ");
        scanf("%d",&opcion);
        switch (opcion)
        {
        case 1:
            cargaDeTarea(&tareasPen,&contador);
            break;
        case 2:
            printf("\n-----------Tareas PENDIENTES----------\n");
            mostrarTarea(tareasPen);
            break;
        case 3:
            int numTarea;
            printf("\nElija que tarea desea marcar como realizada");
            fflush(stdin);
            scanf("%d",&numTarea);
            realizarTarea(&tareasPen,&tareasRe,numTarea);
            break;
        case 4:
            printf("\n-----------Tareas REALIZADAS----------\n");
            mostrarTarea(tareasRe);
            break;
        case 5:
            printf("\nIngrese el ID de la tarea Pendiente a buscar: ");
            scanf("%d",&idTarea);
            buscaTareaId(tareasPen,idTarea);
            break;
        case 6:
            printf("\nIngrese la palabra clave de la tarea Pendiente a buscar: ");
            fflush((stdin));
            gets(palabra);
            buscaTareaPalabra(tareasPen,palabra);
            
            break;
        case 7:
            printf("\nIngrese el ID de la tarea Realizada a buscar: ");
            scanf("%d",&idTarea);
            buscaTareaId(tareasRe,idTarea);
            break;
        case 8:
            printf("\nIngrese la palabra clave de la tarea Realizada a buscar: ");
            fflush((stdin));
            gets(palabra);
            buscaTareaPalabra(tareasRe,palabra);
            break;
        case 9:
            printf("\nIngrese el Id de la tarea Pendiente a quitar: ");
            scanf("%d",&idTarea);
            borrarTarea(&tareasPen,idTarea);
            break;
        case 10:
            break;
            
        
        default:
            printf("\nNo ingresaste  una opcion valida");
            break;
        }


    }while (opcion != 10);
    liberarTarea(tareasPen);
    liberarTarea(tareasRe);

}

//---------- Implementacion de funciones ----------------
void mostrarMenu(){
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
lista crearLista(){
    return NULL;
}
lista aislarNodoXId(lista *l,int idTarea){
    lista aux1 = crearLista();
    lista aux2 = crearLista();
    aux1 = *l;
    if (aux1->T.TareaID == idTarea)
    {
        *l = aux1->siguiente;
        return aux1;
    }
    while (aux1->siguiente->T.TareaID != idTarea)
    {
        aux1 = aux1->siguiente;
        if (aux1 == NULL)
        {
            printf("\nNo se encontro la tareaa borrar.");
            return NULL;
        }   
    }
    aux2= aux1->siguiente;
    aux1->siguiente = aux2->siguiente;
    return aux2;
}
void insertarNodo(lista *l,lista n){
    n->siguiente = *l;
    *l = n;
}
void cargaDeTarea(lista *l,int * contador){

    int numTarea = 0;
    printf("\nIngrese la cantidad de tareas a cargar: ");
    fflush(stdin);
    scanf("%d",&numTarea); 
    for (int i = 0; i < numTarea; i++)
       {
        *contador = *contador + 1;
        lista tareaAux = (lista)malloc(sizeof(struct nodo));
        printf("\nTarea numero %d",*contador);
        tareaAux->T.TareaID = *contador;
        tareaAux->T.Descripcion = (char *)malloc(sizeof(char )*30);
        printf("\nIngresar descripcion :  ");
        fflush(stdin);
        gets(tareaAux->T.Descripcion);
        tareaAux->T.Duracion= rand()%91+10;
        tareaAux->siguiente = *l;
        *l = tareaAux;
    }
}
void borrarTarea(lista *l,int idTarea){
    lista aux;
    aux = aislarNodoXId(l,idTarea);
    free(aux);
}

void mostrarTarea(lista l){
    
    while (l != NULL)
    {
        printf("\n\nNumero de Tarea: %d",l->T.TareaID);
        printf("\nDescripcion: ");
        puts(l->T.Descripcion);
        printf("\nDuracion: %d",l->T.Duracion);
        l=l->siguiente;
    }
    
}
void realizarTarea(lista *l1,lista *l2,int idTarea){
    lista aux = NULL;
    aux = aislarNodoXId(l1,idTarea);
    if (aux != NULL)
    {
        insertarNodo(l2,aux);
    }else{
        printf("\nNo se encontro la tarea en la lista.");
    }
    
}
void liberarTarea(lista l){
    while (l != NULL)
    {
        lista aux;
        aux = l;
        l = aux->siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}

void buscaTareaId(lista l,int id){

    while (l != NULL)
    {
        
        if (l->T.TareaID == id)
        {
            printf("\n\nNumero de Tarea: %d",l->T.TareaID);
            printf("\nDescripcion: ");
            puts(l->T.Descripcion);
            printf("\nDuracion: %d",l->T.Duracion);
            return;
        }    
        l = l->siguiente;
    }
    printf("\nNo se encontro la tarea.");
    return;
}
void buscaTareaPalabra(lista l,char* palabra){

    while (l != NULL)
    {

        if (strstr(l->T.Descripcion,palabra))
        {
            printf("\n\nNumero de Tarea: %d",l->T.TareaID);
            printf("\nDescripcion: ");
            puts(l->T.Descripcion);
            printf("\nDuracion: %d",l->T.Duracion);
            return;
        }    
    }
    printf("\nNo se encontro la tarea.");
    return;
}