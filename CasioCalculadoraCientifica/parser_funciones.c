#include "parser_funciones.h"


// ---- PRIORIDAD DE OPERADORES ----
int prioridad(char op) {
    switch(op) {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '^': return 3;
        case 'V': return 3;
        default: return 0;
    }
}


// Función para calcular la raíz x-ésima de un número
double raiz(double numero, double x) {
    double result;
    if (x == 0) {
        printf("La raíz x-ésima con x = 0 no es válida.\n");
        return -1; // Retorna -1 como un valor indicativo de error
    }

    if(numero < 0.0 && fmod(x,2.0) != 0.0)
    {
        result = pow((numero * -1), 1.0 / x);
        return (result * -1);
    }
    else if (numero < 0.0 && fmod(x,2.0) == 0.0)
    {
        printf("No se puede aplicar raiz par a un nro negativo.\n");
        return -1; // Retorna -1 como un valor indicativo de error
    }
    else
    {
        return pow(numero, 1.0 / x);
    }

}


// Algoritmo Shunting Yard

// ---- CONVERSIÓN INFIX -> POSTFIX ----
char* infix_a_postfix(const char* infix) {
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
        else if (strchr("+-*/^V", *ptr))
        {
            while (!pilaVacia(&pila) &&
                   prioridad(*((char*)verTope(&pila))) >= prioridad(*ptr))
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
double eval_postfix(const char *postfix) {
    double resultado;
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

        if(strchr("+-*/^V", *ptr))
        {
            double* b = (double*)desapilar(&pila);
            double* a = (double*)desapilar(&pila);
            double* r = malloc(sizeof(double));
            switch (*ptr) {
                case '+': *r = *a + *b; break;
                case '-': *r = *a - *b; break;
                case '*': *r = *a * *b; break;
                case '/': *r = *a / *b; break;
                case '^': *r = pow(*a, *b); break;
                case 'V': *r = raiz(*b, *a); break;
            }
            free(a);
            free(b);
            apilar(&pila, r);
        }
        ptr++;
    }

    resultado = *((double*)verTope(&pila));
    vaciarPila(&pila);
    return resultado;
}
