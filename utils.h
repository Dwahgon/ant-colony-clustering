#ifndef UTILS_H
#define UTILS_H

int mod(int x, int y);
char dir_to_hdir(unsigned char dir);
char dir_to_vdir(unsigned char dir);
double distance_squared(double *d1, double *d2, int dimensions);
double distance(double *d1, double *d2, int dimensions);

#endif