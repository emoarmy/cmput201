#ifndef GENPLANE_H
#define GENPLANE_H

#include "plane.h"
FILE *fp;
/////////////////////////////////////////////////
//
// HELPERS
//
////////////////////////////////////////////////
int* splitNumbers(char* line, int number);

char* genFilename(int numberOfPoints, int index);

int findPos(int* arr, int arrSize, int num);

/////////////////////////////////////////////////
//
// VALIDATE
//
////////////////////////////////////////////////
bool isBetween(int between, int lower, int upper);

bool isComment(char* line);

bool checkMax(int max);

bool checkUnique(int* coordinate, int** instance,  int size);

bool checkPlaneInstance(Plane plane);

bool checkAllUnique(Plane plane);

bool checkBounds(Plane plane);

bool checkFile(Plane plane);

/////////////////////////////////////////////////
//
// GETTERS
//
////////////////////////////////////////////////
int* getInput(char* prompt, int num_of_values);

char* getFilename(char** array, int length);

char* getOption(char** array, int length);

int getGeneration(char* filename);

Plane getParameters(void);

char** readFile(char* filename);

Plane getFileParameters(char* line[]);

/////////////////////////////////////////////////
//
// Print Data
//
////////////////////////////////////////////////

bool planeToFile(char* filename, Plane plane);

void planeToTerminal(Plane plane);

void printPlane(Plane plane,char* filename, char* options);

/////////////////////////////////////////////////
//
// GEN DATA
//
////////////////////////////////////////////////
int genCoordinate(int min, int max);

int* genCoordinates(int* x_array, int* y_array );

int** genInstance(int numberOfPoints, int* x_array, int* y_array);

//////////////////////////////////////////////////
//
// Clean Up
//
//////////////////////////////////////////////////
void freePlane(Plane plane);
void freeInstance(int** instance, int length);
#endif
