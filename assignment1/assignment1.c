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

        for(int i=0; i < length; i++){
            if(strcmp(array[i], "-i") == 0){
                filename = array[i+1];
                break;
            }
        }
    return filename;
}

char* getOption(char** array, int length){
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

Plane getParams(void){
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
    plane.instance_size=0;
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
bool checkInstances(Plane plane){
    int incorrect[plane.instance_size];
    for(int i=0; i < plane.instance_size; i++){
        if(isBetween(plane.instance[i][0], plane.MAX_X[0] , plane.MAX_X[1]) && isBetween(plane.instance[i][0], plane.MAX_X[0] , plane.MAX_X[1])){
            return true;
        }
    }
    return false;
}

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
    printf("Options: %s\n", options);
    if(options != NULL && strcmp(options, "output") == 0 ){
        planeToFile("newFilez.txt", plane);
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
    return (rand() % (max-min+1) + min);
}

int* genCoordinates(int* x_array, int* y_array ){
    int* coordinates = malloc(sizeof(int)*2);
    coordinates[0] = genCoordinate(x_array[0], x_array[1]);
    coordinates[1] = genCoordinate(y_array[0], y_array[1]);

    return coordinates;
}

bool checkUnique(int* coordinate, int** instance,  int size){
    for(int i=0; i<size; i++){
        if(coordinate[0] == instance[i][0] && coordinate[1] == instance[i][1]){
            printf("Not Unique");
            return false;
        }
    }
    return true;
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

char* genFilename(int numberOfPoints, int index){
    char* string = malloc(sizeof(char)*100);
    snprintf(string, sizeof(string), "instance%.3i_%.3i.txt", numberOfPoints, index);
    return string;
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
    char* filename = NULL;
    char** lines;
    Plane plane;
    char* options = NULL;
    //initiallize rand() with current time
    srand(time(NULL));
    plane.generation = 1;

    // Cheching for arguments, if they are greater than or equal to two, assume
    // their are options and a filename being passed in trying to be passed in.
    if(argc >= 2){
        filename = getFilename(argv, argc);
        options = getOption(argv, argc);
    }

    // Grab Data
    if (filename == NULL){
        plane = getParams();;
    } else {
        lines = readFile(filename);
        free(lines);
        plane = getParameters(lines);
    }
    while(plane.generations < 
    // printPlane needs to check for option type.
    printPlane(plane, options);

    printf("Instance size = %i\n", plane.instance_size);
    printf("Filename: %s\n", genFilename(plane.NUM_PT, plane.generation));
    return 0;

}
