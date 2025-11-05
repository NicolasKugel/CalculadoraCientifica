#include "comun.h"
#include "constantes.h"
#include <ctype.h>
#include "Utils.h"


int validarOpcion(int op, int *opciones){
    int valida = 0, sesion = 0;
    while(*opciones && sesion < CANTIDAD_DE_ARCHIVOS){
        if (*opciones == op) {
            valida = 1;
            break;
        }
        opciones++;
        sesion++;
    }
    return valida;
}

void mostrarYSeleccionar(){
    char nombreDeArchivos[CANTIDAD_DE_ARCHIVOS][LONG_NOMBRE_DE_ARCHIVO]; // Matriz con los nombres de archivos
    char nombreDeArchivo[LONG_NOMBRE_DE_ARCHIVO], ecuacion[LONG_DE_ECUACIONES];
    char rutaCompleta[RUTA_COMPLETA_ARCHIVO]; // incluyendo el directorio "ecuaciones"
    char seleccionarSesion;
    int opcion = 0, opcionValida = 1, i = 0, numSesion, sesionesDisponibles[CANTIDAD_DE_ARCHIVOS];
    FILE *archivoMapeo, *archivoSeleccionado, *aTmp;

    printf("=== Sesiones guardadas ===\n");
    archivoMapeo = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivoMapeo == NULL){
        printf("No se pudo abrir el archivo de mapeos en modo lectura.\n");
    }
    if (archivoMapeo && validarArchivoVacio(archivoMapeo)){
        // -- Mostrar archivos y guardarlos en la matriz --
        while(fscanf(archivoMapeo, "%d %s", &numSesion, nombreDeArchivo) == 2){
            printf("[Sesion %d] %s\n", numSesion, nombreDeArchivo);
            strcpy(nombreDeArchivos[numSesion - 1], nombreDeArchivo);
            sesionesDisponibles[i] = numSesion;
            i++;
        };

        do {
            if (!opcionValida){
                printf("Opción inválida, ingresa N o S.\n");
            };
            printf("Desea seleccionar una sesión? (S) si (N) no: ");
            seleccionarSesion = toupper(getchar());
            while(getchar() != '\n');
            opcionValida = 0;
        } while(seleccionarSesion != 'S' && seleccionarSesion != 'N');
        opcionValida = 1;

        if (seleccionarSesion == 'S'){
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
            if (archivoSeleccionado == NULL){
                printf("No se pudo abrir el archivo en modo lectura ubicado en: %s\n", rutaCompleta);
            }
            aTmp = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w"); // Archivo sesion actual
            if (aTmp == NULL){
                printf("No se pudo abrir el archivo ecuaciones-sesion-actual.tmp en modo escritura");
            }
            if (archivoSeleccionado && aTmp){
                printf("Abriendo archivo %s\n", rutaCompleta);
                // -- Cargar las ecuaciones en el archivo --
                while(fgets(ecuacion, sizeof(ecuacion), archivoSeleccionado) != NULL){
                    ecuacion[strlen(ecuacion) - 1] = '\0';
                    // printf("ingresando ecuacion %s\n", ecuacion); debug
                    fprintf(aTmp, "%s\n", ecuacion);
                };
                fclose(archivoSeleccionado);
                fclose(aTmp);
            };
        };
    };
}
