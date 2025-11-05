#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

int validarOpcion(int op, int *opciones){
    int valida = 0, s = 0;
    while(*opciones && s < CANTIDAD_DE_ARCHIVOS){
        if (*opciones == op) {
            valida = 1;
            break;
        }
        opciones++;
        s++;
    }
    return valida;
}

void mostrarYSeleccionar(){
    char nombreDeArchivos[CANTIDAD_DE_ARCHIVOS][LONG_NOMBRE_DE_ARCHIVO]; // matriz con los nombres de archivos
    char nombreDeArchivo[LONG_NOMBRE_DE_ARCHIVO], ecuacion[LONG_DE_ECUACIONES];
    char rutaCompleta[RUTA_COMPLETA_ARCHIVO]; // incluyendo el directorio ecuaciones
    int opcion = 0, opcionValida = 1, i = 0, numSesion, sesionesDisponibles[CANTIDAD_DE_ARCHIVOS];
    FILE *archivoMapeo, *archivoSeleccionado, *aTmp;

    archivoMapeo = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivoMapeo == NULL){
        printf("=== No hay archivos guardados ===\n");
        return;
    }

    // -- Mostrar archivos y guardarlos en la matriz --
    while(fscanf(archivoMapeo, "%d %s", &numSesion, nombreDeArchivo) == 2){
        printf("[Sesion %d] %s\n", numSesion, nombreDeArchivo);
        strcpy(nombreDeArchivos[numSesion - 1], nombreDeArchivo);
        sesionesDisponibles[i] = numSesion;
        i++;
    };

    do {
        if (!opcionValida){
            printf("El numero de sesion ingresado no es valido.\n");
        }
        printf("Ingrese numero de sesion: ");
        scanf("%d", &opcion);
        while(getchar() != '\n');
        opcionValida = 0;
    } while(!validarOpcion(opcion, sesionesDisponibles));

    // -- Cargar la sesion elegida en el archivo de la sesion actual --
    printf("Se selecciono el archivo: ecuaciones/%s.txt\n", nombreDeArchivos[opcion - 1]);
    sprintf(rutaCompleta, "ecuaciones/%s.txt", nombreDeArchivos[opcion - 1]);
    archivoSeleccionado = fopen((char*)rutaCompleta, "r"); // Archivo seleccionado
    aTmp = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w"); // Archivo sesion actual
    printf("Abriendo archivo %s\n", rutaCompleta);

    // -- Cargar las ecuaciones en el archivo --
    while(fgets(ecuacion, sizeof(ecuacion), archivoSeleccionado) != NULL){
        ecuacion[strlen(ecuacion) - 1] = '\0';
        printf("ingresando ecuacion %s\n", ecuacion);
        fprintf(aTmp, "%s\n", ecuacion);
    }
    fclose(archivoSeleccionado);
    fclose(aTmp);
}
