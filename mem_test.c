#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

#define TAM_X 15
#define TAM_Y 15

int main()
{
    struct worldClass worlds;
    gol_alloc(&worlds, TAM_X, TAM_Y);
    gol_init(&worlds);
    for (int i = 0; i < 20; i++)
    {
        gol_step(&worlds);
    }
    gol_free(&worlds);

    return EXIT_SUCCESS;
}