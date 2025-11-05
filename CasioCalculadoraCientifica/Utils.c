#include "Utils.h"
#include "constantes.h"

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

