#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Tarea{
    int TareaID; //Numerado en ciclo iteraivo
    char *Descripcion;
    int Duracion; //entre 10-100
}typedef Tarea;



void main(){
    Tarea **tareas;
    int numTarea;
    printf("\nIngrese la cantidad de tareas a cargar");
    scanf("%d",&numTarea);
    tareas = (Tarea **)malloc(sizeof(Tarea *)*numTarea);
    for (int i = 0; i < numTarea; i++)
       {
        tareas[i] = (Tarea *)malloc(sizeof(Tarea));
        tareas[i]->Descripcion = malloc(sizeof(char )*60);
        printf("\nTarea numero %d",i+1);
        printf("\nIngresar descripcion :  ");
        fflush(stdin);
        gets(tareas[i]->Descripcion);
        tareas[i]->Duracion= rand()%91+10;
    }
    printf("\nAqui tus tareas:\n\n");
    for (int k = 0; k < numTarea; k++)
    {
        printf("\n\nNumero de Tarea %d",k+1);
        printf("\nDescripcion: ");
        puts(tareas[k]->Descripcion);
        printf("\nDuracion: %d",tareas[k]->Duracion);
    }
    
    for (int j = 0; j < numTarea; j++)
    {
        free(tareas[j]->Descripcion);
        free(tareas[j]);
    }
    


}