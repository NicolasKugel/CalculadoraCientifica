#ifndef MODULOA_H
#define MODULOA_H

/* =====================================================================
   moduloA_ejecutar():
     1) Solicita la ecuacion al usuario (stdin) con tope MAXIMO_LARGO_ECUACION
     2) Normaliza
     3) Valida:
        - Parentesis balanceados
        - Operadores correctos (permite '-' unario)
        - SIN division por cero literal (ej.: /0, /(0), /0.0, /(-0))
     4) Si todo OK, guarda "ecuacion\n" en RUTA_ARCHIVO_TEMPORAL con fprintf
   Retorna:
     0  -> OK (guardada)
    -1  -> EOF / error de lectura
    -2  -> linea excedida (se trunco y se consumio el resto)
    -3  -> ecuacion vacia tras limpiar
    -4  -> error de archivo al guardar
    >0  -> codigo de error de validacion (ver ecuacion_validar)
   ===================================================================== */
int moduloA_ejecutar(void);

/* Variante para indicar otra ruta y modo de escritura:
   - ruta_archivo: archivo destino
   - agregar_al_final: 1 para append, 0 para reescribir
*/
int moduloA_ejecutar_con_ruta(char *ruta_archivo, int agregar_al_final);

/* =====================================================================
   UTILIDADES DE I/O
   ---------------------------------------------------------------------
   leer_ecuacion_en_buffer:
     - Lee una linea de stdin dentro de 'destino' (tam incluye el '\0')
     - Quita el '\n' final si entro
     - Si se excede el tope, consume el resto hasta '\n'
     Retorna: 0 OK, -1 EOF/error, -2 excedido
   ===================================================================== */
int leer_ecuacion_en_buffer(char *destino, int tamanio);

/* =====================================================================
   NORMALIZACION
   ---------------------------------------------------------------------
   ecuacion_normalizar:
     - Trabaja IN-PLACE sobre la misma cadena
     - Quita espacios ' ', tabulaciones '\t' y retorno de carro '\r'
     - Convierte todo a minuscula
     - Mantiene un unico '\0' final
   ===================================================================== */
void ecuacion_normalizar(char *cadena_ecuacion);

/* =====================================================================
   VALIDACION
   ---------------------------------------------------------------------
   ecuacion_validar:
     - Reglas de cada expresion:
       * Caracteres permitidos: digitos [0-9], '.', ',', 'x', 'y'
         operadores '+', '-', '*', '/', '^', parentesis '(' y ')'
         y 'v'
       * Parentesis balanceados
       * No dos operadores binarios seguidos (permite '-' unario)
       * No termina en operador binario
       * SIN division por cero literal (ej.: /0, /(0), /0.0, /(-0))
   ===================================================================== */
int ecuacion_validar(char *cadena_ecuacion, int *posicion_error);

/* =====================================================================
   GUARDADO EN ARCHIVO
   ---------------------------------------------------------------------
   ecuacion_guardar_en_archivo:
     - Escribe exactamente: "<ecuacion>\n"
     Retorna: 0 OK, -1 argumentos invalidos, -2 error de archivo
   ===================================================================== */
int ecuacion_guardar_en_archivo(char *ruta_archivo, char *cadena_ecuacion, int agregar_al_final);

/* =====================================================================
   AYUDA
   ---------------------------------------------------------------------
   imprimir_ayuda:
     - Muestra por pantalla las reglas de ingreso de ecuaciones
   ===================================================================== */
void imprimir_ayuda(void);


#endif
