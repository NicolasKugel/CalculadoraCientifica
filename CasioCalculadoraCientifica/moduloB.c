#include "comun.h"
#include "constantes.h"
#include "moduloB.h"
#include "Utils.h"

void mostrarEcuacionesSesion() {
    FILE *temp = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "r");
    char ecuacion[LONG_DE_ECUACIONES];
    int i = 1;

    if (temp == NULL) {
        printf("Error al leer archivo temporal\n");
        return;
    } else {
        mostrarEcuacionesDelArchivo(temp);
        fclose(temp);
    };
}
