#ifndef GRID_H
#define GRID_H

#define HEIGHT 50
#define WIDTH 50

int grid_count_neighbouring_items(int grid[HEIGHT][WIDTH], int i, int j, int view_radius);
int grid_get_item(int grid[HEIGHT][WIDTH], int i, int j);
short grid_item_dirs(int grid[HEIGHT][WIDTH], int i, int j);

#endif