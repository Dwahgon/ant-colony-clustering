#ifndef ANT_H
#define ANT_H

#include "grid.h"

#define PICK_DROP_FUNCTION 2
#define DIR_CHANGE_PROB_INCREASE 0.5
#define VIEW_RADIUS 1

#define VIEW_RADIUS_AREA (1 + 2 * VIEW_RADIUS) * (1 + 2 * VIEW_RADIUS)

typedef struct ant
{
    int i;
    int j;
    GridItem *carrying_item;
    double change_dir_prob;
    int current_dir;
} Ant;

char ant_is_carrying(Ant *p_ant);
void ant_simulate(Grid *grid, Ant *p_ant);

extern double k1;
extern double k2;
extern double alpha;

#endif