#include "Utils.h"

void clearScreen()
{
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitEnter()
{
    while (getchar() != '\n'); // limpia el buffer
    printf("\nPresiona Enter para continuar...");
    getchar();
}
