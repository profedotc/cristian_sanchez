#include "gol.h"

static int count_neighbors(const struct worldClass *worlds, int x, int y);
static bool get_cell(const struct worldClass *worlds, int x, int y);

enum world_used
{
	currentWorld = false,
	nextWorld,
};

void gol_init(struct worldClass *worlds)
{
	for (int i = 0; i < worlds->tamX; i++)
	{
		for (int j = 0; j < worlds->tamY; j++)
		{
			worlds->worlds[currentWorld][i][j] = false;
		}
	}
	worlds->worlds[currentWorld][0][1] = true;
	worlds->worlds[currentWorld][1][2] = true;
	worlds->worlds[currentWorld][2][0] = true;
	worlds->worlds[currentWorld][2][1] = true;
	worlds->worlds[currentWorld][2][2] = true;
}

void gol_print(const struct worldClass *worlds)
{
	for (int i = 0; i < worlds->tamX; i++)
	{
		for (int j = 0; j < worlds->tamY; j++)
		{
			if (worlds->worlds[currentWorld][i][j] == true)
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

void gol_step(struct worldClass *worlds)
{

	for (int i = 0; i < worlds->tamX; i++)
	{

		for (int j = 0; j < worlds->tamY; j++)
		{
			int neighbors = count_neighbors(worlds, i, j);

			if (worlds->worlds[currentWorld][i][j])
			{
				worlds->worlds[nextWorld][i][j] = (neighbors == 3) || (neighbors == 2);
			}
			else
			{
				worlds->worlds[nextWorld][i][j] = (neighbors == 3);
			}
		}
	}

	bool **auxp = worlds->worlds[currentWorld];
	worlds->worlds[currentWorld] = worlds->worlds[nextWorld];
	worlds->worlds[nextWorld] = auxp;
}

int count_neighbors(const struct worldClass *worlds, int x, int y)
{
	int neighbors = 0;

	neighbors += get_cell(worlds, x - 1, y - 1);
	neighbors += get_cell(worlds, x - 0, y - 1);
	neighbors += get_cell(worlds, x + 1, y - 1);

	neighbors += get_cell(worlds, x - 1, y - 0);
	neighbors += get_cell(worlds, x + 1, y - 0);

	neighbors += get_cell(worlds, x - 1, y + 1);
	neighbors += get_cell(worlds, x - 0, y + 1);
	neighbors += get_cell(worlds, x + 1, y + 1);

	return neighbors;
}

bool get_cell(const struct worldClass *worlds, int x, int y)
{
	bool *min = &worlds->worlds[currentWorld][0][0];
	bool *max = &worlds->worlds[currentWorld][worlds->tamX - 1][worlds->tamY - 1];

	if (&worlds->worlds[currentWorld][x][y] < min || &worlds->worlds[currentWorld][x][y] > max)
		return false;
	return &worlds->worlds[currentWorld][x][y];
}

void gol_alloc(struct worldClass *worlds, int tamX, int tamY)
{
	worlds->worlds[currentWorld] = (bool **)malloc(tamX * sizeof(bool *));
	worlds->worlds[nextWorld] = (bool **)malloc(tamX * sizeof(bool *));
	for (int i = 0; i < tamX; i++)
	{
		worlds->worlds[currentWorld][i] = (bool *)malloc(tamY * sizeof(bool));
		worlds->worlds[nextWorld][i] = (bool *)malloc(tamY * sizeof(bool));
	}
	worlds->tamX = tamX;
	worlds->tamY = tamY;
}

void gol_free(struct worldClass *worlds)
{
	for (int i = 0; i < worlds->tamX; i++)
	{
		free(worlds->worlds[nextWorld][i]);
		free(worlds->worlds[currentWorld][i]);
	}

	free(worlds->worlds[nextWorld]);
	free(worlds->worlds[currentWorld]);
}