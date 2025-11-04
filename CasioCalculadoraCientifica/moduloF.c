#include "moduloF.h"

int __cargarTablaManual(tbl_val **tbl)
{
    int i, fls = 0;
    clearScreen();
    printf("Ingrese cuantos casos desea evaluar: ");
    scanf("%d", &fls);
    *tbl = (tbl_val*) malloc(sizeof(tbl_val) * fls);
    tbl_val *aux = *tbl;
    for(i=0;i<fls;i++)
    {
        clearScreen();
        printf("ingrese el valor %d de X: ", i+1);
        scanf("%lf", &(aux->x));
        clearScreen();
        printf("ingrese el valor %d de Y: ", i+1);
        scanf("%lf", &(aux->y));
        aux->result = NULL;
        aux++;
    }
    return fls;
}

int __cargarTablaSemiAuto(tbl_val **tbl)
{
    int i, fls = 11; // se setea el valor de fls a 11 porque se guarda el valor ed la variable y un rango de (-5; 5)
    double x, y;
    *tbl = malloc(sizeof(tbl_val) * fls);
    tbl_val *aux = *tbl;
    clearScreen();
    printf("Ingrese el valor de X: ");
    scanf("%lf", &x);
    clearScreen();
    printf("Ingrese el valor de Y: ");
    scanf("%lf", &y);
    for(i=0;i<fls;i++)
    {
        aux->x = x + (-5 + i);
        aux->y = y + (-5 + i);
        aux->result = NULL;
        aux++;
    }
    return fls;
}

void __mostrarTabla(tbl_val *tbl, int cant_fls) //funcion para debugear
{
    tbl_val *aux = tbl;
    int i;
    printf("valor X\t\t\t\tvalor Y\t\t\t\tresultado\n");
    for(i=0;i<cant_fls;i++)
    {
        printf("%lf\t\t\t%lf\t\t\t%s\n", aux->x, aux->y, aux->result);
        aux++;
    }
}

void __mostrarResultados(char *func, tbl_val *tbl, int cant_fls)
{
    tbl_val *aux = tbl;
    int i;
    clearScreen();
    printf("Funcion: %s\n\n", func);
    printf("valor X\t\t\t\tvalor Y\t\t\t\tresultado\n");
    for(i=0;i<cant_fls;i++)
    {
        printf("%lf\t\t\t%lf\t\t\t%s\n", aux->x, aux->y, aux->result);
        aux++;
    }
    waitEnter();
}

void mainModuloF(char* fn)
{
    tbl_val *tabla = NULL;
    tbl_val *aux_tbl;
    int len_tbl, i;
    char op;
    clearScreen();
    printf("Seleccione operacion a realizar:\n");
    printf("* Resolver ecuacion con tabla manual de valores    --> a\n");
    printf("* Resolver ecuacion con valor unico y rangos (+-5) --> b\n");
    printf("* Volver al menu anterior                          --> x\n");
    printf("\nIngrese una opcion para continuar: ");
    scanf("%c", &op);
    switch(op)
    {
        case 'a':
            len_tbl = __cargarTablaManual(&tabla);
            aux_tbl = tabla;
            //__mostrarTabla(tabla, len_tbl);
            for(i=0; i<len_tbl; i++)
            {
                aux_tbl->result = resolverFuncion(fn, aux_tbl->x, aux_tbl->y);
                aux_tbl++;
            }
            __mostrarResultados(fn, tabla, len_tbl);
            free(tabla);
            mainModuloF(fn);
        case 'b':
            len_tbl = __cargarTablaSemiAuto(&tabla);
            aux_tbl = tabla;
            //__mostrarTabla(tabla, len_tbl);
            for(i=0; i<len_tbl; i++)
            {
                aux_tbl->result = resolverFuncion(fn, aux_tbl->x, aux_tbl->y);
                aux_tbl++;
            }
            __mostrarResultados(fn, tabla, len_tbl);
            free(tabla);
            mainModuloF(fn);
        case 'x': // es el valor de x traducido a int
            return;
        default:
            clearScreen();
            printf("Operacion invalida, ingrese una opcion correcta\n");
            waitEnter();
            mainModuloF(fn);
    }
}
