#include<stdio.h>
#include<stdlib.h>
#include <string.h>


//Alumno* registrarAlumno(){ }
//pedir los datos (id y nombre) y mandar llamar el insertarInicio/crearAlumno

Alumno* crearAlumno(int id, char* nombre){ //nodo
    Alumno* nuevo =(Alumno*) malloc (sizeof(Alumno));
    if (nuevo==NULL){
        printf("Error no se pudo asignar memoria\n");
        exit(1);
    }
    nuevo->id=id;
    strcpy(nuevo->nombre, nombre);
    nuevo->lista = NULL;
    nuevo->sig =NULL;
    return nuevo;
}

Alumno* insertarInicio(Alumno* cab, Alumno id, char* nombre){
    Alumno* nuevo = crearAlumno(id, nombre);
    nuevo->sig=cab;
    return nuevo;
}