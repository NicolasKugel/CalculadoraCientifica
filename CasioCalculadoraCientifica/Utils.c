#include "constantes.h"
#include <stdio.h>

void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitEnter()
{
    while (getchar() != '\n'); // limpia el buffer
    printf("\nPresiona Enter para continuar...");
    getchar();
}

// Lista los archivos de sesiones previas guardados.
void mostrarSesiones(){
    int numSesion;
    FILE *archivoMapeo;
    char nombreDeArchivo[LONG_NOMBRE_DE_ARCHIVO];

    archivoMapeo = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivoMapeo == NULL){
        printf("=== No hay archivos guardados ===\n");
        return;
    }
    while(fscanf(archivoMapeo, "%d %s", &numSesion, nombreDeArchivo) == 2){
        printf("[Sesion %d] %s\n", numSesion, nombreDeArchivo);
    };
}

void mostrarEcuacionesDelArchivo(FILE *archivo){
    char ecuacion[LONG_DE_ECUACIONES];
    int i = 1;
    printf("=== Ecuaciones de la sesión actual ===\n");
    __validarArchivoVacio(archivo);
    while (fgets(ecuacion, sizeof(ecuacion), archivo)){
        printf("[Ecuacion %d]. %s", i++, ecuacion);
    };
}

void __validarArchivoVacio(FILE *archivo){
    int primerCaracter = fgetc(archivo);
    if (primerCaracter == EOF){
        printf("== No hay información ==\n");
    } else {
        rewind(archivo);
    };
}

void crearArchivosNecesarios(){
    FILE *archivo;
    archivo = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w");
    fclose(archivo);
    archivo = fopen("ecuaciones/.mapa_sesiones.txt", "w");
    fclose(archivo);
}


