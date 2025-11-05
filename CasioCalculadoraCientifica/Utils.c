#include "constantes.h"
#include "comun.h"
#include <ctype.h>

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
    printf("\nPresiona Enter para continuar...");
    while (getchar() != '\n'); // limpia el buffer
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

void validarArchivoVacio(FILE *archivo){
    int primerCaracter = fgetc(archivo);
    if (primerCaracter == EOF){
        printf("== No hay información ==\n");
    } else {
        rewind(archivo);
    };
}

void mostrarEcuacionesDelArchivo(FILE *archivo){
    char ecuacion[LONG_DE_ECUACIONES];
    int i = 1;
    printf("=== Ecuaciones de la sesión actual ===\n");
    validarArchivoVacio(archivo);
    while (fgets(ecuacion, sizeof(ecuacion), archivo)){
        printf("[Ecuacion %d]. %s", i++, ecuacion);
    };
}

void crearArchivosNecesarios(){
    FILE *archivo;
    archivo = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "r");
    if (archivo == NULL){
        printf("Creando archivo temporal de sesión\n");
        archivo = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w");
    }
    fclose(archivo);
    archivo = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivo == NULL){
        printf("Creando archivo para los mapeos\n");
        archivo = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w");
    }
    fclose(archivo);
}

int buscarOpcionEnOpciones(char op, char *ops){
    while(*ops){
        if (op == *ops){
            return 1;
        };
        ops++;
    }

    return 0;
};

char validarIngresoDeOpcion(char op){
    char opciones_validas[LONG_OPCIONES] = {'A', 'B', 'C', 'D', 'E', 'F', 'H', 'X', '\0'};
    int band = 1;
    do {
        if (!band){
            printf("Opcion ingresada %c no es valida \n", op);
        }

        printf("Opcion: ");
        op = toupper(getchar());
        while (getchar() != '\n'); // Limpiar buffer
        band = 0;
    } while (!buscarOpcionEnOpciones(op, opciones_validas));
    return op;
};
