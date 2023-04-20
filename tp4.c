#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{
    int TareaID; //Numerado en ciclo iteraivo
    char *Descripcion;
    int Duracion; //entre 10-100
}typedef Tarea;

void iniciarTarea(Tarea **tareas,int numTarea);
void cargaDeTarea(Tarea **tareas,int numTarea);
void mostrarTarea(Tarea **tareas,int numTarea);
void liberarTarea(Tarea **tareas,int numTarea);
void buscaTarea(Tarea **tareas,int numTarea,int id);


void main(){
    Tarea **tareasPen,**tareasRe;
    
    int numTarea;
    printf("\nIngrese la cantidad de tareas a cargar");
    scanf("%d",&numTarea);
    tareasPen = (Tarea **)malloc(sizeof(Tarea *)*numTarea);
    iniciarTarea(tareasPen,numTarea);
    iniciarTarea(tareasRe,numTarea);   
    cargaDeTarea(tareasPen,numTarea);

    mostrarTarea(tareasPen,numTarea);

    int contRe = 0;
    for (int i = 0; i < numTarea; i++)
    {   
        int respuesta;
        printf("\n¿La tarea %d esta realizada?",i+1);
        fflush(stdin);
        scanf("%d",&respuesta);
        if (1 == respuesta)
        {
            tareasRe[contRe] = tareasPen[i];
            contRe++;
            tareasPen[i]=NULL;
        }   
    }
    printf("\n-----------Tareas REALIZADAS----------\n");
    mostrarTarea(tareasRe,numTarea);
    printf("\n-----------Tareas PENDIENTES----------\n");
    mostrarTarea(tareasPen,numTarea);

    printf("\nIngrese la tarea a buscar");
    
    int buscar;
    fflush(stdin);
    scanf("%d",&buscar);
    buscaTarea(tareasRe,numTarea,buscar);
   
    
    
    liberarTarea(tareasPen,numTarea);
    liberarTarea(tareasRe,numTarea);

}
void iniciarTarea(Tarea **tareas,int numTarea){    
    for (int i = 0; i < numTarea; i++)
       {  
        tareas[i]=NULL;
    }
    

}
void cargaDeTarea(Tarea **tareas,int numTarea){
    for (int i = 0; i < numTarea; i++)
       {
        tareas[i] = (Tarea *)malloc(sizeof(Tarea));
        printf("\nTarea numero %d",i+1);
        tareas[i]->TareaID=i+1;
        printf("\nIngresar descripcion :  ");
        fflush(stdin);
        tareas[i]->Descripcion = malloc(sizeof(char )*30);
        gets(tareas[i]->Descripcion);
        tareas[i]->Duracion= rand()%91+10;
    }
}

void mostrarTarea(Tarea **tareas,int numTarea){
    printf("\nAqui tus tareas:");
    for (int k = 0; k < numTarea; k++)
    {
        if (tareas[k] != NULL)
        {
            printf("\n\nNumero de Tarea: %d",tareas[k]->TareaID);
            printf("\nDescripcion: ");
            puts(tareas[k]->Descripcion);
            printf("\nDuracion: %d",tareas[k]->Duracion);
        }        
    }
}
void liberarTarea(Tarea **tareas,int numTarea){
    for (int j = 0; j < numTarea; j++)
    {
        free(tareas[j]->Descripcion);
        free(tareas[j]);
    }
}
void buscaTarea(Tarea **tareas,int numTarea,int id){

    for (int i = 0; i < numTarea; i++)
    {
        printf("\n%d",tareas[i]->TareaID);
        
        if (tareas[i] != NULL && tareas[i]->TareaID == id)
        {
            printf("\n\nNumero de Tarea: %d",tareas[i]->TareaID);
            printf("\nDescripcion: ");
            puts(tareas[i]->Descripcion);
            printf("\nDuracion: %d",tareas[i]->Duracion);
            return;
        }    
    }
    printf("\nNo se encontro la tarea.");
}