#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define TAM_X 15
#define TAM_Y 15

void gol_init(bool world[TAM_X][TAM_Y]);
void gol_print(bool world[TAM_X][TAM_Y]);
void gol_step(bool world1[TAM_X][TAM_Y], bool world2[TAM_X][TAM_Y]);
int gol_count_neighbors(bool world[TAM_X][TAM_Y], int x, int y);
bool gol_get_cell(bool world[TAM_X][TAM_Y], int x, int y );
