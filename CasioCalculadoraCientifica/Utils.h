#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <ctype.h>
#include <math.h>
#include "constantes.h"
#include "comun.h"

void clearScreen();

void waitEnter();

void mostrarSesiones();

void mostrarEcuacionesDelArchivo(FILE *archivo);

int validarArchivoVacio(FILE *archivo);

void crearArchivosNecesarios();

char validarIngresoDeOpcion(char);

int buscarOpcionEnOpciones(char, char*);

void reiniciarSesion();

char* doubleAString(double);

#endif // UTILS_H_INCLUDED
