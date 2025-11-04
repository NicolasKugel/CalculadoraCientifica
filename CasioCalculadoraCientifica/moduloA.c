#include "moduloA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* =========================================================================
   LECTURA: guarda en 'destino' una linea de stdin (sin '\n' final)
   -------------------------------------------------------------------------
   - Si la linea entra completa en el buffer, reemplaza el '\n' por '\0'
   - Si se excede, se consume el resto hasta '\n' y se retorna -2
   - Si hay EOF o error, retorna -1
   ========================================================================= */
int leer_ecuacion_en_buffer(char *destino, int tamanio) {
    char *resultado_lectura;
    int longitud_leida;

    /* 1) Verificacion basica de puntero y tamanio minimo (al menos 2: un char + '\0') */
    if (destino == 0 || tamanio <= 1) return -1;

    /* 2) Intentamos leer la linea con fgets (incluye '\n' si entro en el tope) */
    resultado_lectura = fgets(destino, tamanio, stdin);
    if (resultado_lectura == 0) return -1;  /* EOF o error de lectura */

    /* 3) Medimos lo que quedo en el buffer */
    longitud_leida = (int)strlen(destino);

    /* 4) Si el ultimo caracter es '\n', lo quitamos y devolvemos OK */
    if (longitud_leida > 0 && destino[longitud_leida - 1] == '\n') {
        destino[longitud_leida - 1] = '\0';
        return 0;
    }

    /* 5) Si NO hay '\n', significa que la linea fue mas larga que el tope:
          consumimos el resto hasta fin de linea o EOF para limpiar stdin */
    {
        int caracter_extra;
        do { caracter_extra = getchar(); } while (caracter_extra != '\n' && caracter_extra != EOF);
    }
    return -2;  /* Indicamos que se excedio el largo permitido */
}

/* =========================================================================
   NORMALIZACION: trabaja IN-PLACE sobre la cadena recibida
   -------------------------------------------------------------------------
   - Recorre con dos punteros:
       puntero_lectura: lee caracter por caracter
       puntero_escritura: escribe solo los utiles, compactando
   - Quita ' ', '\t', '\r' y convierte a minuscula
   - Mantiene el '\0' final y recorta desperdicio al final
   ========================================================================= */
void ecuacion_normalizar(char *cadena_ecuacion) {
    char *puntero_lectura;
    char *puntero_escritura;
    char *ultimo_caracter_util;

    /* 1) Si el puntero es nulo, no hay nada que hacer */
    if (cadena_ecuacion == 0) return;

    /* 2) Inicializamos punteros de lectura/escritura al inicio de la cadena */
    puntero_lectura = cadena_ecuacion;
    puntero_escritura = cadena_ecuacion;
    ultimo_caracter_util = 0;

    /* 3) Recorremos toda la cadena original */
    while (*puntero_lectura != '\0') {
        char caracter_actual = *puntero_lectura;

        /* 3.a) Ignoramos espacios, tabulaciones y retornos de carro */
        if (caracter_actual != ' ' && caracter_actual != '\t' && caracter_actual != '\r') {
            /* 3.b) Convertimos a minuscula y escribimos en la posicion compactada */
            char caracter_minuscula = (char)tolower((int)caracter_actual);
            *puntero_escritura = caracter_minuscula;

            /* 3.c) Guardamos donde quedo el ultimo caracter realmente util (NO '\0') */
            if (caracter_minuscula != '\0') ultimo_caracter_util = puntero_escritura;

            /* 3.d) Avanzamos la posicion de escritura */
            puntero_escritura++;
        }

        /* 3.e) Avanzamos siempre la lectura */
        puntero_lectura++;
    }

    /* 4) Cerramos la cadena con '\0' en la nueva posicion compactada */
    *puntero_escritura = '\0';

    /* 5) Si no hubo ningun caracter util, la cadena queda vacia */
    if (ultimo_caracter_util == 0) {
        cadena_ecuacion[0] = '\0';
        return;
    }

    /* 6) Aseguramos que el '\0' quede inmediatamente despues del ultimo util */
    *(ultimo_caracter_util + 1) = '\0';
}

