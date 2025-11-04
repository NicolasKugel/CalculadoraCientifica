#include "parser_funciones.h"


// ---- PRIORIDAD DE OPERADORES ----
int __prioridad(char op) {
    switch(op) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '^': return 3;
        case 'v': return 3;
        default: return 0;
    }
}

// Función para calcular la raíz x-ésima de un número
double __raiz(double numero, double x) {
    double result;
    if(numero < 0.0 && fmod(x,2.0) != 0.0)
    {
        result = pow((numero * -1), 1.0 / x);
        return (result * -1);
    }
    else
    {
        return pow(numero, 1.0 / x);
    }

}

char* devolverMsgError(int cod_error)
{
    char* error = NULL;
    char* aux = malloc(TAM_MSG_ERR);
    int len_err = 0;
    switch(cod_error)
    {
        case 1:
            len_err = sprintf(aux, "Error: division por 0");
            break;
        case 2:
            len_err = sprintf(aux, "Error: Indeterminacion de 0 elevado a la 0");
            break;
        case 3:
            len_err = sprintf(aux, "Error: indice de raiz igual a 0");
            break;
        case 4:
            len_err = sprintf(aux, "Error: Raiz de base negativa con indice par");
            break;
    }
    error = (char*) malloc(len_err + 1);
    memcpy(error,aux,len_err + 1);
    free(aux);
    return error;
}

// Algoritmo Shunting Yard

// ---- CONVERSIÓN INFIX -> POSTFIX ----
char* __infix_a_postfix(const char* infix) {
    Pila pila;
    size_t n = strlen(infix);
    char* postfix;
    const char* ptr = infix;
    inicializarPila(&pila);
    postfix = (char*)malloc(2 * n + 1);
    if (!postfix) exit(1);
    char* out = postfix;

    while (*ptr)
    {
        char* op;
        if (isspace(*ptr))
        {
            ptr++;
            continue;
        }
        // número
        if (isdigit(*ptr) || *ptr == '.')
        {
            while (isdigit(*ptr) || *ptr == '.')
            {
                *out++ = *ptr++;
            }
            *out++ = ' ';
            continue;
        }
        // paréntesis
        if (*ptr == '(')
        {
            op = malloc(sizeof(char));
            *op = *ptr;
            apilar(&pila, op);
            ptr++;
            if(*ptr == '-')
            {
                ptr++;
                if(isdigit(*ptr))
                {
                    ptr--;
                    *out++ = *ptr++;
                    while (isdigit(*ptr) || *ptr == '.')
                    {
                        *out++ = *ptr++;
                    }
                    *out++ = ' ';
                    continue;
                }
                else
                {
                    ptr--;
                    ptr--;
                }
            }
            else
            {
                ptr--;
            }
        }
        else if (*ptr == ')')
        {
            while (!pilaVacia(&pila) && *((char*)verTope(&pila)) != '(')
            {
                *out++ = *((char*)desapilar(&pila));
                *out++ = ' ';
            }
            free(desapilar(&pila)); // eliminar '('
        }
        // operadores
        else if (strchr("+-*/^v", *ptr))
        {
            while (!pilaVacia(&pila) &&
                   __prioridad(*((char*)verTope(&pila))) >= __prioridad(*ptr))
            {
                *out++ = *((char*)desapilar(&pila));
                *out++ = ' ';
            }
            op = malloc(sizeof(char));
            *op = *ptr;
            apilar(&pila, op);
        }
        ptr++;
    }

    while (!pilaVacia(&pila))
    {
        *out++ = *((char*)desapilar(&pila));
        *out++ = ' ';
    }

    *out = '\0';
    vaciarPila(&pila);
    return postfix;
}

// ---- EVALUACIÓN DE POSTFIX ----
char* __eval_postfix(const char *postfix) {
    char* resultado = NULL;
    const char *ptr = postfix;
    Pila pila;
    inicializarPila(&pila);
    while(*ptr)
    {
        if(isspace(*ptr))
        {
            ptr++;
            continue;
        }
        if (isdigit(*ptr) || *ptr == '.') {
            char* end;
            double* num = malloc(sizeof(double));
            *num = strtod(ptr, &end);
            apilar(&pila, num);
            ptr = end;
            continue;
        }
        if(*ptr == '-')
        {
            ptr++;
            if(isdigit(*ptr))
            {
                char* end;
                double* num = malloc(sizeof(double));
                ptr--;
                *num = strtod(ptr, &end);
                apilar(&pila, num);
                ptr = end;
                continue;
            }
            else
            {
                ptr--;
            }
        }
        if(strchr("+-*/^v", *ptr))
        {
            double* b = (double*)desapilar(&pila);
            double* a = (double*)desapilar(&pila);
            double* r = malloc(sizeof(double));
            switch (*ptr) {
                case '+':
                    *r = *a + *b;
                    break;
                case '-':
                    *r = *a - *b;
                    break;
                case '*':
                    *r = *a * *b;
                    break;
                case '/':
                    if(*b==0.0)
                    {
                        free(a);
                        free(b);
                        free(r);
                        return devolverMsgError(1);
                    }
                    else
                    {
                        *r = *a / *b;
                        break;
                    }
                case '^':
                    if(*a==0.0&&*b==0.0)
                    {
                        free(a);
                        free(b);
                        free(r);
                        return devolverMsgError(2);
                    }
                    else
                    {
                        *r = pow(*a, *b);
                        break;
                    }
                case 'v':
                    if (*a==0.0)
                    {
                        free(a);
                        free(b);
                        free(r);
                        return devolverMsgError(3);
                    }
                    else if (*b < 0.0 && fmod(*a,2.0) == 0.0)
                    {
                        free(a);
                        free(b);
                        free(r);
                        return devolverMsgError(4);
                    }
                    else
                    {
                        *r = __raiz(*b, *a);
                        break;
                    }
            }
            free(a);
            free(b);
            apilar(&pila, r);
        }
        ptr++;
    }

    resultado = doubleAString(*((double*)verTope(&pila)));
    vaciarPila(&pila);
    return resultado;
}

char* resolverFuncion(char* fx, double var_x, double var_y)
{
    char* funcReemplazada = NULL;
    char* funcPostfix = NULL;
    char* resultado;
    funcReemplazada = reemplazarVariables(fx, var_x, var_y);
    funcPostfix = __infix_a_postfix(funcReemplazada);
    resultado = __eval_postfix(funcPostfix);
    free(funcReemplazada);
    free(funcPostfix);
    return resultado;
}
