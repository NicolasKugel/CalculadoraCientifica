#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "moduloB.h"
#define VERSION 1.0
#define LONG_OPCIONES 9

void validarIngresoDeOpcion(char*, char*);
int buscarOpcionEnOpciones(char, char*);

int main()
{
    char opcion;
    char opciones_validas[LONG_OPCIONES] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'X', '\0'};

    printf("Version de calculadora %0.1f\n", VERSION);
    printf("Ingresa una opcion del siguiente menu:\n\
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

    validarIngresoDeOpcion(&opcion, opciones_validas);

    switch (opcion) {
        case 'A':
            printf("Llamada al modulo A");
            break;
        case 'B':
            printf("Llamada al modulo B\n");
            char vectorDeEcuaciones[10][50] = {{0}};

            strcpy(vectorDeEcuaciones[0], "x+3*2");
            strcpy(vectorDeEcuaciones[1], "x*3+2");
            strcpy(vectorDeEcuaciones[2], "x*3-2");

            char (*pM)[50] = vectorDeEcuaciones;
            int hayValores = 1;
            mostrarEcuacionesSesion(pM, hayValores);
            break;
        case 'C':
            printf("Llamada al modulo C");

            break;
        case 'D':
            printf("Llamada al modulo D");
            break;
        case 'E':
            printf("Llamada al modulo E");
            break;
        case 'F':
            printf("Llamada al modulo F");
            break;
        case 'H':
            printf("Llamada al modulo H");
            break;
        case 'X':
            printf("Llamada al modulo X");
            break;
    }

    return 0;
}

void validarIngresoDeOpcion(char *op, char *ops){
    int band = 1;
    char *posicion_inicial = ops;
    do {
        if (!band){
            printf("Opcion ingresada %c no es valida \n", *op);
        }
        printf("Opcion: ");
        *op = toupper(getchar());
        while (getchar() != '\n'); //Eliminamos el caracter de corte /n
        band = 0;
    } while (!buscarOpcionEnOpciones(*op, posicion_inicial));
}

int buscarOpcionEnOpciones(char op, char *ops){
    int i = 0;
    while(*ops){
        if (op == *ops){
            return 1;
        };
        ops++;
    }

    return 0;
}
