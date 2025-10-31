#include "Pila.h"


// Inicializa una pila vacía.
void inicializarPila(Pila* pila) {
    pila->tope = NULL;
}

// Verifica si la pila está vacía.
int pilaVacia(Pila* pila) {
    return pila->tope == NULL;
}

// Apila (push): agrega un elemento al tope.
void apilar(Pila* pila, void* valor) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        exit(1);
    }
    nuevo->dato = valor;
    nuevo->siguiente = pila->tope;
    pila->tope = nuevo;
}

// Desapila (pop): quita y devuelve el elemento del tope.
void* desapilar(Pila* pila) {
    Nodo* temp;
    void* valor;
    if (pilaVacia(pila)) {
        printf("Error: la pila está vacía.\n");
        exit(1);
    }

    temp = pila->tope;
    valor = temp->dato;
    pila->tope = temp->siguiente;
    free(temp);
    return valor;
}

// Devuelve el elemento del tope sin quitarlo.
const void* verTope(Pila* pila) {
    if (pilaVacia(pila)) {
        printf("Error: la pila está vacía.\n");
        exit(1);
    }
    return pila->tope->dato;
}

// Vacia toda la memoria de la pila. Se recomienda usar cuando
// se quiere reiniciar la pila.
void vaciarPila(Pila* pila) {
    void* d;
    while (!pilaVacia(pila)) {
        d = desapilar(pila);
        free(d);
    }
}

// Vacia toda la memoria de la pila y la libera.
void liberarPila(Pila* pila) {
    if (!pilaVacia(pila))
    {
        vaciarPila(pila);
    }
    free(pila);
}
