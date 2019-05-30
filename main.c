#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_X 5
#define TAM_Y 5

void gol_init(bool world[TAM_X][TAM_Y]);
void gol_print(bool world[TAM_X][TAM_Y]);
void gol_step(bool world1[TAM_X][TAM_Y], bool world2[TAM_X][TAM_Y]);
int gol_count_neighbors(bool world[TAM_X][TAM_Y], int x, int y);
bool gol_get_cell(bool world[TAM_X][TAM_Y], int x, int y );
void gol_copy(bool world1[TAM_X][TAM_Y], bool world2[TAM_X][TAM_Y]);


int main()
{
	bool world1[TAM_X][TAM_Y];
	bool world2[TAM_X][TAM_Y];
	int i = 0;
	
	gol_init(world1);

	do {
		printf("\033cIteration %d\n", i++);
		gol_print(world1);
		gol_step(world1, world2);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void gol_init(bool world[TAM_X][TAM_Y])
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0 ; j < 5; j++)
		{
			if (j > 0 && j < 4 && i == 2){
				world[i][j] = true;
			} else {
				world[i][j]  = false;
			}
		}
	}	
}
void gol_print(bool world[TAM_X][TAM_Y])
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0 ; j < 5; j++)
		{
			if (world[i][j] == true) {
				printf("@");
			} else {
				printf("-");
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
			int neighbors = 0;
			neighbors = gol_count_neighbors(world1, i, j);
			
			if( neighbors == 2 || neighbors == 3){
				world2[i][j] = true;
			} else {
				world2[i][j] = false;
			}
			printf("%d vecinas\n\n", neighbors);
			printf("X= %d	Y= %d\n", i, j);
			
		}
	}

	gol_copy(world1, world2);
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
	if (x < 0 || x >= TAM_X || y < 0 || y >= TAM_Y)
		return false;
	return world[x][y];
}

void gol_copy(bool world1[TAM_X][TAM_Y], bool world2[TAM_X][TAM_Y])
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0 ; j < 5; j++)
		{
			world1[i][j] = world2[i][j];
		}
	} 
}
