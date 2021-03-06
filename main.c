#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

#define TAM_X 15
#define TAM_Y 15

int main()
{
	int i = 0;
	struct worldClass worlds;
	bool check = gol_alloc(&worlds, TAM_X, TAM_Y);
	if(!check){
		printf("***NO SE PUEDE ASIGNAR LA MEMORIA***\n");
		exit(EXIT_FAILURE);
	}
	gol_init(&worlds);
	do
	{
		printf("\033cIteration %d\n", i++);
		gol_print(&worlds);
		gol_step(&worlds);
	} while (getchar() != 'q');

	gol_free(&worlds);

	return EXIT_SUCCESS;
}
