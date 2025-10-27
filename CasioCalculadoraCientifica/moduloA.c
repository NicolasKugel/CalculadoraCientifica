#include "moduloA.h"
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
    const unsigned char *p = (const unsigned char *)s;
    if (!s)
        return 1;

    while (*p)
    {
        /* Si encontramos algo que NO sea espacio, tab, \n o \r -> no es blanca */
        if (*p != ' ' && *p != '\t' && *p != '\n' && *p != '\r')
        {
            return 0;
        }
        p++;
    }
    return 1;
}

int leer_linea(char *dst, size_t dst_tam)
{
    int truncada = 0;
    int c;
    size_t i = 0;

    if (!dst || dst_tam == 0)
        return -1;

    /* Leemos carácter a carácter para controlar el tamaño y CRLF */
    while ((c = getchar()) != EOF)
    {
        if (c == '\r')
            continue; /* ignora CR (Windows) */
        if (c == '\n')
            break; /* fin de línea */
        if (i + 1 < dst_tam)
        {
            dst[i++] = (char)c; /* guardamos mientras haya espacio */
        }
        else
        {
            truncada = 1; /* seguimos consumiendo, pero ya no guardamos */
        }
    }

    if (c == EOF && i == 0)
        return -1; /* EOF sin datos */
    dst[i] = '\0';
    return truncada ? -2 : 0;
}

int entrada_leer_ecuacion(char *dst, size_t dst_tam)
{
    int rc;

    if (!dst || dst_tam == 0)
        return -1;

    printf("Ingrese la ecuacion (x,y; + - * / ^ ; sqrt(...) o root(n,expr)):\n> ");
    rc = leer_linea(dst, dst_tam);
    if (rc == -1)
    {
        /* EOF o error de lectura */
        return -1;
    }
    if (rc == -2)
    {
        /* El usuario escribió más de lo que entra en el buffer */
        cadena_quitar_nueva_linea(dst); /* por las dudas */
        cadena_recortar_bordes(dst);
        return -2; /* avisamos al llamador que se excedió */
    }

    /* Normalización básica */
    cadena_quitar_nueva_linea(dst);
    cadena_recortar_bordes(dst);

    if (cadena_es_blanca(dst))
    {
        return -3; /* vacío o solo blancos */
    }

    /* Limpieza para almacenamiento y parser posterior */
    cadena_quitar_espacios(dst);
    cadena_a_minusculas(dst);

    /* Listo para validación sintáctica posterior (no se hace aquí) */
    return 0;
}

void opcion_A_ingresar_ecuacion_demo(void)
{
    char expr[MAX_EXPR];
    int rc = leer_ecuacion_simple(expr, sizeof(expr));
    if (rc == 0)
    {
        /* expr ya viene sin espacios y en minuscula, lista para validar sintaxis y guardar */
    }
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
}

int leer_ecuacion_simple(char *dst, size_t tam)
{
    size_t i = 0;
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

    resultado = truncada ? -2 : 0;
}
