#include "moduloA.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_EXPR 50

void cadena_quitar_nueva_linea(char *s)
{
    char *p = s;
    if (!p)
        return;

    /* Avanza p hasta el carácter nulo para ubicarse al final */
    while (*p)
        p++;

    /* Si la cadena no estaba vacía, retrocedemos un carácter */
    if (p != s)
    {
        --p;
        /* Si el último carácter es '\n', lo reemplazamos por '\0' */
        if (*p == '\n')
            *p = '\0';
    }
}

void cadena_recortar_bordes(char *s)
{
    const char *p = s;      /* puntero para recorrer y encontrar el final útil */
    char *escritura = s;    /* puntero donde vamos a escribir la versión recortada */
    const char *inicio = s; /* primer carácter no blanco */
    const char *fin = s;    /* último carácter no blanco */

    if (!s)
        return;

    /* Recorremos para detectar el último no-espacio (fin) */
    while (*p)
    {
        if (*p != ' ' && *p != '\t')
            fin = p;
        p++;
    }

    /* Avanzamos inicio hasta el primer no-espacio */
    inicio = s;
    while (*inicio == ' ' || *inicio == '\t')
        inicio++;

    /* Copiamos el segmento [inicio..fin] in-place */
    while (inicio <= fin && *inicio)
    {
        *escritura++ = *inicio++;
    }
    *escritura = '\0';
}

void cadena_quitar_espacios(char *s)
{
    char *w = s;       /* write: dónde escribir */
    const char *r = s; /* read: desde dónde leer */
    if (!s)
        return;

    while (*r)
    {
        /* Copiamos solo si NO es espacio ni tabulación */
        if (*r != ' ' && *r != '\t')
        {
            *w = *r;
            w++;
        }
        r++;
    }
    *w = '\0'; /* cerramos la cadena en la nueva posición */
}

void cadena_a_minusculas(char *s)
{
    unsigned char *p = (unsigned char *)s;
    if (!s)
        return;

    while (*p)
    {
        /* tolower es parte de ctype.h (ANSI C) */
        *p = (unsigned char)tolower(*p);
        p++;
    }
}

int cadena_es_blanca(const char *s)
{
    int result;
    const unsigned char *p = (const unsigned char *)s;
    if (!s)
        result = 1;

    while (*p)
    {
        /* Si encontramos algo que NO sea espacio, tab, \n o \r -> no es blanca */
        if (*p != ' ' && *p != '\t' && *p != '\n' && *p != '\r')
        {
            result = 0;
        }
        p++;
    }
    result = 1;
    return result;
}


char* leer_ecuacion_simple(char *dst, int tam)
{
    int i = 0;
    int c;
    int truncada = 0;
    int resultado;

    if (!dst || tam == 0)
        resultado = -1;

    /* Mensaje opcional: podés quitarlo si esta funcion no debe imprimir */
    printf("Ingrese la ecuacion (x,y; + - * / ^ ; sqrt(...) o root(n,expr)):\n> ");

    /* Leemos caracter por caracter hasta \n o EOF, evitando overflow */
    while ((c = getchar()) != EOF)
    {
        if (c == '\r')
            continue; /* ignora CR (Windows) */
        if (c == '\n')
            break; /* fin de linea */
        if (i + 1 < tam)
        { /* reservo lugar para '\0' */
            dst[i++] = (char)c;
        }
        else
        {
            truncada = 1; /* sigo consumiendo, pero no escribo */
        }
    }

    if (c == EOF && i == 0)
        resultado = -1; /* EOF sin datos */
    dst[i] = '\0';

    /* --- Normalizacion SIMPLE in-place ---
       1) Eliminar espacios y tabs (internos y de bordes)
       2) Pasar a minuscula
       3) Verificar vacio */
    {
        char *w = dst; /* write */
        char *r = dst; /* read */
        int tiene_algo = 0;

        while (*r)
        {
            unsigned char ch = (unsigned char)*r;
            if (ch != ' ' && ch != '\t')
            {
                /* tolower para uniformar (x, y, sqrt, root) */
                *w = (char)tolower(ch);
                if (*w != '\n' && *w != '\r')
                    tiene_algo = 1;
                w++;
            }
            r++;
        }
        *w = '\0';

        if (!tiene_algo)
            resultado = -3; /* estaba vacia o solo blancos */
    }
    //resultado = truncada ? -2 : 0;

    if (!truncada) {
        char *ecuacion;
        printf("Valor de la variable dst: %s\n", dst);
        printf("Longitud de la variable dst: %ld\n", strlen(dst));
        ecuacion = (char*)malloc(sizeof(char) * strlen(dst));
        if (ecuacion == NULL){
            printf("No se pudo reservar la memoria\n");
        }
        strcpy(ecuacion, dst);
        return ecuacion;
    };
    return "\0";
}


void opcion_A_ingresar_ecuacion_demo(void)
{
    char expr[MAX_EXPR], op;
    char *rc;
    FILE *aTmp = fopen("ecuaciones/ecuaciones-sesion-actual.tmp", "w");

    if (aTmp == NULL) {
        printf("Error al abrir el archivo temporal\n");
        return;
    };
    do {
        rc = leer_ecuacion_simple(expr, sizeof(expr));
        if (*rc){
            /* expr ya viene sin espacios y en minuscula, lista para validar sintaxis y guardar */
            printf("Guardando ecuacion %s\n", rc);
            fprintf(aTmp, "%s\n", rc);
            free(rc);
        }
        else{
            printf("Error en la ecuacion\n");
            printf("Valor de RC: %s\n", rc);
        };
        /*
        else if (rc == -2)
        {
            puts("La ecuacion es demasiado larga.");
        }
        else if (rc == -3)
        {
            puts("No se ingreso ninguna ecuacion.");
        }
        else
        {
            puts("Error de lectura.");
        }
        */
        printf("Quiere seguir cargando ecuaciones ? (Y) si (X) no: ");
        op = getchar();
        while(getchar() != '\n');
        op = toupper(op);
    } while(op != 'X');
    fclose(aTmp);
}

