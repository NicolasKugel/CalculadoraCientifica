#ifndef PARSER_FUNCIONES_H_INCLUDED
#define PARSER_FUNCIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "Pila.h"
#include "reemplazar_variables.h"

#define TAM_MSG_ERR 61


char* resolverFuncion(char* func, double val_x, double val_y);


#endif // PARSER_FUNCIONES_H_INCLUDED
