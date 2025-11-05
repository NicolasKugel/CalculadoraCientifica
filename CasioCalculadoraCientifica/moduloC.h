#ifndef MODULOC_INCLUDED
#define MODULOC_INCLUDED

typedef struct{
    int numSesion;
    char nombre[51];
} sesionDisponible;

int validarNombresPrevios(sesionDisponible*);
char validarNombreDeSesion(sesionDisponible*);
void guardarYReiniciar();

#endif // MODULOC_INCLUDED
