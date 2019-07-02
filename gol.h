#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef _GOL_H_
#define _GOL_H_

struct worldClass
{
	bool **worlds[2];
	int tamX;
	int tamY;
};

void gol_init(struct worldClass *worlds);
void gol_print(const struct worldClass *worlds);
void gol_step(struct worldClass *worlds);
void gol_alloc(struct worldClass *worlds, int tamX, int tamY);
void gol_free(struct worldClass *worlds);

#endif