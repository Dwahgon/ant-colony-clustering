#ifndef ANT_H
#define ANT_H

#include "grid.h"

#define PICK_DROP_FUNCTION 1
#define K_1 0.001
#define K_2 0.001
#define DIR_CHANGE_PROB_INCREASE 0.5
#define VIEW_RADIUS 1

#define VIEW_RADIUS_AREA (1+2*VIEW_RADIUS)*(1+2*VIEW_RADIUS)

typedef struct ant{
    int i;
    int j;
    int carrying;
    double change_dir_prob;
    int current_dir;
} Ant;

void ant_pick_drop_0(int grid[HEIGHT][WIDTH], Ant *p_ant);
void ant_simulate(int grid[HEIGHT][WIDTH], Ant *p_ant);


#endif