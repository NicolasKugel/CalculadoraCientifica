#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validarArrayVacio(int *ops){
    int vacio = 1, i;
    for (i = 0; i < 10; i++){
        if (*ops != 0){
            vacio = 0;
            break;
        }
        ops++;
    }
    return vacio;
}

int buscarOpcion(int *op, int ops[]){
    if (ops[*op - 1] != 0){
        return 1;
    }
    return 0;
};

int validarOpcion(int *op, int opDispo[]){
    int band = 0;
    if (!validarArrayVacio(opDispo)){
        do {
            if(band){
                printf("Opción %d es invalida, debe ser un número de sesión disponible.\n", op);
            };
            printf("Ingrese el número de una sesión disponible: ");
            scanf("%d", op);
            while (getchar() != '\n');
            band = 1;
        } while (*op > 10 || *op < 1 || !buscarOpcion(op, opDispo));
    } else {
        printf("No hay archivos guardados\n");
    };
    return opDispo[*op - 1];
};

void mostrarYSeleccionar(){
    char nombreDeArchivos[30];
    int i, opcion = 0, opcionesDisponibles[10] = {0};
    FILE *archivoDeEcuaciones;

    for(i = 0; i < 10; i++){
        sprintf(nombreDeArchivos, "ecuaciones/ECUACIONES-%d.txt", (i + 1));
        archivoDeEcuaciones = fopen(nombreDeArchivos, "r");
        if (!archivoDeEcuaciones){
            continue;
        } else {
            opcionesDisponibles[i] = i + 1;
            printf("[Sesión %d.] %s\n", (i + 1), nombreDeArchivos);
            fclose(archivoDeEcuaciones);
        };
    };
    opcion = validarOpcion(&opcion, opcionesDisponibles);
    // En base a la opcion cargar la matriz del punto A con las ecuaciones del archivo de sesió elegido.
    printf("Se selecciono el archivo: ecuaciones/ECUACIONES-%d.tx\n", opcion);
}



