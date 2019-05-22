#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void gol_init();
void gol_print();
void gol_step();
int gol_count_neighbors();
bool gol_get_cell();
void gol_copy();


int main()
{
	bool world1[5][5];
	bool world2[5][5];
	int i = 0;
	
	gol_init(world1);

	do {
		printf("\033cIteration %d\n", i++);
		gol_print(world1);
		gol_step(world1, world2);
	} while (getchar() != 'q');

	return EXIT_SUCCESS;
}

void gol_init(bool *world)
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0 ; j < 5; j++)
		{
			if (j > 0 && j < 4 && i == 2){
				*((world + j + i*5)) = true;
			} else {
				*(world + j + i*5) = false;
			}
		}
	}	
}
void gol_print(bool *world)
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0 ; j < 5; j++)
		{
			if (*(world + j + i*5) == true) {
				printf("@");
			} else {
				printf("-");
			}
		}
		printf("\n");
	}
}

void gol_step(bool *world1, bool *world2)
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0 ; j < 5; j++)
		{
			*(world2 +j +i*5) = gol_get_cell(world1, i, j);
		}
	}
	gol_copy(world1, world2);
}

int gol_count_neighbors(bool *world, int i, int j)
{

    bool *min = world;
    bool *max = world + (5*5)-1;
	int neighbors = 0;
    if((world + j + (i*5)) >= min && (world + j + (i*5)) <= max) {
		if (world + (j - 1) + ((i*5)-1) >= min && world + (j - 1) + ((i*5)-1) <= max && *(world + (j - 1)+ ((i*5)-1)) == true){
			neighbors ++;
		}
		if (world + j + ((i*5)-1) >= min && world + j + ((i*5)-1) <= max && *(world + j + ((i*5)-1)) == true){
			neighbors ++;
		}
		if (world + (j + 1) + ((i*5)-1) >= min && world + (j + 1) + ((i*5)-1) <= max && *(world + (j + 1) + ((i*5)-1)) == true){
			neighbors ++;
		}
		if (world + (j - 1) + (i*5) >= min && world + (j - 1) + (i*5) <= max && *(world + (j - 1) + (i*5)) == true){
			neighbors ++;
		}
		if (world + (j + 1) + (i*5) >= min && world + (j + 1) + (i*5) <= max && *(world + (j + 1) + (i*5)) == true){
			neighbors ++;
		}
		if (world + (j - 1) + ((i*5)+1) >= min && world + (j - 1) + ((i*5)+1) <= max && *(world + (j - 1) + ((i*5)+1)) == true){
			neighbors ++;
		}
		if (world + j + ((i*5)+1) >= min && world + j + ((i*5)+1) <= max && *(world + j + ((i*5)+1)) == true){
			neighbors ++;
		}
		if (world + (j + 1) + ((i*5)+1) >= min && world + (j + 1) + ((i*5)+1) <= max && *(world + (j + 1) + ((i*5)+1)) == true){
			neighbors ++;
		}
	}
	return neighbors;
	
}


bool gol_get_cell(bool *world, int i, int j )
{
	bool stats = false;
	if(gol_count_neighbors(world, i, j) == 3 || gol_count_neighbors(world, i, j) == 2){
	stats= true;
	} 
	return stats;
}

void gol_copy(bool *world1, bool *world2)
{
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0 ; j < 5; j++)
		{
			*(world1 +j +i*5) = *(world2 +j +i*5);
		}
	} 
}
