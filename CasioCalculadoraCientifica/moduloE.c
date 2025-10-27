#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void eliminarArchivosDeSesiones(){
    char nombreDeArchivos[30];
    int i;
    FILE *archivoDeEcuaciones;

    for(i = 0; i < 10; i++){
        sprintf(nombreDeArchivos, "ecuaciones/ECUACIONES-%d.txt", (i + 1));
        archivoDeEcuaciones = fopen(nombreDeArchivos, "r");
        if (!archivoDeEcuaciones){
            continue;
        } else {
            fclose(archivoDeEcuaciones);
            if (remove(nombreDeArchivos) == 0){
                printf("Se elimino archivo %s\n", nombreDeArchivos);
            } else{
                printf("No se pudo borrar archivo %s\n", nombreDeArchivos);
            };
        };
    };
}


