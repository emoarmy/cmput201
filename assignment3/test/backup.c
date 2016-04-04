/* assignment2.c
*  This program is a naive attempt to write side effect free code.
*  
*  This program performs 3 functions. 1. It validates instance files that
*  are passed in through the terminal using -i. 2. It generates instance
*  files based off user input. 3. It generates a MST based on each instance generated 
*  or read in.
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
#include <math.h>

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

void printMST(int** MST, int size, char* filename, char* option);

/////////////////////////////////////////////////
//
// GEN DATA
//
////////////////////////////////////////////////
int genCoordinate(int min, int max);

int* genCoordinates(int* x_array, int* y_array );

int** genInstance(int numberOfPoints, int* x_array, int* y_array);

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
    int** MST;
    int* degrees;
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

    
    if(filename != NULL){
    // If we opened up a file, the Plane instance is all ready generated for us.
        printPlane(plane, filename, options);
        if(plane.instance_size > 1){
            MST = prims(plane);
            printMST(MST,plane.instance_size, filename, options);
            
            degrees = nodeDegree(MST, plane.instance_size-1);
        } else {
            printf("Can not generate MST, insufficient nodes \n");
        }
    } else {
        while(plane.generation < plane.total_gen){
    // If not we need to generate instances for the number of planes required
            plane.instance = genInstance(plane.NUM_PT, plane.MAX_X, plane.MAX_Y);
            printPlane(plane, NULL, options);
            filename = genFilename(plane.NUM_PT, plane.generation);
            if(plane.instance_size > 1){
                MST = prims(plane);
                printMST(MST,plane.instance_size, filename, options);
                degrees = nodeDegree(MST, plane.instance_size-1);
            } else {
                printf("Can not generate MST, insufficient nodes \n");
            }
            plane.generation++;
        }
    }

    // count degrees
   
    // Need to create code to free plane.instance and and sub arrays of instance
    free(plane.instance);

    // need to free MST
    return 0;
}


/////////////////////////////////////////////////
//
// HELPERS
//
////////////////////////////////////////////////
int* splitNumbers(char* line, int number){
    //Split numbers in a string based on white space
    //This function does a little too much work as it, checks for errors and prints to screen as well
    int *array = malloc(sizeof(int)*2) ; // Hard coded because each line in the sample file has at most 2 ints.
    int number2;
    int count = 0;
    int offset = 0;
    int total_offset =  0;

    // check for a blank line
    if(strcmp(&line[0], " ") != 0){
        for(int i=0; (sscanf(line + total_offset, "%d%n", &number2, &offset))==1; i++){
            total_offset += offset;
            array[i] = number2;
            count++;
        }
    } else {
        array = NULL;
    }
   if(count == number){
       return array;
   } else {
       printf("File is corrupt, the instance file does not match specification\n");
       exit(EXIT_FAILURE);
   }
}


char* genFilename(int numberOfPoints, int index){
    //returns a filename as a string based on the number of points and the instance number
    char* string = malloc(sizeof(char)*100);
    asprintf(&string, "instance%.3i_%.3i.txt", numberOfPoints, index);
    return string;
}

int findPos(int* arr, int arrSize, int num){
    if (num < arrSize){
        for(int i=0; i < arrSize; i++){
            if(arr[i] == num){
                return i;
            }
        }
    }
    return -1;
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
    return atoi(genChar);
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
                temp = splitNumbers(line[i],2);
                plane.MAX_X[1] = temp[0];
                plane.MAX_Y[1] = temp[1];
            }
            //second instance of text should be total number of points
            if(index == 1){
                temp = splitNumbers(line[i],1);
                plane.NUM_PT = temp[0];
            }
            //Anyone after that until the end of the array hould be instances
            if(index >= 2 && strcmp(line[i], "\0") !=0){
                temp = splitNumbers(line[i],2);
                plane.instance_size++;
                instance[index-2] = temp;
            }
            index++;
        }
    }
    plane.instance = instance;
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
    //free(filename);
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

void printPlane(Plane plane, char* filename, char* options){
    // Determine, based on the options being passed in, how to print the given Plane
    if(filename == NULL && options != NULL && strcmp(options, "output") == 0 ){
        char* filename = genFilename(plane.NUM_PT, plane.generation);
        planeToFile(filename, plane);
        printf("%s created\n", filename);
    } else if(filename != NULL && options != NULL && strcmp(options, "output") == 0 ) {
       planeToFile(filename, plane);
       printf("%s created\n", filename);
    } else {
        planeToTerminal(plane);
    }    
}

void printMST(int** MST,int size,char* filename, char* options){
    // Determine, based on the options being passed in, how to print the given Plane
    if(options != NULL && strcmp(options, "output")==0){
        //if option output, print to a file
        fp = fopen(filename, "a");
        fprintf(fp, "# edges of the MST by Prim’s algorithm:\n");
        for(int i=0; i < size-1; i++){
            fprintf(fp, "%i %i %i\n", MST[i][0], MST[i][1], MST[i][2]);
        }
        fprintf(fp, "# total weight of the MST by Prim's algorithm is %i\n", totalWeight(MST, size-1));
        fclose(fp);
    } else {
        //print to terminal
        printf( "# edges of the MST by Prim’s algorithm:\n");
        for(int i=0; i < size-1; i++){
            printf("%i %i %i\n", MST[i][0], MST[i][1], MST[i][2]);
        }
        printf("# total weight of the MST by Prim's algorithm is %i\n", totalWeight(MST, size-1));
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

    // Uses the implicit min of the array and the max as supplied by the user to gen a new x and y coordinate
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


////////////////////////////////////////////////
// BST
//
////////////////////////////////////////////////

int rectDistance(int* coordA, int* coordB){
    // find the rectilinear distance of two coordinates
    return (abs(coordA[0] - coordB[0]) + abs(coordA[1] - coordB[1]));
}

int* copyInstance(int* instance, int len){
    //this is WTF code, need to think about this some more
    int* newInstance = malloc(sizeof(int)*len+1);
    memcpy(newInstance, instance, len);
    return newInstance;
}

int* addVisited(int* visited, int len,  int newPoint){
    // Return a new array that incudes the new point
    // Dead code
    int* newVisited;
    newVisited = copyInstance(visited, len);
    newVisited[len] = newPoint;
    return newVisited;
}

void removeVisited(int* unvisited, int len, int pos){
    // Delete elements from an array, such that it keeps all undeleted values in a contiguous section of the array
    int index = 0;
    for(int i=0; i<len; i++){
        if(unvisited[i] != pos){
            unvisited[index] = unvisited[i];
            index++;
        }
    }
}


int** prims(Plane plane){
    // Returns a MST of format indices1, indice2, weight;
    int visited[plane.instance_size];
    int unvisited[plane.instance_size];
    int* newEdge;
    int sizeUnvisited = plane.instance_size-1;
    int sizeVisited = 0;
    int** MST =  malloc(sizeof(int)*3*plane.instance_size);
    
    //initialize unvisited
    for(int i=0; i < plane.instance_size-1; i++){
      unvisited[i] = i+1;
    }
    // Set an arbitrary starting point
    visited[0] = 0;
    
    // Go through ta set of coordinates and create a MST according to prim's algorithm
    // Prim's algorithm:
    // Arbitrarily choose a starting node
    // Find the shortest distance between the starting node and all nodes that it can connect to
    // add the new node, that has the smallest distance, to visited.
    // Now, until you have visited all nodes, find the minimum distance of all nodes from visited
    // to unvisited
    while(sizeUnvisited >0){
       newEdge = findMin(plane.instance, visited, sizeVisited,  unvisited, sizeUnvisited);
       MST[sizeVisited] = newEdge;
       sizeVisited++;
       visited[sizeVisited] = newEdge[1];
       removeVisited(unvisited, sizeUnvisited, newEdge[1]);
       sizeUnvisited--;
    }
    return MST;

}

int* findMin(int** coords, int* visited, int visitedSize, int* unvisited, int unvisitedSize){
    int minNodeUnvis;
    int minNodeVis;
    int currentDistance;
    int minDistance;
    int* edge = malloc(sizeof(int)*3);
    // Algorithm for finding the minimum distance between two arrays of coordinates
    //i = index of visited array
    for(int i=0; i== 0 || i < visitedSize+1; i++){
        //j = index of unvistied array
        for(int j=0; j < unvisitedSize; j++){
            // calculate the distance between visited[i] and visited[j]
            currentDistance = rectDistance(coords[visited[i]], coords[unvisited[j]]);
            if(i==0 && j==0){
                // if this is the first run through of the for loop set current distance to minDistance and mark
                // each node as visited
                minDistance = currentDistance;
                minNodeUnvis = unvisited[j];
                minNodeVis = visited[i];
            } else if(currentDistance < minDistance){
                // if current distance is less then min distance assign this new combination to minDistance
                minDistance = currentDistance;
                minNodeUnvis = unvisited[j];
                minNodeVis = visited[i];minDistance = currentDistance;

            } else if(currentDistance == minDistance){
                //If there is a tie, reassign minNodeUnvis with return value of breakTie
                minNodeUnvis = breakTie(coords, visited[i], unvisited[j], minNodeUnvis);
                minNodeVis = visited[i];
            }
        }
    }
    edge[0] = minNodeVis;
    edge[1] = minNodeUnvis;
    edge[2] = minDistance;
    return edge;
}

int breakTie(int** coords, int visited, int unvisited, int minNodeUnvis){
    // Breaks the tie by returning the point with the larger delata Y value
    // If delta y values are same, choose the one with highest x value
    // if both x values are the same, choose the minNodeUnvis
    if(abs(coords[minNodeUnvis][1] - coords[visited][1]) > abs(coords[unvisited][1] - coords[visited][1])){
        // Check to see if delta y of MinNode is larger
        return minNodeUnvis;
    } else if(abs(coords[unvisited][1] - coords[visited][1]) > abs(coords[minNodeUnvis][1] - coords[visited][1])){
        // Check to see if delta y of unvisited is largers
        return unvisited;
    } else{
        // find MaxX
        return maxX(coords, minNodeUnvis, unvisited);
    }
}

int maxX(int** coords, int minNodeUnvis, int unvisited){
    //return the max of two ints, in the event of a tie the first int is chosen.
    return coords[unvisited][0] > coords[minNodeUnvis][0]? unvisited: minNodeUnvis;
}

void appendWeight(int* instance, FILE* filename){
    fprintf(filename, "# edges of the MST by Prim’s algorithm:\t");
    fprintf(filename, "%i %i %i", instance[0], instance[1], instance[2]);
}

int totalWeight(int** MST, int length){
    int total = 0;
    for(int i=0; i<length; i++){
        total += MST[i][2];
    }
    return total;
}

int* nodeDegree(int** MST, int size){
    int* degrees = malloc(sizeof(int)*(size+1));
    int count;
    for(int i=0; i< size+1; i++){
        count=0;
        for(int j=0; j< size; j++){
            if(MST[j][0] == i || MST[j][1] ==i){
                count++;
            }
        }
        degrees[i]=count;
    }
    return degrees;
}
