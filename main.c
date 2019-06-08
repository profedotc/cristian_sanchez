#include <stdio.h>
#include <stdbool.h>
#include "gol.h"

int main()
{
	bool world[2][TAM_X][TAM_Y];
	int i = 0;
	
	
	gol_init(world[0]);

	do {
		printf("\033cIteration %d\n", i);
		
		if(i%2 == 0){
			gol_print(world[0]);
			gol_step(world[0], world[1]);
		} else {
			gol_print(world[1]);
			gol_step(world[1], world[0]);
		}
		i++;
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}
