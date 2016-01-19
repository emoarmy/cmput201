#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


FILE *fp;

/////////////////////////////////////////////////
//
// STRUCTS
//
/////////////////////////////////////////////////
typedef struct 
{
    int MAX_X;
    int MAX_Y;
    int NUM_PT;
} plane;


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

int* getOptions(void){
    // Prompts user for the input to construct the circuitry info
    // and returns an array of characters
    int* max_x_y;
    int* num_pt;
    int* num_inst;
    
    max_x_y = getInput("Enter the circuit board size MAX_X MAX_Y: ", 2);
    num_pt = getInput("Enter the number of points NUM_PT: ", 1);
    num_inst = getInput("Enter the number of random instances to be generated: ", 1);

    static int options[4];
    options[0] = max_x_y[0];
    options[1] = max_x_y[1];
    options[2] = num_pt[0];
    options[3] = num_inst[0];
 
    free(max_x_y);
    free(num_pt);
    free(num_inst);

    return options;
}

/////////////////////////////////////////////////
//
// HELPERS
//
////////////////////////////////////////////////

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
    for(int i=0; (*delim = strsep(&line, " \t")) != NULL; i++){
        array[i] = atoi(*delim);
    }
    return array;
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
    printf("Lines: %i \n", index+1);
    fclose(fp);
    return lines;
}

int* getParameters(char* line[], int* size){
    // Check line by line for the presence of a commented line. If the line is commented
    // ignore the line, else add the parameters to the parameters array. 
    
    // Passing in size is a dirty trick to pass back the size of an int array in C
    
    int* parameters = malloc(sizeof(int)*20);
    int index=0;
    for(int i=0; line[i] != NULL; i++){
        if(!isComment(line[i])){
            parameters[index] = *splitNumbers(line[i]);
            index++;
        }
    }
    *size = index;
    return parameters;
}

/////////////////////////////////////////////////
//
// MAIN
//
////////////////////////////////////////////////
int main(int argc, char **argv){
    char* filename; 
    char** lines;
    int size=0;
    /* int max_x, max_y; */
    /* int num_pt; */
    /* int num_to_generate; */
    int* parameters = 0;
    printf("%i \n", argc);
    if(argc >= 2){
        filename = getFilename(argv, argc);
        lines = readFile(filename);
        free(lines);
        parameters = getParameters(lines, &size);
    }else {
        parameters =  getOptions();
    }
    printf("Size = %i\n", size);
    printf("%i %i %i %i %i\n", parameters[0], parameters[1], parameters[2], parameters[3], parameters[4]);
    return 0;
}
