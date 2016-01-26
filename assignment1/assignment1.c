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
} Plane;


/////////////////////////////////////////////////
//
// GETTERS
//
////////////////////////////////////////////////
int* getInput(char* prompt, int num_of_values){
    int *option = malloc(sizeof(int)*2);
    char newLine;
    printf("%s", prompt);
    for(int i = 0; i < num_of_values; i++){
        scanf("%d%c", &option[i], &newLine);
    }
   return option;
}

char* getFilename(char** array, int length){
    char* filename;
    filename = NULL;

        for(int i=0; i <= length; i++){
            if(strcmp(array[i], "-i") == 0){
                filename = array[i+1];
                break;
            }
        }
    return filename;
}

Plane getOptions(void){
    // Prompts user for the input to construct the circuitry info
    // and returns an array of characters
    Plane plane;
    plane.MAX_X[0] = 0;
    plane.MAX_Y[0] = 0;

    int* max_x_y;
    int* num_pt;
    int* num_inst;

    
    max_x_y = getInput("Enter the circuit board size MAX_X MAX_Y: ", 2);
    num_pt = getInput("Enter the number of points NUM_PT: ", 1);
    num_inst = getInput("Enter the number of random instances to be generated: ", 1);

    static int options[4];
    plane.MAX_X[1] = max_x_y[0];
    plane.MAX_Y[1] = max_x_y[1];
    plane.NUM_PT = num_pt[0];
    options[3] = num_inst[0];
 
    free(max_x_y);
    free(num_pt);
    free(num_inst);

    return plane;
}

