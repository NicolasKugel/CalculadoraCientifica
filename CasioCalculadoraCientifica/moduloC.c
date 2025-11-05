#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"
#include "moduloE.h"
#include "Utils.h"

typedef struct{
    int numSesion;
    char nombre[LONG_NOMBRE_DE_ARCHIVO];
} sesionDisponible;

int validarNombresPrevios(sesionDisponible *sesion){
    int proximaSesion = 1, errores = 0, numSesion;
    char nombreSesionPrevia[LONG_DE_SESIONES];
    FILE *archivoMapeos;

    // Primera pasada: verificar nombre y calcular próxima sesión
    archivoMapeos = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivoMapeos != NULL){
        while(fscanf(archivoMapeos, "%d %s", &numSesion, nombreSesionPrevia) == 2) {
            if (strcmp(sesion -> nombre, nombreSesionPrevia) == 0) {
                printf("Ya existe una sesión con el nombre '%s'. Elija otro.\n", sesion -> nombre);
                errores = 1;
            };
            proximaSesion = numSesion + 1; // si llegamos al final, el próximo número será i
        };
        // Segunda verificación: límite de archivos
        if(!errores && proximaSesion > CANTIDAD_DE_ARCHIVOS){
            printf("Limite de 10 archivos alcanzado, elimine los archivos de sesiones.\n");
            mostrarSesiones();
            printf("Ingrese el numero de la sesion a eliminar: ");
            scanf("%d", &numSesion);
            while(getchar() != '\n');
            eliminarArchivoIndividual(numSesion);
            errores = 1;
        };

        if(!errores){
            sesion -> numSesion = proximaSesion;
        };

        fclose(archivoMapeos);
    } else{
        printf("No se pudo abrir el archivo de mapeos en modo lectura.");
        errores = 1;
    };
    return errores;
}

void validarNombreDeSesion(sesionDisponible *sesion){
    int esValido = 1;

    do {
        if(!esValido){
            printf("Caracteres que uso: %ld\n", strlen(sesion -> nombre));
        };
        printf("== El nombre del archivo no debe superar los 50 caracteres ==\n");
        printf("Ingrese el nombre de la sesión: ");
        fgets(sesion -> nombre, sizeof(sesion -> nombre), stdin);
        sesion -> nombre[strcspn(sesion -> nombre, "\n")] = '\0'; // eliminar salto de línea.
        esValido = 0;
    } while(strlen(sesion -> nombre) > LONG_NOMBRE_DE_ARCHIVO || validarNombresPrevios(sesion));
}

void guardarYReiniciar() {
    char rutaCompleta[RUTA_COMPLETA_ARCHIVO];
    char ecuacion[LONG_DE_ECUACIONES];
    FILE *archivoDeEcuaciones, *archivoMapa, *aTmp;
    sesionDisponible sesion;

    // -- Pedir nombre de sesión y verificar si ya existe en el mapa --
    validarNombreDeSesion(&sesion);

    // -- Crear el nuevo archivo de ecuaciones --
    sprintf(rutaCompleta, "ecuaciones/%s.txt", sesion.nombre);
    archivoDeEcuaciones = fopen((char *)rutaCompleta, "w");
    if (!archivoDeEcuaciones) {
        printf("Error al crear el archivo de sesión '%s'\n", rutaCompleta);
        return;
    }

    // -- Escribir las ecuaciones --
    aTmp = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "r");
    while (fgets(ecuacion, sizeof(ecuacion), aTmp)) {
        ecuacion[strcspn(ecuacion, "\n")] = '\0';
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
    fprintf(archivoMapa, "%d %s\n", sesion.numSesion, sesion.nombre);
    fclose(archivoMapa);

    // -- Reiniciar archivo temporal --
    archivoDeEcuaciones = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w");
    if (archivoDeEcuaciones) {
        fclose(archivoDeEcuaciones);
        printf("Archivo temporal reiniciado correctamente.\n");
    };

    printf("Sesión '%s' guardada exitosamente como '%s'\n", sesion.nombre, rutaCompleta);
}
