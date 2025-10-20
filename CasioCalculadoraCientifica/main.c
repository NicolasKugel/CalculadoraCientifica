#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define VERSION 1.0
#define LONG_OPCIONES 8

void validarIngresoDeOpcion(char, char*);
int buscarOpcionEnOpciones(char, char*);

int main()
{
    char opcion;
    char opciones_validas[LONG_OPCIONES] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'X'};


    printf("Version de calculadora %0.1f\n", VERSION);
    printf("Ingresa una opcion del siguiente menu:\n \
    OPCION - DESCRIPCION \n\
    A - Escribir ecuacion \n\
    B - Ver ecuaciones de esta sesion\n\
    C - Guardar y reiniciar sesion\n\
    D - Leer ecuaciones guardadas\n\
    E - Borrar ecucaciones guardadas\n\
    F - Resolver ecuacion\n\
    H - Ayuda\n\
    X - Salir\n\
    ");

    validarIngresoDeOpcion(opcion, opciones_validas);

    switch (toupper(opcion)) {
        case 'A':
            // Llamada al modulo A
            break;
        case 'B':
            // Llamada al modulo B
            break;
        case 'C':
            // Llamada al modulo C
            break;
        case 'D':
            // Llamada al modulo D
            break;
        case 'E':
            // Llamada al modulo E
            break;
        case 'F':
            // Llamada al modulo F
            break;
        case 'H':
            // Llamada al modulo H
            break;
        case 'X':
            // Llamada al modulo X
            break;
    }

    return 0;
}

void validarIngresoDeOpcion(char op, char *ops){
    int band = 1;
    do {
        if (!band){
            printf("Opcion %c ingresada no es valida", op);
        }
        printf("Opcion: \n");
        fgets(op, sizeof(op), stdin);
        band = 0;
    } while (!buscarOpcionEnOpciones(op, ops));
}

int buscarOpcionEnOpciones(char op, char *ops){
    int i = 0;
    for(i = 0; i < LONG_OPCIONES; i++){
        if (op == *ops){
            return 1;
        }
        ops++;
    }
    return 0;
}
