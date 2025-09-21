#include<stdio.h>
#include<stdlib.h>

typedef struct asistencia
{
    char fecha[9]; // DD/MM/AA
    char asitencia; // s ó n
    struct asistencia *sig;
}Asistencia;

typedef struct alumno
{
    int id;
    char nombre[50];
    Asistencia *lista; //Esta es la lista de asistencias
    struct alumno *sig;
}Alumno;

