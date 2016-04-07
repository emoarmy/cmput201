#ifndef PLANE_H
#define PLANE_H

typedef struct
{
    int MAX_X[2];
    int MAX_Y[2];
    int NUM_PT;
    int** instance;
    int instance_size;
    int generation;
    int total_gen;
} Plane;

#endif
