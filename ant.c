#include "ant.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>

void ant_pick_drop_0(int grid[HEIGHT][WIDTH], Ant *p_ant){
    int n_items;
    double p;
    if(!p_ant->carrying && grid[p_ant->i][p_ant->j]){
        n_items = grid_count_neighbouring_items(grid, p_ant->i, p_ant->j, VIEW_RADIUS);
        p = 1.0 - (float)n_items/(float)(VIEW_RADIUS_AREA-1);
        if ((float)rand()/(float)(RAND_MAX) < p){
            grid[p_ant->i][p_ant->j] = 0;
            p_ant->carrying = 1;
        }
    }else if (p_ant->carrying && !grid[p_ant->i][p_ant->j]){
        n_items = grid_count_neighbouring_items(grid, p_ant->i, p_ant->j, VIEW_RADIUS);
        p = (float)n_items/(float)(VIEW_RADIUS_AREA-1);
        if ((float)rand()/(float)(RAND_MAX) < p){
            grid[p_ant->i][p_ant->j] = 1;
            p_ant->carrying = 0;
        }
    }
}

void ant_pick_drop_1(int grid[HEIGHT][WIDTH], Ant *p_ant){
    int n_items;
    double p, f;
    if(!p_ant->carrying && grid[p_ant->i][p_ant->j]){ // Pick
        n_items = grid_count_neighbouring_items(grid, p_ant->i, p_ant->j, VIEW_RADIUS);
        f = (float)n_items/(float)(VIEW_RADIUS_AREA-1);
        p = powf(K_1/(K_1 + f), 2.0);
        if ((float)rand()/(float)(RAND_MAX) < p){
            grid[p_ant->i][p_ant->j] = 0;
            p_ant->carrying = 1;
        }
    }else if (p_ant->carrying && !grid[p_ant->i][p_ant->j]){ // Drop
        n_items = grid_count_neighbouring_items(grid, p_ant->i, p_ant->j, VIEW_RADIUS);
        f = (float)n_items/(float)(VIEW_RADIUS_AREA-1);
        p = powf(f/(f + K_2), 2.0);
        if ((float)rand()/(float)(RAND_MAX) < p){
            grid[p_ant->i][p_ant->j] = 1;
            p_ant->carrying = 0;
        }
    }
}


void ant_rand_walk_update_dir(Ant *p_ant){
    if ((float)rand()/(float)(RAND_MAX) < p_ant->change_dir_prob){
        p_ant->change_dir_prob = 0;
        p_ant->current_dir = (p_ant->current_dir + 1 + rand() % 7) % 8;
    }else{
        p_ant->change_dir_prob += DIR_CHANGE_PROB_INCREASE;
    }
}

void ant_move(Ant *p_ant){
    int hdir, vdir;
    hdir = dir_to_hdir(p_ant->current_dir);
    vdir = dir_to_vdir(p_ant->current_dir);

    p_ant->i = mod(p_ant->i + vdir, HEIGHT);
    p_ant->j = mod(p_ant->j + hdir, WIDTH);
}

void ant_simulate(int grid[HEIGHT][WIDTH], Ant *p_ant){
    switch (PICK_DROP_FUNCTION)
    {
    case 0:
        ant_pick_drop_0(grid, p_ant);
        break;
    case 1:
        ant_pick_drop_1(grid, p_ant);
        break;
    default:
        break;
    }

    ant_rand_walk_update_dir(p_ant);
    ant_move(p_ant);
}