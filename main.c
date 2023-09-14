#define N_ANTS 40
#define N_ITEMS 400
#define ITERATIONS 1000000
#define DATA_DIMENSIONS 2
#define DATA_MIN 0
#define DATA_MAX 10
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ant.h"
#include "grid.h"
#include "utils.h"


void grid_draw(int grid[HEIGHT][WIDTH], Ant ants[N_ANTS], int draw_ants){
    int i, j, k, ant_status;
    Ant *p_ant;
    for (i = 0; i < HEIGHT; i++){
        for(j = 0; j < WIDTH; j++){
            ant_status = 0;
            if (draw_ants){
                for (k = 0; k < N_ANTS; k++){
                    p_ant = &ants[k];
                    if (p_ant->i == i && p_ant->j == j){
                        ant_status = p_ant->carrying + 1;
                        break;
                    }
                }
            }
            if (ant_status == 2)
                printf("&");
            else if (ant_status == 1)
                printf("@");
            else if (grid[i][j])
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("-----------------------------------------\n");
}

void simulate(Ant ants[N_ANTS], int grid[HEIGHT][WIDTH]){
    int i;
    for (i = 0; i < N_ANTS; i++)
        ant_simulate(grid, &ants[i]);
}


int main(){
    Ant ants[N_ANTS], *carryingAnts[N_ANTS], *p_ant;
    int grid[HEIGHT][WIDTH];
    double p;
    int i, j, k, ant_status, r, n_items, it;
    srand(time(NULL));

    // init ants
    for (i = 0; i < N_ANTS; i++){
        p_ant = &ants[i];
        p_ant->i = rand() % HEIGHT;
        p_ant->j = rand() % WIDTH;
        p_ant->carrying = 0;
        p_ant->change_dir_prob = 0.;
        p_ant->current_dir = rand() % 8;
    }
    // init grid
    for (i = 0; i < HEIGHT; i++){
        for (j = 0; j < WIDTH; j++){
            grid[i][j] = 0;
        }
    }
    // place items
    for(i = 0; i < N_ITEMS; i++){
        if (grid[rand() % HEIGHT][rand() % WIDTH]) i--;
        else grid[rand() % HEIGHT][rand() % WIDTH] = 1;
    }

    // Draw
    grid_draw(grid, ants, 1);

    // Run ant logic
    for(it = 0; it < ITERATIONS; it++){
        // getchar();
        simulate(ants, grid);
        // grid_draw(grid, ants);
    }

    while(1){
        j = 0;
        for (i = 0; i < N_ANTS; i++) {
            p_ant = &ants[i];
            if (p_ant->carrying){
                j = 1;
                ant_simulate(grid, p_ant);
            }
        }
        if(!j) break;
    }

    // Draw
    grid_draw(grid, ants, 0);

    return 0;
}