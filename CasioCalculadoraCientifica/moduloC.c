#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"

void guardarYReiniciar(char (*ecuaciones)[LONG_DE_ECUACIONES]) {
    char nombreArchivo[50], nombreSesion[51];
    int existe = 0, i = 1, nombreValido = 1;
    FILE *archivoDeEcuaciones, *archivoMapa;

    // --- 1. Pedir nombre de sesión ---
    do {
        if(!nombreValido){
            printf("El nombre de archivo no debe superar los 50 caracteres\n");
            printf("Caracteres que uso: %d", strlen(nombreSesion));
        }
        printf("Ingrese el nombre de la sesión: ");
        fgets(nombreSesion, sizeof(nombreSesion), stdin);
        nombreSesion[strlen(nombreSesion) - 1] = '\0'; // eliminar salto de línea
        nombreValido = 0;
    } while(strlen(nombreSesion) > 50);

    // --- 2. Verificar si ya existe en el mapa ---
    archivoMapa = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivoMapa != NULL) {
        char nombreExistente[30];
        int numSesion;

        while (fscanf(archivoMapa, "%d %s", &numSesion, nombreExistente) == 2) {
            if (strcmp(nombreSesion, nombreExistente) == 0) {
                printf("Ya existe una sesión con el nombre '%s'. Elija otro.\n", nombreSesion);
                fclose(archivoMapa);
                return;
            };
            i = numSesion + 1; // si llegamos al final, el próximo número será i
            if (i > CANTIDAD_DE_ARCHIVOS){
                printf("Limite de 10 archivos superado, por favor elimine o sobreescriba otro archivo.\n");
                fclose(archivoMapa);
                return;
            };
        };
        fclose(archivoMapa);
    }

    // --- 3. Crear el nuevo archivo de ecuaciones ---
    sprintf(nombreArchivo, "ecuaciones/%s.txt", nombreSesion);
    archivoDeEcuaciones = fopen((char*)nombreArchivo, "w");
    if (!archivoDeEcuaciones) {
        printf("Error al crear el archivo de sesión '%s'\n", nombreArchivo);
        return;
    }

    // --- 4. Escribir las ecuaciones ---
    int j = 0;
    while (*ecuaciones[j]) {
        fprintf(archivoDeEcuaciones, "%s\n", ecuaciones[j]);
        j++;
    }
    fclose(archivoDeEcuaciones);

    // --- 5. Registrar en el mapa ---
    archivoMapa = fopen("ecuaciones/.mapa_sesiones.txt", "a");
    if (!archivoMapa) {
        printf("Error al registrar el nombre en el mapa de sesiones.\n");
        return;
    }
    fprintf(archivoMapa, "%d %s\n", i, nombreSesion);
    fclose(archivoMapa);

    // --- 6. Reiniciar archivo temporal ---
    archivoDeEcuaciones = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w");
    if (archivoDeEcuaciones) {
        fclose(archivoDeEcuaciones);
        printf("Archivo temporal reiniciado correctamente.\n");
    }

    printf("Sesión '%s' guardada exitosamente como '%s'\n", nombreSesion, nombreArchivo);
}
