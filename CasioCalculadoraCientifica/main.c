#include <ctype.h>
#include "comun.h"
#include "constantes.h"
#include "moduloA.h"
#include "moduloB.h"
#include "moduloC.h"
#include "moduloD.h"
#include "moduloE.h"
#include "moduloH.h"
#include "Utils.h"


int main(){
    char opcion = 'X';
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
        opcion = validarIngresoDeOpcion(opcion);

        switch (opcion) {
            case 'A':
                //printf("Llamada al modulo A");
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
                mostrarAyuda();
                break;
        }
    } while(opcion != 'X');
    printf("Llamada al modulo X");
    return 0;
}
