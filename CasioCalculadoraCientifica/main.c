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
                moduloA_ejecutar();
            break;
            case 'B':
                mostrarEcuacionesSesion();
                break;
            case 'C':
                guardarYReiniciar();
                break;
            case 'D':
                mostrarYSeleccionar();
                break;
            case 'E':
                eliminarArchivosDeSesiones();
                break;
            case 'F':
                break;
            case 'H':
                mostrarAyuda();
                break;
        }
    } while(opcion != 'X');
    reiniciarSesion();
    return 0;
}
