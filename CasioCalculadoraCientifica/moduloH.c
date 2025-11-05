#include <stdio.h>
#include "Utils.h"

int mostrarAyuda(){
    char opcion = 'X';

    printf("== Ingresando al menú de ayuda ==\n");
    do {
        printf("Escriba letra del modulo para ver su ayuda:\n\
        OPCION - DESCRIPCION \n\
        A - Escribir ecuacion \n\
        B - Ver ecuaciones de la sesion\n\
        C - Guardar y reiniciar sesion\n\
        D - Leer ecuaciones guardadas\n\
        E - Borrar ecucaciones guardadas\n\
        F - Resolver ecuacion\n\
        H - Ayuda de nuevo\n\
        X - Salir\n\
        ");
        opcion = validarIngresoDeOpcion(opcion);

        switch (opcion) {
            case 'A':
                printf("Ayuda modulo A");
            break;
            case 'B':
                printf("\n=== MODULO B - VER ECUACIONES DE LA SESION ===\n");
                printf("DESCRIPCION: Muestra todas las ecuaciones cargadas en la sesión actual.\n");
                printf("MODO DE USO:\n");
                printf("  1. Seleccione la opción B del menú principal\n");
                printf("  2. El sistema mostrará todas las ecuaciones activas\n");
                printf("  3. Las ecuaciones se muestran en el orden ingresado\n");
                printf("RESTRICCIONES:\n");
                printf("  - Solo muestra ecuaciones de la sesión en curso\n");
                printf("  - No permite modificación directa desde esta vista\n\n");
                waitEnter();
                break;
            case 'C':
                printf("\n=== MODULO C - GUARDAR Y REINICIAR SESION ===\n");
                printf("DESCRIPCION: Guarda la sesión actual y prepara una nueva sesión.\n");
                printf("MODO DE USO:\n");
                printf("  1. Ingrese un nombre único para la sesión (máx. 50 caracteres)\n");
                printf("  2. El sistema valida que el nombre no exista\n");
                printf("  3. Todas las ecuaciones se guardan en un archivo\n");
                printf("  4. La sesión actual se reinicia para nuevas ecuaciones\n");
                printf("RESTRICCIONES:\n");
                printf("  - Máximo 10 sesiones guardadas simultáneamente\n");
                printf("  - Nombres de sesión deben ser únicos\n");
                printf("  - No se permiten caracteres especiales en nombres\n");
                printf("  - Si hay 10 sesiones, debe eliminar una para guardar\n\n");
                waitEnter();
                break;
            case 'D':
                printf("Ayuda modulo D");
                printf("\n=== MODULO D - LEER ECUACIONES GUARDADAS ===\n");
                printf("DESCRIPCION: Carga una sesión guardada anteriormente.\n");
                printf("MODO DE USO:\n");
                printf("  1. El sistema muestra lista de sesiones guardadas\n");
                printf("  2. Seleccione el número de sesión deseada\n");
                printf("  3. Todas las ecuaciones de esa sesión se cargan\n");
                printf("  4. Puede continuar trabajando con esas ecuaciones\n");
                printf("RESTRICCIONES:\n");
                printf("  - La sesión actual se reemplaza por la cargada\n");
                printf("  - Máximo 10 sesiones disponibles para cargar\n\n");
                waitEnter();
                break;
            case 'E':
                printf("\n=== MODULO E - BORRAR ECUACIONES GUARDADAS ===\n");
                printf("DESCRIPCION: Elimina sesiones guardadas permanentemente.\n");
                printf("MODO DE USO:\n");
                printf("  Al presionar E automaticamente los archivos de sesiones previas guardados \n\
                se borran permanentemente\n");
                printf("RESTRICCIONES:\n");
                printf("  - La eliminación es PERMANENTE e IRREVERSIBLE\n");
                printf("  - Solo afecta sesiones guardadas, no la sesión actual\n\n");
                waitEnter();
                break;
            case 'F':
                printf("Ayuda modulo F");
                waitEnter();
                break;
            case 'H':
                printf("\n=== MODULO H - AYUDA DEL PROGRAMA ===\n");
                printf("DESCRIPCION: Proporciona información de uso para todos los módulos.\n");
                printf("MODO DE USO:\n");
                printf("  1. Seleccione la letra del módulo que necesita ayuda\n");
                printf("  2. Lea la descripción, modo de uso y restricciones\n");
                printf("  3. Presione cualquier tecla para continuar viendo ayuda\n");
                printf("  4. Presione 'X' para salir del sistema de ayuda\n");
                waitEnter();
                break;
        }
    } while(opcion != 'X');
    printf("== Saliendo del menú de ayuda ==\n");
    return 0;
}