/* =========================================================================
   VALIDACION: helpers y reglas
   ========================================================================= */

/*  Indica si un caracter es un operador binario de los permitidos */
int es_operador_binario(char caracter) {
    return (caracter == '+' || caracter == '-' || caracter == '*' || caracter == '/' || caracter == '^');
}

/*  Determina si el literal numerico en [posicion_inicio..posicion_final) es exactamente CERO
    - Acepta formas: "0", "00", "0.0", ".0", "00.00"
    - No acepta notacion cientifica
    - cantidad_avance devuelve la cantidad de caracteres consumidos como numero
      (0 si no comienza con numero valido)
*/
int es_literal_cero(char *cadena, int posicion_inicio, int posicion_final, int *cantidad_avance) {
    int posicion_actual = posicion_inicio;
    int contiene_digito = 0;
    int contiene_digito_no_cero = 0;

    /* 1) Parte entera: consumimos digitos */
    while (posicion_actual < posicion_final &&
           cadena[posicion_actual] >= '0' && cadena[posicion_actual] <= '9') {
        if (cadena[posicion_actual] != '0') contiene_digito_no_cero = 1;
        contiene_digito = 1;
        posicion_actual++;
    }

    /* 2) Punto decimal (opcional) */
    if (posicion_actual < posicion_final && cadena[posicion_actual] == '.') {
        posicion_actual++;
        /* 3) Parte decimal: tambien opcional */
        while (posicion_actual < posicion_final &&
               cadena[posicion_actual] >= '0' && cadena[posicion_actual] <= '9') {
            if (cadena[posicion_actual] != '0') contiene_digito_no_cero = 1;
            contiene_digito = 1;
            posicion_actual++;
        }
    }

    /* 4) Cantidad de caracteres que consumimos como numero */
    if (cantidad_avance) *cantidad_avance = posicion_actual - posicion_inicio;

    /* 5) Si no hubo ningun digito, no es numero -> no es cero literal */
    if (!contiene_digito) return 0;

    /* 6) Si hubo algun digito distinto de '0', no es cero literal */
    if (contiene_digito_no_cero) return 0;

    /* 7) Si todos los digitos fueron '0' (y/o '.0...'), es cero literal */
    return 1;
}

/*  Verifica si hay DIVISION POR CERO a partir de s[posicion_division] == '/'
    - Permite parentesis envolventes: /(0), /((0.0)), etc.
    - Permite signo unario: /-0, /(-0.0)
    - Si detecta cero literal, retorna 1; si no, 0
    - 'avance' (si no es 0) recibe cuantos caracteres pertenecen al divisor inspeccionado
*/
int hay_division_por_cero_literal(char *cadena, int posicion_division, int limite_final, int *avance) {
    int posicion_actual = posicion_division + 1;
    int cantidad_parentesis_abiertos = 0;
    int cantidad_avanzada_numero = 0;

    /* 1) Salteamos cualquier cantidad de parentesis de apertura */
    while (posicion_actual < limite_final && cadena[posicion_actual] == '(') {
        cantidad_parentesis_abiertos++;
        posicion_actual++;
    }

    /* 2) Permitimos un signo menos unario delante del numero */
    if (posicion_actual < limite_final && cadena[posicion_actual] == '-') {
        posicion_actual++;
    }

    /* 3) Checamos si lo que sigue es un literal cero */
    if (es_literal_cero(cadena, posicion_actual, limite_final, &cantidad_avanzada_numero)) {
        int posicion_fin_numero = posicion_actual + cantidad_avanzada_numero;

        /* 4) Si habia parentesis, intentamos cerrarlos (si faltan, la validacion general lo marcara aparte) */
        while (posicion_fin_numero < limite_final &&
               cantidad_parentesis_abiertos > 0 &&
               cadena[posicion_fin_numero] == ')') {
            cantidad_parentesis_abiertos--;
            posicion_fin_numero++;
        }

        /* 5) Calculamos el avance total consumido del divisor inspeccionado */
        if (avance) *avance = posicion_fin_numero - (posicion_division + 1);

        /* 6) Confirmamos division por cero literal */
        return 1;
    }

    /* 7) Si no era cero literal, no hay error de este tipo aqui */
    return 0;
}

