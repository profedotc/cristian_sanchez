#include "gol.h"

static int count_neighbors(const struct worldClass *worlds, int x, int y);
static bool get_cell(const struct worldClass *worlds, int x, int y);

enum world_used
{
	CURRENTWORLD,
	NEXTWORLD,
};

void gol_alloc(struct worldClass *worlds, int tamX, int tamY)
{
	worlds->worlds[CURRENTWORLD] = (bool **)malloc(tamX * sizeof(bool *));
	worlds->worlds[NEXTWORLD] = (bool **)malloc(tamX * sizeof(bool *));
	for (int i = 0; i < tamX; i++)
	{
		worlds->worlds[CURRENTWORLD][i] = (bool *)malloc(tamY * sizeof(bool));
		worlds->worlds[NEXTWORLD][i] = (bool *)malloc(tamY * sizeof(bool));
	}
	worlds->tamX = tamX;
	worlds->tamY = tamY;
}

void gol_free(struct worldClass *worlds)
{
	for (int i = 0; i < worlds->tamX; i++)
	{
		free(worlds->worlds[NEXTWORLD][i]);
		free(worlds->worlds[CURRENTWORLD][i]);
	}

	free(worlds->worlds[NEXTWORLD]);
	free(worlds->worlds[CURRENTWORLD]);
}

void gol_init(struct worldClass *worlds)
{
	for (int i = 0; i < worlds->tamX; i++)
	{
		for (int j = 0; j < worlds->tamY; j++)
		{
			worlds->worlds[CURRENTWORLD][i][j] = false;
		}
	}
	worlds->worlds[CURRENTWORLD][0][1] = true;
	worlds->worlds[CURRENTWORLD][1][2] = true;
	worlds->worlds[CURRENTWORLD][2][0] = true;
	worlds->worlds[CURRENTWORLD][2][1] = true;
	worlds->worlds[CURRENTWORLD][2][2] = true;
}

void gol_print(const struct worldClass *worlds)
{
	for (int i = 0; i < worlds->tamX; i++)
	{
		for (int j = 0; j < worlds->tamY; j++)
		{
			if (worlds->worlds[CURRENTWORLD][i][j] == true)
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

			if (worlds->worlds[CURRENTWORLD][i][j])
			{
				worlds->worlds[NEXTWORLD][i][j] = (neighbors == 3) || (neighbors == 2);
			}
			else
			{
				worlds->worlds[NEXTWORLD][i][j] = (neighbors == 3);
			}
		}
	}

	bool **auxp = worlds->worlds[CURRENTWORLD];
	worlds->worlds[CURRENTWORLD] = worlds->worlds[NEXTWORLD];
	worlds->worlds[NEXTWORLD] = auxp;
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
	if (x >= worlds->tamX)
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = worlds->tamX - 1;
	}
	if (y >= worlds->tamY)
	{
		y = 0;
	}
	else if (y < 0)
	{
		y = worlds->tamY - 1;
	}
	return worlds->worlds[CURRENTWORLD][x][y];
}
