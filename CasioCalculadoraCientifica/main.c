#include <ctype.h>
#include "comun.h"
#include "constantes.h"
#include "moduloA.h"
#include "moduloB.h"
#include "moduloC.h"
#include "moduloD.h"
#include "moduloE.h"
#include "Utils.h"

char validarIngresoDeOpcion(char, char*);
int buscarOpcionEnOpciones(char, char*);

int main(){
    char opcion = 'X';
    char opciones_validas[LONG_OPCIONES] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'X', '\0'};
    crearArchivosNecesarios();

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
                moduloA_ejecutar();
            break;
            case 'B':
                printf("Llamada al modulo B\n");
                mostrarEcuacionesSesion();
                break;
            case 'C':
                printf("Llamada al modulo C\n");
                guardarYReiniciar();
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
                printf("Llamada al modulo F\n");
                break;
            case 'H':
                printf("Llamada al modulo H\n");
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
        while (getchar() != '\n'); // Limpiar buffer
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
