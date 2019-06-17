#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define TAM_X 15
#define TAM_Y 15

struct worldClass
{
	bool worlds[2][TAM_X][TAM_Y];
	bool wordlUsed;
};

void gol_init(struct worldClass *wordlsObject);
void gol_print(const struct worldClass *wordlsObject);
void gol_step(struct worldClass *wordlsObject);
int gol_count_neighbors(bool world[TAM_X][TAM_Y], int x, int y);
bool gol_get_cell(bool world[TAM_X][TAM_Y], int x, int y);
