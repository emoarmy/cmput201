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
void readFile(char* filename){
    size_t nBytes = 255;
    char** lines = malloc(sizeof(sizeof(char*)*255)*255);
    
    fp = fopen(filename, "rt");
    if (fp == NULL){
           exit(EXIT_FAILURE);
    }
    //int* somenum;
    char* somechar;
    int index =0;
    while(index < 254){
        
        if (feof(fp)){
            // checking to see if we're pointing at end of the file
            break;
        }
        ssize_t bytesize;
        bytesize = getline(&lines[index], &nBytes, fp);
        index++;
        //printf("%s", lines);
    }
    fclose(fp);

}

/////////////////////////////////////////////////
//
// MAIN
//
////////////////////////////////////////////////
int main(int argc, char **argv){
    char* filename; 
    /* int max_x, max_y; */
    /* int num_pt; */
    /* int num_to_generate; */
    int* parameters = 0;
    printf("%i \n", argc);
    if(argc >= 2){
        filename = getFilename(argv, argc);
        readFile(filename);
    }else {
        parameters =  getOptions();
    }
    
    //printf("%i %i %i %i\n", parameters[0], parameters[1], parameters[2], parameters[3]);
    return 0;
}
