#include "Utils.h"


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

int validarArchivoVacio(FILE *archivo){
    int hayInformacion = 0;
    int primerCaracter = fgetc(archivo);
    if (primerCaracter == EOF){
        printf("== No hay información ==\n");
    } else {
        hayInformacion = 1;
        rewind(archivo);
    };
    return hayInformacion;
}

void mostrarEcuacionesDelArchivo(FILE *archivo){
    char ecuacion[LONG_DE_ECUACIONES];
    int i = 1;
    printf("=== Ecuaciones de la sesión actual ===\n");
    if(validarArchivoVacio(archivo)){
        while (fgets(ecuacion, sizeof(ecuacion), archivo)){
            printf("[Ecuacion %d]. %s", i++, ecuacion);
        };
    };
    rewind(archivo);
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
        archivo = fopen("ecuaciones/.mapa_sesiones.txt", "w");
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

void reiniciarSesion(){
    FILE *aSesionActual;
    aSesionActual = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w");
    if (aSesionActual) {
        fclose(aSesionActual);
        // printf("Archivo temporal reiniciado correctamente.\n"); debug
    };
};

// convierto valor de double a string
char* doubleAString(double val)
{
    char* buffer = NULL;
    char* buffer_aux = NULL;
    int len = 0;
    buffer_aux = (char*) malloc(TAM_NUM);
    if(val == trunc(val))
    {
        sprintf(buffer_aux, "%.0lf", val);
    }
    else
    {
        sprintf(buffer_aux, "%lf", val);
    }
    len = strlen(buffer_aux);
    buffer = (char*) malloc(len + 1);
    memcpy(buffer, buffer_aux, len + 1);
    free(buffer_aux);
    return buffer;
}
