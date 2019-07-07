#include "gol.h"

enum world_used
{
	CURRENTWORLD,
	NEXTWORLD,
};

static int count_neighbors(const struct worldClass *worlds, int x, int y);
static bool get_cell(const struct worldClass *worlds, int x, int y);
static void set_cell(struct worldClass *worlds, enum world_used ewu, int x, int y, bool baux);

bool gol_alloc(struct worldClass *worlds, int tamX, int tamY)
{
	for (int i = CURRENTWORLD; i <= NEXTWORLD; i++)
	{
		worlds->worlds[i] = (bool *)malloc(tamX * tamY * sizeof(bool));
		if (!worlds->worlds[i])
			return 0;
	}
	worlds->tamX = tamX;
	worlds->tamY = tamY;
	return 1;
}

void gol_free(struct worldClass *worlds)
{
	for (int i = CURRENTWORLD; i <= NEXTWORLD; i++)
	{
		free(worlds->worlds[i]);
	}
}

static void set_cell(struct worldClass *worlds, enum world_used ewu, int x, int y, bool baux)
{
	worlds->worlds[ewu][x * worlds->tamY + y] = baux;
}

void gol_init(struct worldClass *worlds)
{
	for (int i = 0; i < worlds->tamX; i++)
	{
		for (int j = 0; j < worlds->tamY; j++)
		{
			set_cell(worlds, CURRENTWORLD, i, j, false);
		}
	}
	set_cell(worlds, CURRENTWORLD, 0, 1, true);
	set_cell(worlds, CURRENTWORLD, 1, 2, true);
	set_cell(worlds, CURRENTWORLD, 2, 0, true);
	set_cell(worlds, CURRENTWORLD, 2, 1, true);
	set_cell(worlds, CURRENTWORLD, 2, 2, true);
}

void gol_print(const struct worldClass *worlds)
{
	for (int i = 0; i < worlds->tamX; i++)
	{
		for (int j = 0; j < worlds->tamY; j++)
		{
			if (get_cell(worlds, i, j) == true)
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

			if (get_cell(worlds, i, j))
			{
				bool baux = (neighbors == 2) || (neighbors == 3);
				set_cell(worlds, NEXTWORLD, i, j, baux);
			}
			else
			{
				bool baux = neighbors == 3;
				set_cell(worlds, NEXTWORLD, i, j, baux);
			}
		}
	}

	bool *auxp = worlds->worlds[CURRENTWORLD];
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
	return worlds->worlds[CURRENTWORLD][x * worlds->tamY + y];
}
