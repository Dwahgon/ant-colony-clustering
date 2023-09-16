#include "ant.h"
#include "utils.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

double k1 = 0.0;
double k2 = 0.0;
double alpha = 0.0;

double fi(Grid *grid, GridItem *item, unsigned int i, unsigned int j)
{
    unsigned char k;
    char hdir, vdir;
    unsigned int s = grid_count_neighbouring_items(grid, i, j, VIEW_RADIUS);
    double sum = 0.0;
    for (k = 0; k < 8; k++)
    {
        hdir = dir_to_hdir(k);
        vdir = dir_to_vdir(k);
        if (grid_has_item(grid, i + vdir, j + hdir))
        {
            sum += 1 - distance(item->X, grid_get_item(grid, i + vdir, j + hdir)->X, item->x_size) / alpha;
        }
    }
    return s > 0 && sum > 0 ? sum / ((double)s * (double)s) : 0.;
}

double pp(Grid *grid, GridItem *item, unsigned int i, unsigned int j)
{
    return pow(k1 / (k1 + fi(grid, item, i, j)), 2.0);
}

double pd(Grid *grid, GridItem *item, unsigned int i, unsigned int j)
{
    double f = fi(grid, item, i, j);
    return pow(f / (k2 + f), 2.0);
}

// void ant_pick_drop_0(Grid *grid, Ant *p_ant)
// {
//     int n_items;
//     double p = 0;
//     if (!p_ant->carrying_item && grid_has_item(grid, p_ant->i, p_ant->j))
//     {
//         n_items = grid_count_neighbouring_items(grid, p_ant->i, p_ant->j, VIEW_RADIUS);
//         p = 1.0 - (float)n_items / (float)(VIEW_RADIUS_AREA - 1);
//     }
//     else if (p_ant->carrying_item && !grid_has_item(grid, p_ant->i, p_ant->j))
//     {
//         n_items = grid_count_neighbouring_items(grid, p_ant->i, p_ant->j, VIEW_RADIUS);
//         p = (float)n_items / (float)(VIEW_RADIUS_AREA - 1);
//     }
//     if ((float)rand() / (float)(RAND_MAX) < p)
//     {
//         p_ant->carrying_item = grid_set_item(grid, p_ant->carrying_item, p_ant->i, p_ant->j);
//     }
// }

// void ant_pick_drop_1(Grid *grid, Ant *p_ant)
// {
//     int n_items;
//     double p = 0, f;
//     if (!p_ant->carrying_item && grid_has_item(grid, p_ant->i, p_ant->j))
//     { // Pick
//         n_items = grid_count_neighbouring_items(grid, p_ant->i, p_ant->j, VIEW_RADIUS);
//         f = (float)n_items / (float)(VIEW_RADIUS_AREA - 1);
//         p = powf(k1 / (k2 + f), 2.0);
//     }
//     else if (p_ant->carrying_item && !grid_has_item(grid, p_ant->i, p_ant->j))
//     { // Drop
//         n_items = grid_count_neighbouring_items(grid, p_ant->i, p_ant->j, VIEW_RADIUS);
//         f = (float)n_items / (float)(VIEW_RADIUS_AREA - 1);
//         p = powf(f / (f + k2), 2.0);
//     }
//     if ((float)rand() / (float)(RAND_MAX) < p)
//     {
//         p_ant->carrying_item = grid_set_item(grid, p_ant->carrying_item, p_ant->i, p_ant->j);
//     }
// }

void ant_pick_drop_2(Grid *grid, Ant *p_ant)
{
    unsigned int s;
    double p = 0, f;
    if (!p_ant->carrying_item && grid_has_item(grid, p_ant->i, p_ant->j))
    { // Pick
        p = pp(grid, grid_get_item(grid, p_ant->i, p_ant->j), p_ant->i, p_ant->j);
    }
    else if (p_ant->carrying_item && !grid_has_item(grid, p_ant->i, p_ant->j))
    { // Drop
        p = pd(grid, p_ant->carrying_item, p_ant->i, p_ant->j);
    }
    if ((float)rand() / (float)(RAND_MAX) < p)
    {
        p_ant->carrying_item = grid_set_item(grid, p_ant->carrying_item, p_ant->i, p_ant->j);
    }
}

void ant_rand_walk_update_dir(Ant *p_ant)
{
    if ((float)rand() / (float)(RAND_MAX) < p_ant->change_dir_prob)
    {
        p_ant->change_dir_prob = 0;
        p_ant->current_dir = (p_ant->current_dir + 1 + rand() % 7) % 8;
    }
    else
    {
        p_ant->change_dir_prob += DIR_CHANGE_PROB_INCREASE;
    }
}

char ant_is_carrying(Ant *p_ant)
{
    return p_ant->carrying_item ? 1 : 0;
}

void ant_move(Grid *grid, Ant *p_ant)
{
    int hdir, vdir;
    hdir = dir_to_hdir(p_ant->current_dir);
    vdir = dir_to_vdir(p_ant->current_dir);

    p_ant->i = mod(p_ant->i + vdir, grid->height);
    p_ant->j = mod(p_ant->j + hdir, grid->width);
}

void ant_simulate(Grid *grid, Ant *p_ant)
{
    switch (PICK_DROP_FUNCTION)
    {
    case 0:
        ant_pick_drop_0(grid, p_ant);
        break;
    case 1:
        ant_pick_drop_1(grid, p_ant);
        break;
    case 2:
        ant_pick_drop_2(grid, p_ant);
    default:
        break;
    }

    ant_rand_walk_update_dir(p_ant);
    ant_move(grid, p_ant);
}