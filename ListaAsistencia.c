#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct asistencia 
{
    char fecha[9];   
    char asitencia;  
    struct asistencia *sig;
} Asistencia;

typedef struct alumno 
{
    int id;
    char nombre[50];
    Asistencia *lista;
    struct alumno *sig;
} Alumno;


void agregarAsistencia(Alumno*alumno, char*fecha, char presente) 
{
    Asistencia*nueva = (Asistencia*) malloc(sizeof(Asistencia));

    if (nueva == NULL) 
    {
        printf("ERROR. No se pudo asignar memoria.\n");
        exit(1);
    }
    strcpy(nueva->fecha, fecha);
    nueva->asitencia = presente;
    nueva->sig = alumno->lista;
    alumno->lista = nueva;
}


void tomarAsistencia(Alumno*cab) 
{
    char fecha[9];
    printf("Ingrese la fecha (DD/MM/AA): ");
    scanf("%s", fecha);

    Alumno*actual = cab;
    while(actual != NULL) 
    {
        char resp;
        printf("¿%s está presente? (s/n): ", actual->nombre);
        scanf(" %c", &resp);
        agregarAsistencia(actual, fecha, resp);
        actual = actual->sig;
    }
}


void mostrarLista(Alumno*cab) 
{
    Alumno*actual = cab;

    while(actual != NULL) 
    {
        printf("\nAlumno ID: %d, Nombre: %s\n", actual->id, actual->nombre);
        Asistencia*a = actual->lista;

        if(a == NULL) 
            printf("Sin asistencias registradas.\n");
            else {
            while (a != NULL) 
            {
                printf("Fecha: %s - Asistencia: %c\n", a->fecha, a->asitencia);
                a = a->sig;
            }
        }

        actual = actual->sig;
    }
}



void menu(Alumno*listaAlumnos) 
{
    int opcion;
    do {
        printf("\n===== Menú Principal =====\n");
        printf("1. Tomar asistencia\n");
        printf("2. Mostrar lista de asistencia (todos los alumnos)\n");
        printf("3. Mostrar asistencia de un alumno\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) 
        {
            case 1:
                tomarAsistencia(listaAlumnos);
                break;
            case 2:
                mostrarLista(listaAlumnos);
                break;
            case 3: 
            {
                int id;
                printf("Ingrese el ID del alumno para mostrar su asistencia: ");
                scanf("%d", &id);
                mostrarAsistenciaAlumno(listaAlumnos, id);
                break;
            }
            case 4:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Intente de nuevo.\n");
        }
    } while(opcion != 4);
}

int main() 
{
   
}