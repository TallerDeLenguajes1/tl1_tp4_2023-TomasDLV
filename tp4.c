#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct tarea{
    int TareaID; //Numerado en ciclo iteraivo
    char *Descripcion;
    int Duracion; //entre 10-100
};
typedef struct tarea Tarea;
struct nodo
{
    Tarea T;
    struct nodo *siguiente;
};
typedef struct nodo * Nodo;
typedef Nodo * Lista;


void mostrarMenu();//
Lista crearLista();//
Nodo aislarNodoXId(Lista l,int idTarea);//
void insertarNodo(Lista l,Nodo n);//
void cargaDeTarea(Lista l,int *contador);//
void borrarTarea(Lista l,int idTarea);//
void mostrarTareas(Lista l);//
void realizarTarea(Lista l1,Lista l2,int idTarea);//
void liberarTarea(Lista l);
void buscaTareaId(Lista l,int id);
void buscaTareaPalabra(Lista l,char * palabra);


void main(){
    Lista tareasPen,tareasRe;
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
            int bandera = 0;
            do
            {
                cargaDeTarea(tareasPen,&contador);
                printf("\nDesea continuar cargando Tareas?(si: 1 |no: 0)");
                scanf("%d",&bandera);
                fflush(stdin);
            } while (bandera ==1);

            break;
        case 2:
            printf("\n-----------Tareas PENDIENTES----------\n");
            mostrarTareas(tareasPen);
            break;
        case 3:
            int numTarea;
            printf("\nElija que tarea desea marcar como realizada");
            fflush(stdin);
            scanf("%d",&numTarea);
            realizarTarea(tareasPen,tareasRe,numTarea);
            break;
        case 4:
            printf("\n-----------Tareas REALIZADAS----------\n");
            mostrarTareas(tareasRe);
            break;
        case 5:
            printf("\nIngrese el ID de la tarea Pendiente a buscar: ");
            scanf("%d",&idTarea);
            buscaTareaId(tareasPen,idTarea);
            break;
        case 6:
            printf("\nIngrese la palabra clave de la tarea Pendiente a buscar: ");
            fflush(stdin);
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
            borrarTarea(tareasPen,idTarea);
            break;
        case 10:
            return;
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
Lista crearLista(){
    return NULL;
}
Nodo aislarNodoXId(Lista l,int idTarea){
    Nodo aux1;
    Nodo aux2;
    aux1 = l;
    while (aux1 != NULL || aux1->T.TareaID != idTarea)
    {
        aux2 = aux1;
        aux1 = aux1->siguiente;
    }
    if (aux1 == NULL)
    {
        return NULL;
    }else
    {
        return aux1;
    }
}
void insertarNodo(Lista l,Nodo n){
    n->siguiente = l;
    l = n;
}
void cargaDeTarea(Lista l,int * contador){

    Nodo tareaAux = (Nodo)malloc(sizeof(struct nodo));
    printf("\nTarea numero %d", *contador);
    tareaAux->T.TareaID = *contador;
    tareaAux->T.Descripcion = (char *)malloc(sizeof(char) * 30);
    printf("\nIngresar descripcion :  ");
    fflush(stdin);
    gets(tareaAux->T.Descripcion);
    tareaAux->T.Duracion = rand() % 91 + 10;
    insertarNodo(l,tareaAux);
}
void borrarTarea(Lista l,int idTarea){
    Nodo aux;
    aux = aislarNodoXId(l,idTarea);
    free(aux);
}

void mostrarTareas(Lista l){
    Nodo aux;
    aux = l;
    while (aux != NULL)
    {
        printf("\n\nNumero de Tarea: %d",aux->T.TareaID);
        printf("\nDescripcion: ");
        puts(aux->T.Descripcion);
        printf("\nDuracion: %d",aux->T.Duracion);
        aux=aux->siguiente;
    }
}
void realizarTarea(Lista l1,Lista l2,int idTarea){
    Nodo aux;
    aux = aislarNodoXId(l1,idTarea);
    if (aux != NULL)
    {
        insertarNodo(l2,aux);
    }else{
        printf("\nNo se encontro la tarea en la Lista.");
    }
    
}
void liberarTarea(Lista l){
    
    while (l != NULL)
    {
        Nodo aux;
        aux = l;
        l = aux->siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
}

void buscaTareaId(Lista l,int id){
    Nodo aux;
    aux = l;

    while (aux != NULL)
    {
        
        if (aux->T.TareaID == id)
        {
            printf("\n\nNumero de Tarea: %d",aux->T.TareaID);
            printf("\nDescripcion: ");
            puts(aux->T.Descripcion);
            printf("\nDuracion: %d",aux->T.Duracion);
            return;
        }    
        aux = aux->siguiente;
    }
    printf("\nNo se encontro la tarea.");
    return;
}
void buscaTareaPalabra(Lista l,char* palabra){
    Nodo aux;
    aux = l;
    while (aux != NULL)
    {

        if (strstr(aux->T.Descripcion,palabra))
        {
            printf("\n\nNumero de Tarea: %d",aux->T.TareaID);
            printf("\nDescripcion: ");
            puts(aux->T.Descripcion);
            printf("\nDuracion: %d",aux->T.Duracion);
            return;
        }   
        aux = aux->siguiente; 
    }
    printf("\nNo se encontro la tarea.");
    return;
}