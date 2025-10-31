#ifndef PARSER_FUNCIONES_H_INCLUDED
#define PARSER_FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "Pila.h"

int prioridad(char);

double raiz(double, double);

char* infix_a_postfix(const char*);

double eval_postfix(const char*);


#endif // PARSER_FUNCIONES_H_INCLUDED
