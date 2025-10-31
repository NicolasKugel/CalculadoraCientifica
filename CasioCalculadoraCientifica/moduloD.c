#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mostrarYSeleccionar(){
    char nombreDeArchivos[10][51];
    char (*pArchivo)[51] = nombreDeArchivos; // defino el puntero por las dudas, para seguir escalando
    int opcion = 0, numSesion;
    FILE *archivoMapeo;

    archivoMapeo = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivoMapeo == NULL){
        printf("=== No hay archivos guardados ===\n");
        return;
    }

    // -- Mostrar archivos --
    while(fscanf(archivoMapeo, "%d %s", &numSesion, nombreDeArchivos) == 2){
        printf("[Sesion %d] %s\n", numSesion, nombreDeArchivos);
        strcpy(nombreDeArchivos[numSesion], nombreDeArchivos);
    };

    printf("Ingrese numero de sesion: ");
    scanf("%d", &opcion);
    while(getchar() != '\n');
    // En base a la opcion cargar la matriz del punto A con las ecuaciones del archivo de sesió elegido.
    printf("Se selecciono el archivo: ecuaciones/%s.txt\n", pArchivo[opcion]);
}



