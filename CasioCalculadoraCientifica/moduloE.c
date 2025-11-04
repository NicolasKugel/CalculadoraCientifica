#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

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


