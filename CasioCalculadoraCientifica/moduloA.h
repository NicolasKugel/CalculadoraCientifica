/* Prototipo de funci�n: leer ecuaci�n */
int leer_ecuacion_simple(char *dst, size_t tam);

/* Quita el '\n' final si existe. */
void cadena_quitar_nueva_linea(char *s);

/* Recorta espacios al inicio y al final (in-place). */
void cadena_recortar_bordes(char *s);

/* Elimina TODOS los espacios y tabulaciones internos (in-place). */
void cadena_quitar_espacios(char *s);

/* Convierte a min�sculas (ASCII) in-place. */
void cadena_a_minusculas(char *s);

/* Devuelve 1 si la cadena est� vac�a o solo tiene espacios/blancos; 0 en caso contrario. */
int cadena_es_blanca(const char *s);
