#ifndef BST_H
#define BST_H

#include "plane.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/////////////////////////////////////////////////
//
// BST
//
////////////////////////////////////////////////

int rectDistance(int* coordA, int* coordB);

void appendWeight(int* instance, FILE* filename);

int* addVisited(int* visited, int len, int newPoint);

int** prims(Plane plane);

int breakTie(int** coords, int visited, int unvisited, int minNodeUnvis);

int maxX(int** coords, int minNodeUnvis, int unvisited);

int* findMin(int** coords, int* visited, int sizeVisited, int* unvisited, int sizeUnvisited);

int totalWeight(int** MST, int length);

int* nodeDegree(int** MST, int size);

void printMST(int** MST, int size, char* filename, char* option);
#endif
