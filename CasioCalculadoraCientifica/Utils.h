#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

void clearScreen();

void waitEnter();

void mostrarSesiones();

void mostrarEcuacionesDelArchivo(FILE *archivo);

void validarArchivoVacio(FILE *archivo);

void crearArchivosNecesarios();

char validarIngresoDeOpcion(char);

int buscarOpcionEnOpciones(char, char*);

#endif // UTILS_H_INCLUDED
