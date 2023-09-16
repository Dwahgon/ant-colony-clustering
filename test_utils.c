#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int test_distance_1(){
    double v1[2] = {0,0}, v2[2] = {20, 20}, v3[2] = {-20, -20};
    printf("%lf\n%lf\n", distance(v1, v1, 2), distance(v2, v3, 2));
}

int main(){
    test_distance_1();
}