#include "gol.h"

static int count_neighbors(bool world[TAM_X][TAM_Y], bool *position);
static bool get_cell(bool world[TAM_X][TAM_Y], bool *position);

void gol_init(struct worldClass *wordlsObject)
{
	wordlsObject->wordlUsed = false;
	for (int i = 0; i < TAM_X; i++)
	{
		for (int j = 0; j < TAM_Y; j++)
		{
			wordlsObject->worlds[wordlsObject->wordlUsed][i][j] = false;
		}
	}
	wordlsObject->worlds[wordlsObject->wordlUsed][0][1] = true;
	wordlsObject->worlds[wordlsObject->wordlUsed][1][2] = true;
	wordlsObject->worlds[wordlsObject->wordlUsed][2][0] = true;
	wordlsObject->worlds[wordlsObject->wordlUsed][2][1] = true;
	wordlsObject->worlds[wordlsObject->wordlUsed][2][2] = true;
}

void gol_print(const struct worldClass *wordlsObject)
{
	for (int i = 0; i < TAM_X; i++)
	{
		for (int j = 0; j < TAM_Y; j++)
		{
			if (wordlsObject->worlds[wordlsObject->wordlUsed][i][j] == true)
			{
				printf(" X ");
			}
			else
			{
				printf(" * ");
			}
		}
		printf("\n");
	}
}

void gol_step(struct worldClass *wordlsObject)
{

	for (int i = 0; i < TAM_X; i++)
	{

		for (int j = 0; j < TAM_Y; j++)
		{
			int neighbors = count_neighbors(wordlsObject->worlds[wordlsObject->wordlUsed], &wordlsObject->worlds[wordlsObject->wordlUsed][i][j]);

			if (wordlsObject->worlds[wordlsObject->wordlUsed][i][j])
			{
				wordlsObject->worlds[!wordlsObject->wordlUsed][i][j] = (neighbors == 3) || (neighbors == 2);
			}
			else
			{
				wordlsObject->worlds[!wordlsObject->wordlUsed][i][j] = (neighbors == 3);
			}
		}
	}
	wordlsObject->wordlUsed = !wordlsObject->wordlUsed;
}

int count_neighbors(bool world[TAM_X][TAM_Y], bool *position)
{
	int neighbors = 0;

	neighbors += get_cell(world, (position-(TAM_Y-1)));	
	neighbors += get_cell(world, (position-TAM_Y));	
	neighbors += get_cell(world, (position-(TAM_Y+1)));

	neighbors += get_cell(world, (position+1));	
	neighbors += get_cell(world, (position-1));
		
	neighbors += get_cell(world, (position+(TAM_Y-1)));	
	neighbors += get_cell(world, (position+TAM_Y));	
	neighbors += get_cell(world, (position+(TAM_Y+1)));

	return neighbors;
}

bool get_cell(bool world[TAM_X][TAM_Y], bool *position)
{

	bool *min = &world[0][0];
	bool *max = &world[TAM_X - 1][TAM_Y - 1];

	if (position < min || position > max)
		return false;
	return *position;
}
