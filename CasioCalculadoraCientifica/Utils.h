#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

void clearScreen();

void waitEnter();

void mostrarSesiones();

void mostrarEcuacionesDelArchivo(FILE *archivo);

int validarArchivoVacio(FILE *archivo);

void crearArchivosNecesarios();

char validarIngresoDeOpcion(char);

int buscarOpcionEnOpciones(char, char*);

void reiniciarSesion();

#endif // UTILS_H_INCLUDED
