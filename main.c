#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_X 15
#define TAM_Y 15

void gol_init(bool world[TAM_X][TAM_Y]);
void gol_print(bool world[TAM_X][TAM_Y]);
void gol_step(bool world1[TAM_X][TAM_Y], bool world2[TAM_X][TAM_Y]);
int gol_count_neighbors(bool world[TAM_X][TAM_Y], int x, int y);
bool gol_get_cell(bool world[TAM_X][TAM_Y], int x, int y );


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

void gol_init(bool world[TAM_X][TAM_Y])
{
	for(int i = 0; i < TAM_X; i++)
	{
		for(int j = 0 ; j < TAM_Y; j++)
		{
			world[i][j]  = false;
		}
	}
	world[0][1] = true;
	world[1][2] = true;
	world[2][0] = true;
	world[2][1] = true;
	world[2][2] = true;
}

void gol_print(bool world[TAM_X][TAM_Y])
{
	for(int i = 0; i < TAM_X; i++)
	{
		for(int j = 0 ; j < TAM_Y; j++)
		{
			if (world[i][j] == true) {
				printf(" X ");
			} else {
				printf(" * ");
			}
		}
		printf("\n");
	}
}

void gol_step(bool world1[TAM_X][TAM_Y], bool world2[TAM_X][TAM_Y])
{
	
	for(int i = 0; i < TAM_X; i++)
	{
		
		for(int j = 0 ; j < TAM_Y; j++)
		{
			int neighbors = gol_count_neighbors(world1, i, j);
			
			if (world1[i][j]) {
				world2[i][j] = (neighbors == 3) || (neighbors == 2);
			} else {
				world2[i][j] = (neighbors == 3);
			}
		}
	}

}

int gol_count_neighbors(bool world[TAM_X][TAM_Y], int x, int y)
{
    int neighbors = 0;
    
	neighbors += gol_get_cell(world, x - 1, y - 1);
	neighbors += gol_get_cell(world, x - 0, y - 1);
	neighbors += gol_get_cell(world, x + 1, y - 1);

	neighbors += gol_get_cell(world, x - 1, y - 0);
	neighbors += gol_get_cell(world, x + 1, y - 0);
	
	neighbors += gol_get_cell(world, x - 1, y + 1);
	neighbors += gol_get_cell(world, x - 0, y + 1);
	neighbors += gol_get_cell(world, x + 1, y + 1);
	
	return neighbors;
}

bool gol_get_cell(bool world[TAM_X][TAM_Y], int x, int y)
{
	bool *min = &world[0][0];
	bool *max = &world[TAM_X - 1][TAM_Y - 1];
	
	if (&world[x][y]  < min || &world[x][y]  > max)
		return false;	
	return world[x][y];
}


