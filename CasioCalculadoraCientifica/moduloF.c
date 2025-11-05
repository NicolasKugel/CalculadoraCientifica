#include "moduloF.h"

typedef struct {
    char fn[LONG_DE_ECUACIONES];
    int pos;
} tbl_fn;

typedef struct {
    double x;
    double y;
    char* result;
} tbl_val;


char* __seleccionarFuncion()
{
    tbl_fn funciones[CANTIDAD_DE_ECUACIONES] = {{"\0", 1},{"\0", 2},{"\0", 3},{"\0", 4},{"\0", 5},{"\0", 6},{"\0", 7},{"\0", 8},{"\0", 9},{"\0", 10}};
    FILE *sesion_actual = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "r");
    tbl_fn *fn_aux = funciones;
    char *output = (char*) malloc(LONG_DE_ECUACIONES);
    int j = 1, opcionValida = 1;
    while(fgets(fn_aux->fn, LONG_DE_ECUACIONES, sesion_actual))
    {
        fn_aux++;
    }
    rewind(sesion_actual);
    fn_aux = funciones;
    do
    {
        clearScreen();
        if(!opcionValida)
            printf("opcion invalida, por favor seleccione una correcta\n\n");
        fn_aux = funciones;
        printf("Lista de ecuaciones: \n");
        while(strcmp(fn_aux->fn,"\0"))
        {
            printf("%d) %s\n", fn_aux->pos, fn_aux->fn);
            fn_aux++;
        }
        printf("\nSeleccione una opcion: ");
        scanf("%d", &j);
        while (getchar() != '\n');
        fn_aux = funciones;
        if(j>=1 && j<=10)
        {
            while(fn_aux->pos != j)
            fn_aux++;
        }
        opcionValida = 0;
    } while(!strcmp(fn_aux->fn,"\0") || (j<1 || j>10));
    strcpy(output,fn_aux->fn);
    fclose(sesion_actual);
    return output;
}

int __cargarTablaManual(tbl_val **tbl)
{
    int i, fls = 0;
    clearScreen();
    printf("Ingrese cuantos casos desea evaluar: ");
    scanf("%d", &fls);
    while (getchar() != '\n');
    *tbl = (tbl_val*) malloc(sizeof(tbl_val) * fls);
    tbl_val *aux = *tbl;
    for(i=0;i<fls;i++)
    {
        clearScreen();
        printf("ingrese el valor %d de X: ", i+1);
        scanf("%lf", &(aux->x));
        while (getchar() != '\n');
        clearScreen();
        printf("ingrese el valor %d de Y: ", i+1);
        scanf("%lf", &(aux->y));
        while (getchar() != '\n');
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
    while (getchar() != '\n');
    clearScreen();
    printf("Ingrese el valor de Y: ");
    scanf("%lf", &y);
    while (getchar() != '\n');
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

void mainModuloF()
{
    tbl_val *tabla = NULL;
    tbl_val *aux_tbl;
    int len_tbl, i;
    char op;
    char* fn;
    clearScreen();
    fn = __seleccionarFuncion();
    clearScreen();
    printf("Ecuacion seleccionada: %s\n\n", fn);
    printf("Seleccione operacion a realizar:\n");
    printf("* Resolver ecuacion con tabla manual de valores    --> A\n");
    printf("* Resolver ecuacion con valor unico y rangos (+-5) --> B\n");
    printf("* Volver al menu anterior                          --> X\n");
    printf("\nIngrese una opcion para continuar: ");
    scanf("%c", &op);
    while (getchar() != '\n');
    switch(op)
    {
        case 'A':
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
            break;
        case 'B':
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
            break;
        case 'X': // es el valor de x traducido a int
            break;
        default:
            clearScreen();
            printf("Operacion invalida, ingrese una opcion correcta\n");
            waitEnter();
            mainModuloF(fn);
    }
}
