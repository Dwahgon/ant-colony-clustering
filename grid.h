#ifndef GRID_H
#define GRID_H

typedef struct grid_item
{
    double *X;
    unsigned int x_size;
    int y;
} GridItem;

typedef struct grid
{
    int width;
    int height;
    int data_dim;
    GridItem ***matrix;
} Grid;

Grid *grid_init(int width, int height, int data_dim);
Grid *grid_free(Grid *grid);
void gi_init(GridItem *gi, unsigned int x_size);
void gi_free(GridItem *gi);
unsigned int grid_count_neighbouring_items(Grid *grid, unsigned int i, unsigned int j, unsigned int view_radius);
void grid_place_items_randomly(Grid *grid, GridItem **items, int qnt);
GridItem *grid_get_item(Grid *grid, int i, int j);
char grid_has_item(Grid *grid, int i, int j);
GridItem *grid_set_item(Grid *grid, GridItem *item, int i, int j);

#endif