#include "moduloB.h"
#include "constantes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void mostrarEcuacionesSesion() {
    FILE *temp = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "r");
    char ecuacion[LONG_DE_ECUACIONES];
    int i = 0;

    if (!temp) {
        printf("Error al leer archivo temporal\n");
        return;
    }
    printf("=== Ecuaciones de la sesión actual ===\n");
    while (fgets(ecuacion, sizeof(ecuacion), temp)){
        printf("[Ecuacion %d]. %s", i++, ecuacion);
    };

    fclose(temp);
}
