#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H

typedef struct _args
{
    char *filePath;
    int n_ants;
    int grid_width;
    int grid_height;
    double alpha;
    double k1;
    double k2;
    int data_dimensions;
    int iterations;
    char interactive;
} Args;

void parse_args(Args *args, int argc, char **argv);

#endif