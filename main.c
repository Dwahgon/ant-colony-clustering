#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ant.h"
#include "grid.h"
#include "utils.h"
#include "parseargs.h"
#include "parsefile.h"

void grid_draw(Grid *grid, Ant *ants, int n_ants, int draw_ants)
{
    int i, j, k, ant_status;
    Ant *p_ant;
    for (i = 0; i < grid->height; i++)
    {
        for (j = 0; j < grid->width; j++)
        {
            ant_status = 0;
            if (draw_ants)
            {
                for (k = 0; k < n_ants; k++)
                {
                    p_ant = &ants[k];
                    if (p_ant->i == i && p_ant->j == j)
                    {
                        ant_status = ant_is_carrying(p_ant) + 1;
                        break;
                    }
                }
            }
            if (ant_status == 2)
                printf("&");
            else if (ant_status == 1)
                printf("@");
            else if (grid_has_item(grid, i, j))
                printf("%c", 'a' - 1 + grid_get_item(grid, i, j)->y);
            else
                printf(" ");
        }
        printf("\n");
    }
    for (i = 0; i < grid->width; i++)
    {
        printf("=");
    }
    printf("\n");
}

void simulate(Ant *ants, int n_ants, Grid *grid)
{
    int i;
    for (i = 0; i < n_ants; i++)
        ant_simulate(grid, &ants[i]);
}

void validate(Grid *grid, int n_items)
{
    int i, j;
    unsigned int cont;
    for (i = 0; i < grid->height; i++)
    {
        for (j = 0; j < grid->width; j++)
        {
            cont += (unsigned int)grid_has_item(grid, i, j);
        }
    }
    if (cont != n_items)
    {
        printf("error: there are missing items\n");
    }
}

int main(int argc, char **argv)
{
    Args args;
    Ant *ants, *p_ant;
    Grid *grid;
    GridItem **grid_items;
    double p;
    int i, j, k, ant_status, r, n_items, it;

    parse_args(&args, argc, argv);
    k1 = args.k1;
    k2 = args.k2;
    alpha = args.alpha;
    grid_items = parse_file(args.filePath, args.data_dimensions, &n_items);
    // [1] "The total number of iterations has to grow with the size of the data set. Linear growth proves to be sufficient, as this keeps the average number of times each grid cell is visited constant. Here, #iterations=2000*n_items with a minimal number of 1 million iterations imposed."
    args.iterations = args.iterations == -1 ? max(2000*n_items, 1000000) : args.interactive;
    // [1] " Given a set of n_items items, the grid (comprising a total of N_cells cells) should offer a sufficient amount of ‘free’ space to permit the quick dropping of data items (note that each grid cell can only be occupied by one data item). This can be achieved by keeping the ratio r_occupied=N_items/N_cells constant. A good value, found experimentally, is 1/10. We obtain this by using a square grid with a resolution of sqrt(10*N_items)xsqrt(10*N_items) grid cells."
    args.grid_width = args.iterations == -1 ? (int)sqrt(10.0*(double)n_items) : args.grid_width;
    args.grid_height = args.iterations == -1 ? args.grid_width : args.grid_height;
    grid = grid_init(args.grid_width, args.grid_height, args.data_dimensions);
    ants = (Ant *)calloc(args.n_ants, sizeof(Ant));
    grid_place_items_randomly(grid, grid_items, n_items);
    free(grid_items);

    srand(time(NULL));

    // init ants
    for (i = 0; i < args.n_ants; i++)
    {
        p_ant = &ants[i];
        p_ant->i = rand() % grid->height;
        p_ant->j = rand() % grid->width;
        p_ant->carrying_item = NULL;
        p_ant->change_dir_prob = 0.;
        p_ant->current_dir = rand() % 8;
    }

    // Draw
    grid_draw(grid, ants, args.n_ants, 1);

    // Run ant logic
    for (it = 0; it < args.iterations; it++)
    {
        if (args.interactive)
            getchar();
        simulate(ants, args.n_ants, grid);
        if (args.interactive)
            grid_draw(grid, ants, args.n_ants, 1);
    }

    grid_draw(grid, ants, args.n_ants, 1);

    while (1)
    {
        j = 0;
        for (i = 0; i < args.n_ants; i++)
        {
            p_ant = &ants[i];
            if (p_ant->carrying_item)
            {
                j++;
                ant_simulate(grid, p_ant);
            }
        }
        if (!j)
            break;
    }

    // Draw
    grid_draw(grid, ants, args.n_ants, 0);
    validate(grid, n_items);

    grid = grid_free(grid);
    free(args.filePath);
    free(ants);

    return 0;
}

// [1] - Ant-based clustering: a comparative study of its relative performance with respect to-means, average link and 1d-so