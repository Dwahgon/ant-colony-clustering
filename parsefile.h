#ifndef PARSE_FILE_H
#define PARSE_FILE_H

#include "grid.h"

GridItem **parse_file(char *file_path, int data_dimensions, int *n_items);

#endif