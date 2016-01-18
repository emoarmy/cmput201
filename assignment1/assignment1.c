#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


FILE *fp;
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

bool isComment(char* line){
    // Returns true if the line starts with #
    return (strcmp(line, "#") !=0);
}
/////////////////////////////////////////////////
//
// HELPERS
//
////////////////////////////////////////////////

bool valideLine(char* line){
    if(line){
        return true;
    } else {
        return false;
    }
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
    //int* somenum;
    int index =0;
    while(index < 3){
        
        if (feof(fp)){
            // checking to see if we're pointing at end of the file
            break;
        }
        getline(&lines[index], &nBytes, fp);
        index++;
        //printf("%s", lines);
    }
    fclose(fp);
    return lines;
}

/////////////////////////////////////////////////
//
// MAIN
//
////////////////////////////////////////////////
int main(int argc, char **argv){
    char* filename; 
    char** lines;
    /* int max_x, max_y; */
    /* int num_pt; */
    /* int num_to_generate; */
    int* parameters = 0;
    printf("%i \n", argc);
    if(argc >= 2){
        filename = getFilename(argv, argc);
        lines = readFile(filename);
        for(int i=0; i< 2; i++){
            printf("%s / ", lines[i]);
        }
    }else {
        parameters =  getOptions();
    }
    
    //printf("%i %i %i %i\n", parameters[0], parameters[1], parameters[2], parameters[3]);
    return 0;
}
