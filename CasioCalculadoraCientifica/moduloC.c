#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"

void guardarYReiniciar(char (*ecuaciones)[LONG_DE_ECUACIONES]){
    char nombreDeArchivos[30];
    int i = 1, hayArchivosDisponibles = 0;

    FILE *archivoDeEcuaciones;
    sprintf(nombreDeArchivos, "ecuaciones/ECUACIONES-%d.txt", i);
    archivoDeEcuaciones = fopen(nombreDeArchivos, "r");
    if (!archivoDeEcuaciones){
        hayArchivosDisponibles = 1;
        printf("Archivo numero %d de ecuaciones disponible\n", i);
    };
    while(archivoDeEcuaciones && !hayArchivosDisponibles && i <= CANTIDAD_DE_ARCHIVOS){
        fclose(archivoDeEcuaciones);
        i++;
        sprintf(nombreDeArchivos, "ecuaciones/ECUACIONES-%d.txt", i);
        printf("Intentando abrir archivo %s\n", nombreDeArchivos);
        archivoDeEcuaciones = fopen((char *) nombreDeArchivos, "r");
        if(!archivoDeEcuaciones){
            hayArchivosDisponibles = 1;
            printf("Archivo numero %d de ecuaciones disponible\n", i);
        } else{
            printf("Archivo numero %d de ecuaciones no disponible\n", i);
        };
    };
    if (hayArchivosDisponibles){
        archivoDeEcuaciones = fopen(nombreDeArchivos, "w");
        int i = 0;
        while (*ecuaciones[i]){
            fprintf(archivoDeEcuaciones, "%s\n", ecuaciones[i]);
            i++;
        };
        fclose(archivoDeEcuaciones);
        archivoDeEcuaciones = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "r");
        if (!archivoDeEcuaciones) {
            printf("Aún no hay archivo temporal en está sesión\n");
        } else {
            fclose(archivoDeEcuaciones);
            printf("Eliminando registros en archivo temporal de la sesión\n");
            archivoDeEcuaciones = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w");
        };
        fclose(archivoDeEcuaciones);
    };
}
