#include "parseargs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void parse_args(Args *args, int argc, char **argv)
{
    int i, *p_write_i = NULL;
    double *p_write_d = NULL;
    char **p_write_s = NULL;
    args->n_ants = 20;
    args->grid_width = 50;
    args->grid_height = 50;
    args->k1 = 1.0;
    args->k2 = 1.0;
    args->alpha = 1.0;
    args->data_dimensions = 2;
    args->iterations = 100000;
    args->filePath = NULL;
    args->interactive = 0;

    for (i = 1; i < argc; i++)
    {
        // Read n ants
        if (p_write_i)
        {
            *p_write_i = atoi(argv[i]);
            p_write_i = NULL;
        }
        else if (p_write_d)
        {
            *p_write_d = atof(argv[i]);
            p_write_d = NULL;
        }
        else if (p_write_s)
        {
            if (*p_write_s)
                free(*p_write_s);
            *p_write_s = (char *)malloc(strlen(argv[i]) * sizeof(char));
            strcpy(*p_write_s, argv[i]);
            p_write_s = NULL;
        }

        else if (!strcmp(argv[i], "-n"))
            p_write_i = &args->n_ants;
        else if (!strcmp(argv[i], "-h"))
            p_write_i = &args->grid_height;
        else if (!strcmp(argv[i], "-w"))
            p_write_i = &args->grid_width;
        else if (!strcmp(argv[i], "-t"))
            p_write_i = &args->iterations;
        else if (!strcmp(argv[i], "-d"))
            p_write_i = &args->data_dimensions;
        else if (!strcmp(argv[i], "-a"))
            p_write_d = &args->alpha;
        else if (!strcmp(argv[i], "-k"))
            p_write_d = &args->k1;
        else if (!strcmp(argv[i], "-l"))
            p_write_d = &args->k2;
        else if (!strcmp(argv[i], "-f"))
            p_write_s = &args->filePath;
        else if (!strcmp(argv[i], "-i"))
            args->interactive = 1;
        else
        {
            printf("Argumento desconhecido: %s", argv[i]);
            exit(1);
        }
    }

    if (!args->filePath)
    {
        args->filePath = calloc(strlen("./input.txt"), sizeof(char));
        strcpy(args->filePath, "./input.txt");
    }
}