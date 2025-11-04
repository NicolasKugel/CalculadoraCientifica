#ifndef MODULOA_H
#define MODULOA_H

/* =====================================================================
   CONFIGURACION / CONSTANTES
   ---------------------------------------------------------------------
   - MAXIMO_LARGO_ECUACION: tope logico para leer una ecuacion desde stdin
   - RUTA_ARCHIVO_TEMPORAL: ruta por defecto para guardar las ecuaciones
   ===================================================================== */
#define MAXIMO_LARGO_ECUACION 256
#define RUTA_ARCHIVO_TEMPORAL "ecuaciones/ecuaciones-sesion-actual.tmp"

/* =====================================================================
   moduloA_ejecutar():
     1) Solicita la ecuacion al usuario (stdin) con tope MAXIMO_LARGO_ECUACION
     2) Normaliza (quita espacios/tabs/CR y pasa a minuscula)
     3) Valida:
        - Debe haber un unico '=' (no al inicio ni al final)
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
     - Reglas generales de la ecuacion:
       * Debe haber exactamente UN '='
       * No al inicio ni al final
       * Ambos lados deben ser expresiones validas
     - Reglas de cada expresion:
       * Caracteres permitidos: digitos [0-9], '.', ',', 'x', 'y'
         operadores '+', '-', '*', '/', '^', parentesis '(' y ')'
         y letras 's','q','r','t','o' (para "sqrt" y "root")
       * Parentesis balanceados
       * No dos operadores binarios seguidos (permite '-' unario)
       * No termina en operador binario
       * SIN division por cero literal (ej.: /0, /(0), /0.0, /(-0))
     Codigos de retorno:
       0  OK
       1  vacia (o algun lado vacio)
       2  caracter invalido
       3  parentesis cerrados de mas
       4  operadores binarios seguidos
       5  termina en operador
       6  parentesis desbalanceados
       7  mas de un '='
       8  '=' al inicio o al final
       9  lado izquierdo vacio
      10  lado derecho vacio
      11  falta '='
      12  division por cero literal
     *posicion_error (si no es 0) recibe la posicion aproximada del problema
   ===================================================================== */
int ecuacion_validar(char *cadena_ecuacion, int *posicion_error);

/* =====================================================================
   GUARDADO EN ARCHIVO
   ---------------------------------------------------------------------
   ecuacion_guardar_en_archivo:
     - Abre la ruta indicada en modo append (agregar_al_final=1) o write (0)
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
