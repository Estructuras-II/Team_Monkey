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


Alumno* crearAlumno(int id, char* nombre);
Alumno* insertarInicio(Alumno* cab, int id, char* nombre);
Alumno* buscarAlumno(Alumno* cab, int id);
void agregarAsistencia(Alumno* alumno, char* fecha, char presente);
void tomarAsistencia(Alumno* cab);
void mostrarLista(Alumno* cab);
void mostrarAsistenciaAlumno(Alumno* cab, int idBuscado);
Alumno* registrarAlumnos();
void menu(Alumno* listaAlumnos);


int main() {
    printf("Registro de alumnos\n");
    Alumno* listaAlumnos = registrarAlumnos();
    if (listaAlumnos == NULL) {
        printf("No se registraron alumnos\n");
        return 0;
    }

    menu(listaAlumnos);
    return 0;
}

Alumno* crearAlumno(int id, char* nombre) {
    Alumno* nuevo = (Alumno*) malloc(sizeof(Alumno));
    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria\n");
        exit(1);
    }
    nuevo->id = id;
    strcpy(nuevo->nombre, nombre);
    nuevo->lista = NULL;
    nuevo->sig = NULL;
    return nuevo;
}

Alumno* insertarInicio(Alumno* cab,int id, char* nombre) {
    Alumno* nuevo = crearAlumno(id,nombre);
    nuevo->sig = cab;
    return nuevo;
}

Alumno* buscarAlumno(Alumno* cab, int id) {
    while (cab != NULL) {
        if (cab->id== id)
            return cab;
        cab = cab->sig;
    }
    return NULL;
}


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


void mostrarAsistenciaAlumno(Alumno* cab, int idBuscado) {
    Alumno* alumno = buscarAlumno(cab,idBuscado);
    if (alumno == NULL) {
        printf("Alumno con ID %d no encontrado.\n", idBuscado);
        return;
    }
    printf("Asistencias para %s (ID: %d):\n", alumno->nombre,alumno->id);
    Asistencia* a = alumno->lista;
    if (a == NULL) {
        printf("No hay asistencias registradas.\n");
        return;
    }
    while (a != NULL) {
        printf("  Fecha: %s - Presente: %c\n", a->fecha, a->asitencia);
        a = a->sig;
    }
}


Alumno* registrarAlumnos() {
    Alumno* lista = NULL;
    char continuar;
    do {
        int id;
        char nombre[50];

        printf("\n Registro de Alumno \n");
        printf("Ingrese ID del alumno: ");
        scanf("%d", &id);
        printf("Ingrese nombre del alumno: ");
        scanf(" %[^\n]", nombre);

        if (buscarAlumno(lista, id)) {
            printf("Ya existe un alumno con ese ID\n");
        } else {
            lista = insertarInicio(lista, id, nombre);
            printf("Alumno agregado correctamente.\n");
        }

        printf("Deseas agregar otro alumno?(s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    return lista;
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


