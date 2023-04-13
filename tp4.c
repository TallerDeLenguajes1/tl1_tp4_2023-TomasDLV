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


void main(){
    Tarea **tareasPen,**tareasRe;
    
    int numTarea;
    printf("\nIngrese la cantidad de tareas a cargar");
    scanf("%d",&numTarea);
    tareasPen = (Tarea **)malloc(sizeof(Tarea *)*numTarea);
    iniciarTarea(tareasPen,numTarea);
    cargaDeTarea(tareasPen,numTarea);

    mostrarTarea(tareasPen,numTarea);

    int contRe = 0;
    for (int i = 0; i < numTarea; i++)
    {   
        char respuesta[2];
        printf("\n¿La tarea %d esta realizada?",i+1);
        fflush(stdin);
        gets(respuesta);
        if (1==strcmp(respuesta,"si"))
        {
            tareasRe[contRe] = tareasPen[i];
            contRe++;
            tareasPen[i]=NULL;
        }
        
    }
    

    iniciarTarea(tareasPen,numTarea);
    iniciarTarea(tareasRe,numTarea);   
    
    liberarTarea(tareas,numTarea);
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
        printf("\nIngresar descripcion :  ");
        fflush(stdin);
        tareas[i]->Descripcion = malloc(sizeof(char )*60);
        gets(tareas[i]->Descripcion);
        tareas[i]->Duracion= rand()%91+10;
    }
}

void mostrarTarea(Tarea **tareas,int numTarea){
    printf("\nAqui tus tareas:\n\n");
    for (int k = 0; k < numTarea; k++)
    {
        printf("\n\nNumero de Tarea %d",k+1);
        printf("\nDescripcion: ");
        puts(tareas[k]->Descripcion);
        printf("\nDuracion: %d",tareas[k]->Duracion);
    }
}
void liberarTarea(Tarea **tareas,int numTarea){
    for (int j = 0; j < numTarea; j++)
    {
        free(tareas[j]->Descripcion);
        free(tareas[j]);
    }
}