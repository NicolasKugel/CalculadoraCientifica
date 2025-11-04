#include "reemplazar_variables.h"

// convierto valor de double a string
char* doubleAString(double val)
{
    char* buffer = NULL;
    char* buffer_aux = NULL;
    int len = 0;
    buffer_aux = (char*) malloc(TAM_NUM);
    if(val == trunc(val))
    {
        sprintf(buffer_aux, "%.0lf", val);
    }
    else
    {
        sprintf(buffer_aux, "%lf", val);
    }
    len = strlen(buffer_aux);
    buffer = (char*) malloc(len + 1);
    memcpy(buffer, buffer_aux, len + 1);
    free(buffer_aux);
    return buffer;
}

// reemplazo las ocurrencias de x e y en la funcion con sus respectivos valores
char* reemplazarVariables(char* func, double val_x, double val_y)
{
    char* buffer = malloc(sizeof(char));
    int len_aux = 0, len_buff = 0;
    *buffer = '\0';
    while(*func)
    {
        if(*func=='x'||*func=='X')
        {
            char* aux_x;
            aux_x = doubleAString(val_x);
            len_aux = strlen(aux_x);
            if(val_x<0)
            {
                len_buff = strlen(buffer);
                buffer = (char*) realloc(buffer, len_buff + len_aux + 3);
                strcat(buffer,"(");
                strcat(buffer,aux_x);
                strcat(buffer,")");
            }
            else
            {
                len_buff = strlen(buffer);
                buffer = (char*) realloc(buffer, len_buff + len_aux + 1);
                strcat(buffer,aux_x);
            }
            free(aux_x);
            func++;
        }
        else if (*func=='y'||*func=='Y')
        {
            char* aux_y;
            aux_y = doubleAString(val_y);
            len_aux = strlen(aux_y);
            if(val_y<0)
            {
                len_buff = strlen(buffer);
                buffer = (char*) realloc(buffer, len_buff + len_aux + 3);
                strcat(buffer,"(");
                strcat(buffer,aux_y);
                strcat(buffer,")");
            }
            else
            {
                len_buff = strlen(buffer);
                buffer = (char*) realloc(buffer, len_buff + len_aux + 1);
                strcat(buffer,aux_y);
            }
            free(aux_y);
            func++;
        }
        else
        {
            len_buff = strlen(buffer);
            buffer = (char*) realloc(buffer, len_buff + 2);
            buffer[len_buff] = *func;
            buffer[len_buff+1] = '\0';
            func++;
        }
    }
    return buffer;
}
