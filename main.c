#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
	int i = 0;
	struct worldClass wordlsObject;
	gol_init(&wordlsObject);
	do
	{
		printf("\033cIteration %d\n", i++);
		gol_print(&wordlsObject);
		gol_step(&wordlsObject);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}
