#include "grid.h"
#include "utils.h"

int grid_count_neighbouring_items(int grid[HEIGHT][WIDTH], int i, int j, int view_radius){
    int cont = 0, y, x;
    for (y = -view_radius; y < view_radius; y++){
        for (x = -view_radius; x < view_radius; x++){
            if (y == 0 && x == 0) continue;
            cont += grid_get_item(grid, i+y, j+x);
        }
    }
    return cont;
}

int grid_get_item(int grid[HEIGHT][WIDTH], int i, int j){
    return grid[mod(i, HEIGHT)][mod(j, WIDTH)];
}

short grid_item_dirs(int grid[HEIGHT][WIDTH], int i, int j){
    int k, hdir, vdir;
    short item_dirs = 0;
    for (k = 0; i < 8; k++){
        hdir = dir_to_hdir(i);
        vdir = dir_to_vdir(i);
        item_dirs |= grid_get_item(grid, i+vdir, j+hdir) << k;
    }
    return item_dirs;
}