/*  Valida una EXPRESION (sin '=') en el rango [inicio, fin) de la cadena:
    - Caracteres permitidos
    - Parentesis balanceados
    - Operadores correctos (permite '-' unario)
    - NO termina en operador
    - NO contiene division por cero literal
    Retorna:
      0 OK
      1 vacia
      2 caracter invalido
      3 parentesis cerrados de mas
      4 operadores binarios seguidos
      5 termina en operador
      6 parentesis desbalanceados al final
     12 division por cero literal
    posicion_error_local (si no es 0) se setea con la posicion relativa del error
*/
int validar_expresion_simple(char *cadena, int inicio, int fin, int *posicion_error_local) {
    int cantidad_parentesis = 0;
    int ultimo_fue_operador = 1;  /* Al inicio, permitimos '-' unario */
    int posicion_actual;

    /* 1) Si el rango esta vacio, la expresion es vacia */
    if (cadena == 0 || inicio >= fin) {
        if (posicion_error_local) *posicion_error_local = 0;
        return 1;
    }

    /* 2) Recorremos caracter por caracter dentro del rango indicado */
    for (posicion_actual = inicio; posicion_actual < fin; posicion_actual++) {
        char caracter_actual = cadena[posicion_actual];

        /* 2.a) Validamos alfabeto permitido*/
        if (!((caracter_actual >= '0' && caracter_actual <= '9') ||
              caracter_actual == '.' || caracter_actual == ',' ||
              caracter_actual == 'x' || caracter_actual == 'y' ||
              caracter_actual == '+' || caracter_actual == '-' ||
              caracter_actual == '*' || caracter_actual == '/' ||
              caracter_actual == '^' || caracter_actual == '(' ||
              caracter_actual == ')' || caracter_actual == 'v'
              )) {
            if (posicion_error_local) *posicion_error_local = posicion_actual - inicio;
            return 2;
        }

        /* 2.b) Balanceo de parentesis */
        if (caracter_actual == '(') {
            cantidad_parentesis++;
        } else if (caracter_actual == ')') {
            cantidad_parentesis--;
            if (cantidad_parentesis < 0) {
                if (posicion_error_local) *posicion_error_local = posicion_actual - inicio;
                return 3;
            }
        }

        /* 2.c) Reglas de operadores (y chequear division por cero literal cuando es '/') */
        if (es_operador_binario(caracter_actual)) {
            int permite_menos_unario = (caracter_actual == '-');

            /* Chequeo especifico: divisor cero literal luego de '/' */
            if (caracter_actual == '/') {
                int avance_divisor = 0;
                if (hay_division_por_cero_literal(cadena, posicion_actual, fin, &avance_divisor)) {
                    if (posicion_error_local) *posicion_error_local = (posicion_actual - inicio) + 1; /* posicion aprox del divisor */
                    return 12;
                }
            }

            /* No permitir dos operadores binarios seguidos, salvo '-' unario */
            if (ultimo_fue_operador && !permite_menos_unario) {
                if (posicion_error_local) *posicion_error_local = posicion_actual - inicio;
                return 4;
            }

            /* Marca: acabamos de ver un operador */
            ultimo_fue_operador = 1;
        } else if (caracter_actual != '(' && caracter_actual != ',') {
            /* Cualquier cosa que no sea operador ni '(' ni ',' cuenta como "valor" */
            ultimo_fue_operador = 0;
        }
    }

    /* 3) La expresion no puede terminar en operador binario */
    if (inicio < fin) {
        char ultimo_caracter = cadena[fin - 1];
        if (es_operador_binario(ultimo_caracter)) {
            if (posicion_error_local) *posicion_error_local = (fin - 1) - inicio;
            return 5;
        }
    }

    /* 4) Parentesis deben quedar balanceados */
    if (cantidad_parentesis != 0) {
        if (posicion_error_local) *posicion_error_local = fin - inicio;
        return 6;
    }

    /* 5) Todo OK para este lado de la ecuacion */
    return 0;
}

