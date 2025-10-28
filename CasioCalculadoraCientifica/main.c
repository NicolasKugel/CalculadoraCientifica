#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "moduloB.h"
#include "moduloC.h"
#include "moduloD.h"
#include "moduloE.h"
#define VERSION 1.0
#define LONG_OPCIONES 9

char validarIngresoDeOpcion(char, char*);
int buscarOpcionEnOpciones(char, char*);

int main(){
    char opcion = 'X';
    char opciones_validas[LONG_OPCIONES] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'X', '\0'};

    printf("Version de calculadora %0.1f\n", VERSION);
    do {
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

        opcion = validarIngresoDeOpcion(opcion, opciones_validas);

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
                printf("Llamada al modulo C\n");
                char vectorDeEcuaciones2[10][50] = {{0}};

                strcpy(vectorDeEcuaciones2[0], "x+3*2");
                strcpy(vectorDeEcuaciones2[1], "x*3+2");
                strcpy(vectorDeEcuaciones2[2], "x*3-2");

                char (*pM2)[50] = vectorDeEcuaciones2;
                guardarYReiniciar(pM2);
                break;
            case 'D':
                printf("Llamada al modulo D\n");
                mostrarYSeleccionar();
                break;
            case 'E':
                printf("Llamada al modulo E\n");
                eliminarArchivosDeSesiones();
                break;
            case 'F':
                printf("Llamada al modulo F");
                break;
            case 'H':
                printf("Llamada al modulo H");
                break;
        }
    } while(opcion != 'X');
    printf("Llamada al modulo X");
    return 0;
}

char validarIngresoDeOpcion(char op, char *ops){
    int band = 1;
    char *posicion_inicial = ops;
    do {
        if (!band){
            printf("Opcion ingresada %c no es valida \n", op);
        }

        printf("Opcion: ");
        op = getchar();
        while (getchar() != '\n'); //Eliminamos el caracter de corte /n
        op = toupper(op);
        band = 0;
    } while (!buscarOpcionEnOpciones(op, posicion_inicial));

    return op;
};

int buscarOpcionEnOpciones(char op, char *ops){
    while(*ops){
        if (op == *ops){
            return 1;
        };
        ops++;
    }

    return 0;
};
