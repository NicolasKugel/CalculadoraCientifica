#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

typedef struct {
    int numSesion;
    char nombreSesion[LONG_NOMBRE_DE_ARCHIVO];
} sesion;

void eliminarArchivosDeSesiones(){
    char nombreDeArchivo[LONG_NOMBRE_DE_ARCHIVO], rutaCompleta[RUTA_COMPLETA_ARCHIVO];
    int numSesion;
    FILE *archivoMapeos;

    archivoMapeos = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivoMapeos != NULL){
        while(fscanf(archivoMapeos, "%d %s", &numSesion, nombreDeArchivo) == 2){
            sprintf(rutaCompleta, "ecuaciones/%s.txt", nombreDeArchivo);
            if(remove(rutaCompleta) == 0){
                printf("Se elimino archivo %s\n", rutaCompleta);
            } else{
                printf("No se pudo borrar archivo %s\n", rutaCompleta);
            };
        }
        fclose(archivoMapeos);
        remove("ecuaciones/.mapa_sesiones.txt");
    }else {
        printf("No se pudo abrir el archivo de mapeos\n");
    }
}

void eliminarArchivoIndividual(int sesionAEliminar){
    sesion sesionesDisponibles[9];
    int i = 0, j;
    FILE *archivoMapeo;
    char rutaCompleta[RUTA_COMPLETA_ARCHIVO];

    archivoMapeo = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivoMapeo == NULL){
        printf("No se pudo abrir el archivo de mapeos para lectura.\n");
    };
    while(fscanf(archivoMapeo, "%d %s", &sesionesDisponibles[i].numSesion, sesionesDisponibles[i].nombreSesion) == 2){
        if (sesionesDisponibles[i].numSesion == sesionAEliminar){
            sprintf(rutaCompleta, "ecuaciones/%s.txt", sesionesDisponibles[i].nombreSesion);
            printf("Sesion a eliminar encontrada, archivo: %s\n", rutaCompleta);
            remove(rutaCompleta);
            continue; // No se avanza el indice para pisar los valores con las sesiones que si se quieren convervar.
        }else{
            i++;
        };
    };
    fclose(archivoMapeo);

    archivoMapeo = fopen("ecuaciones/.mapa_sesiones.txt", "w");
    if (archivoMapeo == NULL){
        printf("No se pudo abrir el archivo de mapeos para escritura.\n");
    };
    for(j = 0; j < i; j++){
        fprintf(archivoMapeo, "%d %s\n", j + 1, sesionesDisponibles[j].nombreSesion); // Reorganizo los archivos.
        printf("Cargando ecuaciones en sesion %d %s\n", sesionesDisponibles[j].numSesion, sesionesDisponibles[j].nombreSesion);
    };
    fclose(archivoMapeo);
}

