#include "grid.h"
#include "utils.h"
#include <stdlib.h>

Grid *grid_free(Grid *grid)
{
    int i, j;
    for (i = 0; i < grid->height; i++)
    {
        for (j = 0; j < grid->width; j++)
        {
            if (grid->matrix[i][j])
                free(grid->matrix[i][j]);
        }
        free(grid->matrix[i]);
    }
    free(grid->matrix);
}

Grid *grid_init(int width, int height, int data_dim)
{
    Grid *grid = (Grid *)malloc(sizeof(Grid));
    int i, j, k;
    GridItem ***matrix = (GridItem ***)calloc(height, sizeof(GridItem **));
    for (i = 0; i < height; i++)
    {
        matrix[i] = (GridItem **)calloc(width, sizeof(GridItem *));
        for (j = 0; j < width; j++)
        {
            matrix[i][j] = NULL;
        }
    }
    grid->width = width;
    grid->height = height;
    grid->data_dim = data_dim;
    grid->matrix = matrix;
    return grid;
}

void gi_init(GridItem *gi, unsigned int x_size)
{
    gi->y = 0;
    gi->x_size = x_size;
    gi->X = (double *)calloc(x_size, sizeof(double));
}

void gi_free(GridItem *gi)
{
    free(gi->X);
}

void grid_place_items_randomly(Grid *grid, GridItem **items, int qnt)
{
    unsigned int i, j;
    while (qnt > 0)
    {
        i = rand();
        j = rand();
        if (grid_has_item(grid, i, j))
            continue;
        grid_set_item(grid, items[qnt - 1], i, j);
        qnt--;
    }
}

unsigned int grid_count_neighbouring_items(Grid *grid, unsigned int i, unsigned int j, unsigned int view_radius)
{
    int y, x, vr = (int)view_radius;
    unsigned int cont = 0;
    for (y = -vr; y < vr; y++)
    {
        for (x = -vr; x < vr; x++)
        {
            if (y == 0 && x == 0)
                continue;
            cont += grid_has_item(grid, i + y, j + x);
        }
    }
    return cont;
}

GridItem *grid_get_item(Grid *grid, int i, int j)
{
    return grid->matrix[mod(i, grid->height)][mod(j, grid->width)];
}

char grid_has_item(Grid *grid, int i, int j)
{
    return grid_get_item(grid, i, j) ? 1 : 0;
}

GridItem *grid_set_item(Grid *grid, GridItem *item, int i, int j)
{
    GridItem *previous_item = grid_get_item(grid, i, j);
    grid->matrix[mod(i, grid->height)][mod(j, grid->width)] = item;
    return previous_item;
}