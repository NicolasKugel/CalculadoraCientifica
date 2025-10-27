#include "moduloB.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void mostrarEcuacionesSesion(char (*ecuaciones)[50], int hayEcuaciones) {
    if (!hayEcuaciones) {
        printf("No hay ecuaciones cargadas.\n");
        return;
    }

    FILE *temp = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w");
    if (!temp) {
        printf("Error al crear archivo temporal");
        return;
    }

    printf("=== Ecuaciones de la sesión actual ===\n");
    int i = 0;
    while(*ecuaciones[i]){
        fprintf(temp, "%s\n", ecuaciones[i]); // se guarda ecuación en archivo temporal
        printf("[%d.] %s\n", i + 1, ecuaciones[i]); // se muestra en pantalla
        i++;
    }

    fclose(temp);
    printf("\nEcuaciones guardadas temporalmente en 'ecuaciones-sesion-actual.tmp'\n");
}
