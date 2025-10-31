#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Estructura para un nodo de la pila
typedef struct Nodo {
    void* dato;
    struct Nodo* siguiente;
} Nodo;

// Estructura principal de la pila
typedef struct {
    Nodo* tope;
} Pila;


void inicializarPila(Pila*);

int pilaVacia(Pila*);

void apilar(Pila*, void*);

void* desapilar(Pila*);

const void* verTope(Pila*);

void vaciarPila(Pila* pila);

void liberarPila(Pila* pila);


#endif // PILA_H_INCLUDED
