#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

void guardarYReiniciar() {
    char rutaCompleta[RUTA_COMPLETA_ARCHIVO], nombreSesion[LONG_DE_SESIONES];
    char ecuacion[LONG_DE_ECUACIONES];
    int i = 1, nombreValido = 1;
    FILE *archivoDeEcuaciones, *archivoMapa, *aTmp;

    // -- Pedir nombre de sesión --
    do {
        if(!nombreValido){
            printf("El nombre de archivo no debe superar los 50 caracteres\n");
            printf("Caracteres que uso: %ld\n", strlen(nombreSesion));
        }
        printf("Ingrese el nombre de la sesión: ");
        fgets(nombreSesion, sizeof(nombreSesion), stdin);
        nombreSesion[strlen(nombreSesion) - 1] = '\0'; // eliminar salto de línea
        nombreValido = 0;
    } while(strlen(nombreSesion) > 50);

    // -- Verificar si ya existe en el mapa --
    archivoMapa = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivoMapa != NULL) {
        char nombreSesionPrevia[LONG_DE_SESIONES];
        int numSesion;

        while (fscanf(archivoMapa, "%d %s", &numSesion, nombreSesionPrevia) == 2) {
            if (strcmp(nombreSesion, nombreSesionPrevia) == 0) {
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

    // -- Crear el nuevo archivo de ecuaciones --
    sprintf(rutaCompleta, "ecuaciones/%s.txt", nombreSesion);
    archivoDeEcuaciones = fopen((char *)rutaCompleta, "w");
    if (!archivoDeEcuaciones) {
        printf("Error al crear el archivo de sesión '%s'\n", rutaCompleta);
        return;
    }

    // -- Escribir las ecuaciones --
    aTmp = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "r");
    while (fgets(ecuacion, sizeof(ecuacion), aTmp)) {
        ecuacion[strlen(ecuacion) - 1] = '\0';
        printf("Guardando ecuacion %s\n", ecuacion);
        fprintf(archivoDeEcuaciones, "%s\n", ecuacion);
    }
    fclose(archivoDeEcuaciones);

    // -- Registrar en el mapa --
    archivoMapa = fopen("ecuaciones/.mapa_sesiones.txt", "a");
    if (!archivoMapa) {
        printf("Error al registrar el nombre en el mapa de sesiones.\n");
        return;
    }
    fprintf(archivoMapa, "%d %s\n", i, nombreSesion);
    fclose(archivoMapa);

    // -- Reiniciar archivo temporal --
    archivoDeEcuaciones = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w");
    if (archivoDeEcuaciones) {
        fclose(archivoDeEcuaciones);
        printf("Archivo temporal reiniciado correctamente.\n");
    }

    printf("Sesión '%s' guardada exitosamente como '%s'\n", nombreSesion, rutaCompleta);
}
