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
typedef Nodo lista;


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