/////////////////////////////////////////////////
//
// HELPERS
//
////////////////////////////////////////////////
bool isBetween(int between, int lower, int upper){
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

int* splitNumbers(char* line){
    int *array = malloc(sizeof(int)*2) ; // Hard coded because each line in the sample file has at most 2 ints.
    char **delim;
    char* argv[10];
    delim = argv;
    printf("Line is: %s", line);
    if(strcmp(&line[0], " ") != 0){
        for(int i=0; (*delim = strsep(&line, " \t")) != NULL; i++){
            array[i] = atoi(*delim);
        }
    } else {
        array = NULL;
    }
   return array;
}

void printPlane(Plane plane){
    printf("Max X is between %i and %i\n", plane.MAX_X[0], plane.MAX_X[1]);
    printf("Max y is between %i and %i\n", plane.MAX_Y[0], plane.MAX_Y[1]);
    printf("Number of coordinates to generate: %i\n", plane.NUM_PT);
    printf("Remaining number of generations: %i\n \n", plane.generation);
}
/////////////////////////////////////////////////
//
// SETTERS
//
////////////////////////////////////////////////
char** readFile(char* filename){
    size_t nBytes = 255;
    char **lines = malloc(1000*sizeof(char*));
    lines[0] = NULL;
    
    fp = fopen(filename, "rt");
    if (fp == NULL){
           exit(EXIT_FAILURE);
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

Plane getParameters(char* line[]){
    // Check line by line for the presence of a commented line. If the line is commented
    // ignore the line, else add the parameters to the parameters array. 
    Plane plane;
    int** instance = malloc(sizeof(int[2])*100);
    plane.MAX_X[0] = 0;
    plane.MAX_Y[0] = 0;
    plane.instance_size = 0;
    int end;
   
    int index=0;
    for(int i=0; line[i] != NULL; i++){
        if(!isComment(line[i])){
            if(index == 0){
                int* temp = splitNumbers(line[i]);
                plane.MAX_X[1] = temp[0];
                plane.MAX_Y[1] = temp[1];
            }
            if(index == 1){
                int* temp = splitNumbers(line[i]);
                plane.NUM_PT = temp[0];
            }
            if(index >= 2 && strcmp(line[i], "\0") !=0){
                int* temp = splitNumbers(line[i]);
                end = plane.instance_size++;
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
// verifying Data
//
////////////////////////////////////////////////
bool checkInstances(Plane plane){
    int incorrect[plane.instance_size];
    for(int i=0; i < plane.instance_size; i++){
        if(isBetween(plane.instance[i][0], plane.MAX_X[0] , plane.MAX_X[1]) && isBetween(plane.instance[i][0], plane.MAX_X[0] , plane.MAX_X[1])){
            return true;
        } else{
        }
    }
}

bool PlanetoFile(char* filename, Plane plane){
    FILE *newFile;

    //the variable we're going to use to print everything
    char toChar[30];
    newFile = fopen(filename, "w+");

    //print MAX_X and MAX_Y
    int MAX_X = plane.MAX_X[1];
    sprintf(toChar, "%d\t", MAX_X);
    fwrite(toChar, sizeof(char*), 1, newFile);
    sprintf(toChar, "%d\n", plane.MAX_Y[1]);
    fwrite(toChar, sizeof(char*), 1, newFile);

    
    
    for(int i=0; i < plane.NUM_PT; i++){
        printf("Generated instance %i\t%i\n", plane.instance[i][0], plane.instance[i][1]);
        sprintf(toChar, "%d \t", plane.instance[i][0]);
        fwrite(toChar, sizeof(char*), 1, newFile);
        sprintf(toChar, "%d \n", plane.instance[i][1]);
        fwrite(toChar, sizeof(toChar), 1, newFile);
    }
    fclose(newFile);
    return true;
}
/////////////////////////////////////////////////
//
// GEN DATA
//
////////////////////////////////////////////////
int genCoordinate(int min, int max){
    return (rand() % (max-min+1) + min);
}

int* genCoordinates(int* x_array, int* y_array ){
    int* coordinates = malloc(sizeof(int)*2);
    coordinates[0] = genCoordinate(x_array[0], x_array[1]);
    coordinates[1] = genCoordinate(y_array[0], y_array[1]);
    //printf("Coordinates %i %i\n", coordinates[0], coordinates[1]); 
    
    return coordinates;
}

int** genInstance(int numberOfPoints, int* x_array, int* y_array){
    int** instance = malloc(sizeof(int)*2*numberOfPoints);
    int* coordinates;
    for(int i=0; i<numberOfPoints; i++){
        coordinates = genCoordinates(x_array, y_array);
        while(checkUnique(coordinates, instance, i-1) == false){
            coordinates = genCoordinates(x_array, y_array);
        }
        instance[i] = coordinates;
        //printf("Instance %i %i\n", instance[i][0], instance[i][1]);
    }
    return instance;
}

bool checkUnique(int* coordinate, int** instance,  int size){
    for(int i=0; i<size; i++){
        if(coordinate[0] == instance[i][0] && coordinate[1] == instance[i][1]){
            return false;
        }
    }
    return true;
}
/////////////////////////////////////////////////
//
// MAIN
//
////////////////////////////////////////////////

// Must check for errors in instance, if so output error to console.
// If option output is given, output file to a text
// If option output is not given output to screen
int main(int argc, char **argv){
    char* filename; 
    char** lines;
    Plane plane;
    char* options;
    //initiallize rand() with current time
    srand(time(NULL));
    if(argc >= 2){
        filename = getFilename(argv, argc);
        options = getOption(argv, argc);
        lines = readFile(filename);
        free(lines);
        plane = getParameters(lines);
    }else {
        plane = getOptions();
        plane.instance = genInstance(plane.NUM_PT, plane.MAX_X, plane.MAX_Y);
        free(plane.instance);
    }
    for(int i=0; i < plane.NUM_PT; i++){
        printf("Generated instance %i\t%i\n", plane.instance[i][0], plane.instance[i][1]);
    }
    printPlane(plane);
    
    printf("Instance size = %i\n", plane.instance_size);
    
    PlanetoFile("newFilez.txt", plane);
    
    return 0;
}
