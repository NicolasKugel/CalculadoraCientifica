#include "comun.h"
#include "constantes.h"
#include "moduloE.h"
#include "Utils.h"

typedef struct{
    int numSesion;
    char nombre[LONG_NOMBRE_DE_ARCHIVO];
} sesionDisponible;

int __validarNombresPrevios(sesionDisponible *sesion){
    int proximaSesion = 1, errores = 0, numSesion;
    char nombreSesionPrevia[LONG_NOMBRE_DE_ARCHIVO];
    FILE *archivoMapeos;

    archivoMapeos = fopen("ecuaciones/.mapa_sesiones.txt", "r");
    if (archivoMapeos != NULL){
        // Primera pasada: verificar nombre y calcular próxima sesión
        while(fscanf(archivoMapeos, "%d %s", &numSesion, nombreSesionPrevia) == 2) {
            if (strcmp(sesion -> nombre, nombreSesionPrevia) == 0) {
                printf("Ya existe una sesión con el nombre '%s'. Elija otro.\n", sesion -> nombre);
                errores = 1;
            };
            proximaSesion = numSesion + 1; // si llegamos al final, el próximo número será i
        };
        // Segunda verificación: límite de archivos
        if(!errores && proximaSesion > CANTIDAD_DE_ARCHIVOS){
            printf("Limite de 10 archivos alcanzado, elimine los archivos de sesiones.\n");
            mostrarSesiones();
            printf("Ingrese el numero de la sesion a eliminar: ");
            scanf("%d", &numSesion);
            while(getchar() != '\n');
            eliminarArchivoIndividual(numSesion);
            errores = 1;
        };
        if(!errores){
            sesion -> numSesion = proximaSesion;
        };
        fclose(archivoMapeos);
    } else{
        printf("No se pudo abrir el archivo de mapeos en modo lectura.");
        errores = 1;
    };
    return errores;
}

void __validarNombreDeSesion(sesionDisponible *sesion){
    int esValido = 1;
    do {
        if(!esValido){
            printf("Caracteres que uso: %lld\n", strlen(sesion -> nombre));
        };
        printf("== El nombre del archivo no debe superar los 50 caracteres ==\n");
        printf("Ingrese el nombre de la sesión: ");
        fgets(sesion -> nombre, sizeof(sesion -> nombre), stdin);
        sesion -> nombre[strcspn(sesion -> nombre, "\n")] = '\0'; // eliminar salto de línea.
        esValido = 0;
    } while(strlen(sesion -> nombre) > LONG_NOMBRE_DE_ARCHIVO || __validarNombresPrevios(sesion));
}

void guardarYReiniciar() {
    char rutaCompleta[RUTA_COMPLETA_ARCHIVO];
    char ecuacion[LONG_DE_ECUACIONES];
    FILE *archivoDeEcuaciones, *archivoMapa, *aTmp;
    sesionDisponible sesion;

    // -- Pedir nombre de sesión y verificar si ya existe en el mapa --
    __validarNombreDeSesion(&sesion);

    // -- Crear el nuevo archivo de ecuaciones --
    sprintf(rutaCompleta, "ecuaciones/%s.txt", sesion.nombre);
    archivoDeEcuaciones = fopen((char *)rutaCompleta, "w");
    if (!archivoDeEcuaciones) {
        printf("Error al crear el archivo de sesión '%s'\n", rutaCompleta);
        return;
    }

    // -- Escribir las ecuaciones --
    aTmp = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "r");
    while (fgets(ecuacion, sizeof(ecuacion), aTmp)) {
        ecuacion[strcspn(ecuacion, "\n")] = '\0';
        // printf("Guardando ecuacion %s\n", ecuacion); debug
        fprintf(archivoDeEcuaciones, "%s\n", ecuacion);
    }
    fclose(archivoDeEcuaciones);

    // -- Registrar en el mapa --
    archivoMapa = fopen("ecuaciones/.mapa_sesiones.txt", "a");
    if (!archivoMapa) {
        printf("Error al registrar el nombre en el mapa de sesiones.\n");
        return;
    }
    fprintf(archivoMapa, "%d %s\n", sesion.numSesion, sesion.nombre);
    fclose(archivoMapa);

    // -- Reiniciar archivo temporal --
    reiniciarSesion();

    printf("Sesión '%s' guardada exitosamente en: '%s'\n", sesion.nombre, rutaCompleta);
}
