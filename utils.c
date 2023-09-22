#include <math.h>
#include <stdio.h>

int mod(int x, int y)
{
    int m = x % y;
    return m < 0 ? ((y < 0) ? m - y : m + y) : m;
}

int max(int x, int y) {
    return x > y ? x : y;
}

char dir_to_hdir(unsigned char dir)
{
    return (dir == 0 || dir == 1 || dir == 8) - (dir >= 3 && dir <= 5);
}

char dir_to_vdir(unsigned char dir)
{
    return (dir >= 5 && dir <= 7) - (dir >= 1 && dir <= 3);
}

double distance_squared(double *d1, double *d2, int dimensions)
{
    double sum = 0;
    while (dimensions--)
        sum += (d1[dimensions] - d2[dimensions]) * (d1[dimensions] - d2[dimensions]);
    return sum;
}

double distance(double *d1, double *d2, int dimensions)
{
    double res = sqrt(distance_squared(d1, d2, dimensions));
    // printf("%lf\n", res);
    return res;
}