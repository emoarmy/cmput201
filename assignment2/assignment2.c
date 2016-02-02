/* assignment1.c
*  This program performs two functions. 1. It validates instance files that
*  are passed in through the terminal using -i. 2. It generates instance
*  files based off user input.
*
*  Assumptions: That the user is not intentionally malicious and they try to enter
*  positive integers as input. If they try to enter strings or other weird characters, bad
*  things could happen. It is also assumed that any file coordinates are valid coordinates
*  Another assumption is that MAX_X or MAX_Y are both going to be greater than 0.
*
* Copyright 2016, Justin Barclay.
* All rights reserved.
*
* Created by:		Justin Barclay (justincbarclay@gmail.com)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

FILE *fp;
/////////////////////////////////////////////////
//
// STRUCTS
//
/////////////////////////////////////////////////
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

/////////////////////////////////////////////////
//
// HELPERS
//
////////////////////////////////////////////////
int* splitNumbers(char* line){
    //Split numbers in a string based on the \t delimiter"
    int *array = malloc(sizeof(int)*2) ; // Hard coded because each line in the sample file has at most 2 ints.
    char** strings;
    // max size of any string
    char* astring[10];
    strings = astring;
    if(strcmp(&line[0], " ") != 0){
        for(int i=0; (*strings = strsep(&line, " \t")) != NULL; i++){
            array[i] = atoi(*strings);
        }
    } else {
        array = NULL;
    }
   return array;
}


char* genFilename(int numberOfPoints, int index){
    //returns a filename as a string based on the number of points and the instance number
    char* string = malloc(sizeof(char)*100);
    asprintf(&string, "instance%.3i_%.3i.txt", numberOfPoints, index);
    return string;
}

/////////////////////////////////////////////////
//
// VALIDATE
//
////////////////////////////////////////////////
bool isBetween(int between, int lower, int upper){
    //return true if the first variable is between the second two variables
    // this does no error checking for incorrect input
    if (between > lower && upper > between){
        return true;
    }
    return false;
}

bool isComment(char* line){
    // Returns true if the line starts with #
    if(strncmp(&line[0], "#", strlen("#"))==0){
        return true;
    } else {
        return false;
    }
}

bool checkMax(int max){
    return (max > 0);
}

bool checkUnique(int* coordinate, int** instance,  int size){

    // A quick and dirty way to check if a given coordinate is unique.
    // It iterates through the passed in instance and returns false if both
    // x and y coordinates match one in the instance
    for(int i=0; i<size; i++){
        if(coordinate[0] == instance[i][0] && coordinate[1] == instance[i][1]){
            return false;
        }
    }
    return true;
}
bool checkPlaneInstance(Plane plane){
    return(plane.instance_size == plane.NUM_PT);
}

bool checkAllUnique(Plane plane){
    // check to make sure all coordinates are unique
     for(int i=0; i<plane.instance_size; i++){
        for(int j=i+1; j< plane.instance_size; j++){
            if(plane.instance[i][0]==plane.instance[j][0] && plane.instance[i][1]==plane.instance[j][1]){
                return false;
            }
        }
    }
    return true;
}

bool checkBounds(Plane plane){
    // check all instances in the plane to see if they are below Max_X and Max_Y
    for(int i=0; i < plane.instance_size; i++){
        if(plane.instance[i][0] > plane.MAX_X[1] || plane.instance[i][1] > plane.MAX_Y[1]) {
            return false;
        }
    }
    return true;
}

bool checkFile(Plane plane){
        if(!checkMax(plane.MAX_X[1]) || !checkMax(plane.MAX_Y[1])){
            return false;
        }
        if(!checkPlaneInstance(plane)){
            return false;
        }
        if(!checkAllUnique(plane)){
            return false;
        }
        if(!checkBounds(plane)){
            return false;
        }
        return true;

}

/////////////////////////////////////////////////
//
// GETTERS
//
////////////////////////////////////////////////
int* getInput(char* prompt, int num_of_values){
    // Prompts user for input and pattern matches characters until it finds as many as needed and returns the option int array
    int *option = malloc(sizeof(int)*num_of_values);
    printf("%s", prompt);
    for(int i = 0; i < num_of_values; i++){
        scanf("%d", &option[i]);
    }
   return option;
}

char* getFilename(char** array, int length){
    // Parses an array of strings and if a string matching "-i" is found, it returns the next string in the array
    // if no file name is in the string, return NULL
    char* filename;
    filename = NULL;

        for(int i=0; i < length; i++){
            if(strcmp(array[i], "-i") == 0){
                filename = array[i+1];
                break;
            }
        }
    return filename;
}

char* getOption(char** array, int length){
    // Like getFilename, this function parses through an array of strings and grabs the element after -o and returns it as an option
    char* option;
    option = NULL;

        for(int i=0; i < length; i++){
            if(strcmp(array[i], "-o") == 0){
                option = array[i+1];
                break;
            }
        }
   return option;
}
int getGeneration(char* filename){
    // This parses a string that is passed into it for a number that indicates the generation number of the instance
    char* genChar;
    char* ptr;
    int index;
    ptr = strchr(filename, '_');
    if(ptr != NULL){
        index = ptr - filename;
        asprintf(&genChar, "%c%c%c", filename[index+1], filename[index+2], filename[index+3]);
    } else {
        return -1;
    }
    int gen = atoi(genChar);
    return gen;
}
Plane getParameters(void){
    // Prompts user for the input to construct planes
    // and returns an array of ints
    Plane plane;
    plane.MAX_X[0] = 0;
    plane.MAX_Y[0] = 0;
    plane.generation = 0;

    int* max_x_y;
    int* num_pt;
    int* num_inst;


    max_x_y = getInput("Enter the circuit board size MAX_X MAX_Y: ", 2);
    num_pt = getInput("Enter the number of points NUM_PT: ", 1);
    num_inst = getInput("Enter the number of random instances to be generated: ", 1);
    plane.instance_size=0;

    //Error checking to ensure, that we can generate as many unique points as the user requires
    while(num_pt[0] > max_x_y[0]+1 * max_x_y[1]+1){
        printf("Please enter a number of points less than %i\n", max_x_y[0]+1 * max_x_y[1]+1);
        num_pt = getInput("Enter the number of points NUM_PT: ", 1);
    }

    // assign inputs from user to plane
    plane.MAX_X[1] = max_x_y[0];
    plane.MAX_Y[1] = max_x_y[1];
    plane.NUM_PT = num_pt[0];
    plane.total_gen = num_inst[0];

    // free all malloc variables in the program
    free(max_x_y);
    free(num_pt);
    free(num_inst);

    return plane;
}

char** readFile(char* filename){
    // Takes a file name, and searches for that file in the same direcotry as the program is being executed
    // If it fails, to find a file it returns NULL otherwise it returns an array of \n terminated strings

    size_t nBytes = 255;
    char** lines = malloc(1000*sizeof(char*));
    lines[0] = NULL;

    fp = fopen(filename, "rt");
    if (fp == NULL){
        return NULL;
    }
    int index =0;
    while(feof(fp) == 0){
        getline(&lines[index], &nBytes, fp);
        index++;
    }
    lines[index+1] = NULL;
    fclose(fp);
    return lines;
}

Plane getFileParameters(char* line[]){
    // Check line by line for the presence of a commented line. If the line is commented
    // ignore the line, else add the parameters to the parameters array.
    Plane plane;

    // I need to learn how realloc works. This could cause bugs if I am reading in a file that has more than 100 instances
    int** instance = malloc(sizeof(int[2])*100);

    //Initialize variable
    plane.MAX_X[0] = 0;
    plane.MAX_Y[0] = 0;
    plane.instance_size = 0;
    plane.total_gen = 0;
    int index=0;
    int* temp;

    // Read the the line array until it reaches null
    for(int i=0; line[i] != NULL; i++){
        if(!isComment(line[i])){
            //First instance of text from the array that is not a comment should be max_x and max_y
            if(index == 0){
                temp = splitNumbers(line[i]);
                plane.MAX_X[1] = temp[0];
                plane.MAX_Y[1] = temp[1];
            }
            //second instance of text should be total number of points
            if(index == 1){
                temp = splitNumbers(line[i]);
                plane.NUM_PT = temp[0];
            }
            //Anyone after that until the end of the array hould be instances
            if(index >= 2 && strcmp(line[i], "\0") !=0){
                temp = splitNumbers(line[i]);
                plane.instance_size++;
                instance[index-2] = temp;
            }
            index++;
        }
    }
    plane.instance = instance;
    free(temp);
    return plane;
}

/////////////////////////////////////////////////
//
// Print Data
//
////////////////////////////////////////////////

bool planeToFile(char* filename, Plane plane){
    FILE *newFile;
    //the variable we're going to use to print everything
    newFile = fopen(filename, "w+");
    //print MAX_X and MAX_Y
    fprintf(newFile, "#area [0, MAX_X] x [0, MAX_Y]\n");
    fprintf(newFile, "%d\t%d\n", plane.MAX_X[1], plane.MAX_Y[1]);

    //print number of points Generated
    fprintf(newFile, "#number of points NUM_PT\n");
    fprintf(newFile, "%d\n", plane.NUM_PT);

    fprintf(newFile, "#coordinates\n");
    for(int i=0; i < plane.NUM_PT; i++){
        fprintf(newFile, "%d\t%d\n", plane.instance[i][0], plane.instance[i][1]);
    }
    fprintf(newFile, "#end of instance\n");
    fclose(newFile);
    return true;
}

void planeToTerminal(Plane plane){

    //print MAX_X and MAX_Y
    printf("#area [0, MAX_X] x [0, MAX_Y]\n");
    printf("%d\t%d\n", plane.MAX_X[1], plane.MAX_Y[1]);

    //print number of points Generated
    printf("#number of points NUM_PT\n");
    printf("%d\n", plane.NUM_PT);

    printf("#coordinates\n");
    for(int i=0; i < plane.NUM_PT; i++){
        printf("%d\t%d\n", plane.instance[i][0], plane.instance[i][1]);
    }
    printf("#end of instance\n");
}

void printPlane(Plane plane, char* options){
    // Determine, based on the options being passed in, how to print the given Plane
    if(options != NULL && strcmp(options, "output") == 0 ){
        char* filename = genFilename(plane.NUM_PT, plane.generation);
        planeToFile(filename, plane);
        printf("%s created.\n", filename);
        free(filename);
    } else {
        planeToTerminal(plane);
    }
}

/////////////////////////////////////////////////
//
// GEN DATA
//
////////////////////////////////////////////////
int genCoordinate(int min, int max){
    // this has some issues with uniform number distributions but for this class it should work
    return (rand() % (max-min+1) + min);
}

int* genCoordinates(int* x_array, int* y_array ){
    // This code is malloc and needs to call free

    //Uses the implicit min of the array and the max as supplied by the user to gen a new x and y coordinate
    int* coordinates = malloc(sizeof(int)*2);
    coordinates[0] = genCoordinate(x_array[0], x_array[1]);
    coordinates[1] = genCoordinate(y_array[0], y_array[1]);

    return coordinates;
}

int** genInstance(int numberOfPoints, int* x_array, int* y_array){
    // Takes in 3 parametes, number of points to generate, an array with min and max x coordinates
    // and an array with min and man y coordinates;
    int** instance = malloc(sizeof(int)*2*numberOfPoints);
    int* coordinates;
    for(int i=0; i<numberOfPoints; i++){
        coordinates = genCoordinates(x_array, y_array);
        while(checkUnique(coordinates, instance, i-1) == false){
            coordinates = genCoordinates(x_array, y_array);
        }
        instance[i] = coordinates;

    }
    return instance;
}

/////////////////////////////////////////////////
//
// MAIN
//
////////////////////////////////////////////////

// Must check for errors in instance, if so output error to console.
// If option output is given, output file to a text
// If option output is not given output to screen
int main(int argc, char** argv){
    char* filename = NULL;
    char** lines;
    Plane plane;
    char* options = NULL;
    bool correctFile = true;
    //initiallize rand() with current time
    srand(time(NULL));

    // Cheching for arguments, if they are greater than or equal to two, assume
    // their are options and a filename being passed in trying to be passed in.
    if(argc >= 2){
        filename = getFilename(argv, argc);
        options = getOption(argv, argc);
    }

    // Grab Data
    if (filename == NULL){
        plane = getParameters();
        plane.instance_size = plane.NUM_PT;
    } else {
        lines = readFile(filename);

        // Check to see if a file was succesffully parsed
        if(lines == NULL){
            printf("File not found\n");
            printf("Exiting...\n");
            return -1;
        }
        plane.generation = getGeneration(filename);

        plane = getFileParameters(lines);
        correctFile = checkFile(plane);
        free(lines);
    }
    
    // Ensure instances is of the correct size;
    if(!correctFile){
        printf("File is corrupt, the instance file does not match specification\n");
        return -2;
    }

    // A hack to test if we opened a file
    if(filename != NULL){
        printPlane(plane, options);
    }

    // The hack is needed because plane.generation will only be less than plane.total_gen when
    // the user inputs data through the terminal
    while(plane.generation < plane.total_gen){
        plane.instance = genInstance(plane.NUM_PT, plane.MAX_X, plane.MAX_Y);
        printPlane(plane, options);
        plane.generation++;
    }

    free(plane.instance);
    return 0;
}