/*  Valida la ECUACION completa con '=' aplicando validar_expresion_simple a ambos lados.
    Retorna los mismos codigos + los de igualdad:
      7 mas de un '='
      8 '=' al inicio o al final
      9 lado izquierdo vacio
     10 lado derecho vacio
     11 falta '='
*/
int ecuacion_validar(char *cadena_ecuacion, int *posicion_error) {
    int largo_total;
    int cantidad_iguales;
    int posicion_igual;
    int indice;

    /* 1) Cadena no debe ser nula ni vacia */
    if (cadena_ecuacion == 0 || *cadena_ecuacion == '\0') {
        if (posicion_error) *posicion_error = 0;
        return 1;
    }

    /* 2) Contamos simbolos '=' y guardamos la posicion del primero */
    largo_total = (int)strlen(cadena_ecuacion);
    cantidad_iguales = 0;
    posicion_igual = -1;

    for (indice = 0; indice < largo_total; indice++) {
        if (cadena_ecuacion[indice] == '=') {
            cantidad_iguales++;
            if (posicion_igual == -1) posicion_igual = indice;
        }
    }

    /* 3) Reglas sobre '=' */
    if (cantidad_iguales == 0) return 11;                 /* falta '=' */
    if (cantidad_iguales > 1) return 7;                   /* mas de uno */
    if (posicion_igual == 0 || posicion_igual == largo_total - 1) return 8; /* al inicio o al final */

    /* 4) Validamos LADO IZQUIERDO: [0 .. posicion_igual) */
    {
        int posicion_error_local = 0;
        int codigo = validar_expresion_simple(cadena_ecuacion, 0, posicion_igual, &posicion_error_local);
        if (codigo != 0) {
            if (codigo == 1) return 9;  /* lado izquierdo vacio */
            if (posicion_error) *posicion_error = posicion_error_local;
            return codigo;
        }
    }

    /* 5) Validamos LADO DERECHO: (posicion_igual .. fin] -> [posicion_igual+1 .. largo_total) */
    {
        int posicion_error_local = 0;
        int codigo = validar_expresion_simple(cadena_ecuacion, posicion_igual + 1, largo_total, &posicion_error_local);
        if (codigo != 0) {
            if (codigo == 1) return 10; /* lado derecho vacio */
            if (posicion_error) *posicion_error = (posicion_igual + 1) + posicion_error_local;
            return codigo;
        }
    }

    /* 6) Si llegamos aqui, la ecuacion es valida */
    return 0;
}

/* =========================================================================
   GUARDADO: escribe "ecuacion\n" con fprintf en la ruta indicada
   -------------------------------------------------------------------------
   - agregar_al_final = 1  => "a" (append)
   - agregar_al_final = 0  => "w" (reescribir)
   ========================================================================= */
int ecuacion_guardar_en_archivo(char *ruta_archivo, char *cadena_ecuacion, int agregar_al_final) {
    FILE *archivo;

    /* 1) Verificar argumentos */
    if (ruta_archivo == 0 || cadena_ecuacion == 0) return -1;

    /* 2) Abrir archivo en el modo solicitado */
    archivo = fopen(ruta_archivo, agregar_al_final ? "a" : "w");

    if (archivo == 0) return -2;

    /* 3) Escribir exactamente la ecuacion y un salto de linea */
    if (fprintf(archivo, "%s\n", cadena_ecuacion) < 0) {
        fclose(archivo);
        return -2;
    }

    /* 4) Cerrar archivo y retornar OK */
    fclose(archivo);
    return 0;
}

/* =========================================================================
   EJECUTORES DEL MODULO A
   -------------------------------------------------------------------------
   - moduloA_ejecutar(): usa RUTA_ARCHIVO_TEMPORAL y modo "append"
   - moduloA_ejecutar_con_ruta(): permite ruta y modo
   ========================================================================= */
int moduloA_ejecutar_con_ruta(char *ruta_archivo, int agregar_al_final) {
    char ecuacion[MAXIMO_LARGO_ECUACION];
    int resultado_operacion;
    int posicion_error_detectada = -1;

    /* 1) Pedir ecuacion al usuario con tope claro */
    puts("Ingrese la ecuacion (maximo 256 caracteres):");

    /* 2) Leer en buffer fijo */
    resultado_operacion = leer_ecuacion_en_buffer(ecuacion, MAXIMO_LARGO_ECUACION);
    if (resultado_operacion != 0) {
        if (resultado_operacion == -2) puts("La linea supera el largo maximo permitido.");
        return resultado_operacion; /* -1 (EOF/error) o -2 (excedido) */
    }

    /* 3) Normalizar (quitar espacios/tabs/CR y pasar a minuscula) */
    ecuacion_normalizar(ecuacion);
    if (ecuacion[0] == '\0') {
        puts("La ecuacion quedo vacia tras limpiar.");
        return -3;
    }

    /* 4) Validar ecuacion (incluye igualdad, operadores, parentesis y division por cero literal) */
    resultado_operacion = ecuacion_validar(ecuacion, &posicion_error_detectada);
    if (resultado_operacion != 0) {
        if (resultado_operacion == 12) {
            printf("Ecuacion invalida: division por cero literal (posicion %d).\n", posicion_error_detectada);
        } else {
            printf("Ecuacion invalida (codigo %d) en posicion %d.\n", resultado_operacion, posicion_error_detectada);
        }
        return resultado_operacion;
    }

    /* 5) Guardar en archivo temporal con fprintf("<ecuacion>\\n") */
    resultado_operacion = ecuacion_guardar_en_archivo(ruta_archivo, ecuacion, agregar_al_final);
    if (resultado_operacion != 0) {
        puts("No se pudo escribir la ecuacion en el archivo temporal.");
        return -4;
    }

    /* 6) Anunciar exito */
    puts("Ecuacion guardada correctamente.");
    return 0;
}

int moduloA_ejecutar(void) {
    /* Usamos la ruta por defecto y agregamos al final del archivo */
    return moduloA_ejecutar_con_ruta(RUTA_ARCHIVO_TEMPORAL, 1);
}

/* =========================================================================
   AYUDA: texto para guiar al usuario en el ingreso de la ecuacion
   ========================================================================= */
void imprimir_ayuda(void) {
    puts("AYUDA  Como cargar ecuaciones");
    puts("");
    puts("FORMATO GENERAL:");
    puts("  - La ecuacion debe tener un unico signo igual '=' (izquierda = derecha).");
    puts("  - No puede empezar ni terminar con '='.");
    puts("  - Se permiten espacios: el sistema los elimina al procesar.");
    puts("");
    puts("VARIABLES PERMITIDAS:");
    puts("  - x, y");
    puts("");
    puts("OPERADORES PERMITIDOS:");
    puts("  +  -  *  /  ^");
    puts("  - El signo menos unario se permite al inicio, tras otro operador o tras '('.");
    puts("");
    puts("FUNCIONES:");
    puts("  sqrt(expr)   -> raiz cuadrada");
    puts("  root(n,expr) -> raiz n-esima");
    puts("");
    puts("NUMEROS:");
    puts("  - Usar '.' para decimales (ejemplo: 3.5).");
    puts("  - No usar notacion cientifica.");
    puts("");
    puts("DIVISIONES (REGLA ESPECIAL):");
    puts("  - No se permite dividir por un cero literal: /0, /(0), /0.0, /(-0), /((0.00)), etc.");
    puts("  - Si el divisor es una variable o expresion (ej.: /x, /(x+y)), pasa esta validacion.");
    puts("");
    puts("EJEMPLOS VALIDOS:");
    puts("  y=2*x+3");
    puts("  x^2+y^2=25");
    puts("  sqrt(x)=y");
    puts("  y=root(3,x*y+2)");
    puts("");
    puts("EJEMPLOS INVALIDOS:");
    puts("  x+y           (falta '=')");
    puts("  =x+2          ('=' al inicio)");
    puts("  x+2=          ('=' al final)");
    puts("  x++y=3        (dos operadores seguidos)");
    puts("  (x+y=3        (parentesis sin cerrar)");
    puts("  y=3,5         (usar punto para decimales, no coma)");
    puts("  y=1/0         (division por cero literal)");
}
